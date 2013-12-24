#include "ISOXMLParser.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include "support/base64.h"
#include "ISOObjectGroupInfo.h"
#include "ISOObjectInfo.h"
#include "ISOLayerInfo.h"
#include "ISOTileInfo.h"
#include "ISOTilesetInfo.h"


using namespace std;

NS_CC_YHGE_BEGIN

/*
 void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
 void tmx_endElement(void *ctx, const xmlChar *name);
 void tmx_characters(void *ctx, const xmlChar *ch, int len);
 */

static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if (dict)
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}

ISOXMLParser::ISOXMLParser()
:m_pMapInfo(NULL)
,m_bTranslateLayerData(false)
{

}

ISOXMLParser::~ISOXMLParser()
{
    CCLOG("ISOXMLParser destroy");
    CC_SAFE_RELEASE(m_pMapInfo);
}

ISOXMLParser * ISOXMLParser::formatWithXMLFile(const char *tmxFile)
{
    ISOXMLParser *pRet = new ISOXMLParser();
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOXMLParser * ISOXMLParser::formatWithXML(const char* tmxString, const char* resourcePath)
{
    ISOXMLParser *pRet = new ISOXMLParser();
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void ISOXMLParser::internalInit(const char* tmxFileName, const char* resourcePath)
{
    m_pMapInfo=new ISOMapInfo();
    m_pMapInfo->init();
    
        
    if (tmxFileName != NULL)
    {
        m_sTMXFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        m_sResources = resourcePath;
    }
    m_sCurrentString = "";
        
}
bool ISOXMLParser::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool ISOXMLParser::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(m_sTMXFileName.c_str());
}

bool ISOXMLParser::parseXMLString(const char *xmlString)
{
    int len = strlen(xmlString);
    if (xmlString == NULL || len <= 0)
    {
        return false;
    }
    
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    return parser.parse(xmlString, len);
}

bool ISOXMLParser::parseXMLFile(const char *xmlFilename)
{
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);

    return parser.parse(xmlFilename);
}


// the XML parser calls here with all the elements
void ISOXMLParser::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    if(atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2)
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(std::pair<std::string, std::string>(key, value));
        }
    }
    if(elementName == "map")
    {
        std::string version = valueForKey("version", attributeDict);
        if ( version != "1.0")
        {
            CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %@", version.c_str());
        }
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        m_pMapInfo->setMapSize(s);
        
        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        m_pMapInfo->setTileSize(s);
        
        //#RRGGBB
        const char* backgroundColor=valueForKey("backgroundcolor", attributeDict);
        
        long backgroundColorValue=strtol(backgroundColor+1, NULL, 16);
        ccColor3B color=ccc3(backgroundColorValue>>16,backgroundColorValue>>8 & 0xFF,backgroundColorValue &0xFF);
        m_pMapInfo->setBackgroundColor(color);
        
        
        // The parent element is now "map"
        m_nCurrentElement=ISOParsePropertyMap;
    }
    else if(elementName == "tileset")
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            if (m_sTMXFileName.find_last_of("/") != string::npos)
            {
                string dir = m_sTMXFileName.substr(0, m_sTMXFileName.find_last_of("/") + 1);
                externalTilesetFilename = dir + externalTilesetFilename;
            }
            else
            {
                externalTilesetFilename = m_sResources + "/" + externalTilesetFilename;
            }
            externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathForFilename(externalTilesetFilename.c_str());
            
            this->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            ISOTilesetInfo *tileset = new ISOTilesetInfo();
            tileset->setName(valueForKey("name", attributeDict));
            tileset->setFirstGid((unsigned int)atoi(valueForKey("firstgid", attributeDict)));
            tileset->setSpacing ((unsigned int)atoi(valueForKey("spacing", attributeDict)));
            tileset->setMargin ((unsigned int)atoi(valueForKey("margin", attributeDict)));
            CCSize s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->setTileSize(s);
            
            m_pMapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
        m_nCurrentElement=ISOParsePropertyTileset;
    }
    else if(elementName == "tile")
    {
        ISOTilesetInfo* tilesetInfo = (ISOTilesetInfo*)m_pMapInfo->getTilesets()->lastObject();
        unsigned int tileId= atoi(valueForKey("id", attributeDict));
        
        ISOTileInfo* tileInfo=new ISOTileInfo();
        tileInfo->setId(tileId);
        
        tilesetInfo->getTiles()->addObject(tileInfo);
        tileInfo->release();
       
        m_nCurrentElement=ISOParsePropertyTile;
        
    }
    else if(elementName == "layer")
    {
        ISOLayerInfo *layerInfo = new ISOLayerInfo();
        layerInfo->setName(valueForKey("name", attributeDict));
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        layerInfo->setLayerSize(s);
        
        std::string visible = valueForKey("visible", attributeDict);
        layerInfo->setVisible(!(visible == "0"));
        
        std::string opacity = valueForKey("opacity", attributeDict);
        if( opacity != "" )
        {
            layerInfo->setOpacity((unsigned char)255*atof(opacity.c_str()));
        }
        else
        {
            layerInfo->setOpacity(255);
        }
        CCPoint pos;
        
        pos.x = (float)atof(valueForKey("x", attributeDict));
        pos.y = (float)atof(valueForKey("y", attributeDict));
        layerInfo->setOffset(pos);
        
        m_pMapInfo->getLayers()->addObject(layerInfo);
        layerInfo->release();
        
        // The parent element is now "layer"
        m_nCurrentElement=ISOParsePropertyLayer;
        
    }
    else if(elementName == "objectgroup")
    {
        ISOObjectGroupInfo *objectGroup = new ISOObjectGroupInfo();
        objectGroup->setName(valueForKey("name", attributeDict));
        CCPoint positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * m_pMapInfo->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * m_pMapInfo->getTileSize().height;
        objectGroup->setPositionOffset(positionOffset);
        
        m_pMapInfo->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();
        
        // The parent element is now "objectgroup"
        m_nCurrentElement=ISOParsePropertyObjectGroup;
        
    }
    else if(elementName == "image")
    {
        
        
        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        
        if (m_sTMXFileName.find_last_of("/") != string::npos)
        {
            string dir = m_sTMXFileName.substr(0, m_sTMXFileName.find_last_of("/") + 1);
            imagename=dir+imagename;
        }
        else
        {
            imagename=m_sResources + (m_sResources.size() ? "/" : "") + imagename;
        }
        
        //check width and height
        const char* widthValue = valueForKey("width", attributeDict);
        const char* heightValue = valueForKey("height", attributeDict);
        
        ISOTilesetInfo* tilesetInfo = (ISOTilesetInfo*)m_pMapInfo->getTilesets()->lastObject();
        //use by tileset or tile
        if ( m_nCurrentElement == ISOParsePropertyTileset ){
            
            tilesetInfo->setImageSource(imagename.c_str());
            
            if(widthValue && heightValue){
                CCSize s;
                s.width=(float)atof(widthValue);
                s.height=(float)atof(heightValue);
                tilesetInfo->setImageSize(s);
            }
            
        }else if(m_nCurrentElement == ISOParsePropertyTile){
            
            ISOTileInfo* tileInfo=(ISOTileInfo*)tilesetInfo->getTiles()->lastObject();
            
            tileInfo->setImageSource(imagename.c_str());
            
            if(widthValue && heightValue){
                CCSize s;
                s.width=(float)atof(widthValue);
                s.height=(float)atof(heightValue);
                tileInfo->setImageSize(s);
            }
        }
        
    }
    else if(elementName == "data")
    {
        //TODO support image data
        std::string encoding = valueForKey("encoding", attributeDict);
        std::string compression = valueForKey("compression", attributeDict);
        
        if( encoding == "base64" )
        {

            m_nLayerAttribs |=ISOParseLayerAttribBase64;
            m_bStoringCharacters=true;
            
            if( compression == "gzip" )
            {
                m_nLayerAttribs |=ISOParseLayerAttribGzip;
            } else
                if (compression == "zlib")
                {
                    m_nLayerAttribs |=ISOParseLayerAttribZlib;
                }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert(m_nLayerAttribs != ISOParseLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );
        
    }
    else if(elementName == "object")
    {
        ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)m_pMapInfo->getObjectGroups()->lastObject();
        

        ISOObjectInfo *objInfo = new ISOObjectInfo();
        
        objInfo->setName(valueForKey("name", attributeDict));
        
        objInfo->setType(valueForKey("type", attributeDict));
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        objInfo->setSize(s);
        // But X and Y since they need special treatment
        // X
        
        CCPoint pos;
        const char* value = valueForKey("x", attributeDict);
        if( value )
        {
            pos.x = (float)atof(value) + objectGroupInfo->getPositionOffset().x;
        }
        
        // Y
        value = valueForKey("y", attributeDict);
        if( value )  {
            float y = (float)atof(value) + objectGroupInfo->getPositionOffset().y;
            
            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            pos.y = (m_pMapInfo->getMapSize().height * m_pMapInfo->getTileSize().height) - y - s.height;
        }
        
        objInfo->setPosition(pos);
        
        // Add the object to the objectGroup
        objectGroupInfo->getObjects()->addObject(objInfo);
        objInfo->release();
        
        // The parent element is now "object"
        m_nCurrentElement=ISOParsePropertyObject;
        
    }
    else if(elementName == "property")
    {
        if ( m_nCurrentElement == ISOParsePropertyNone )
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                  valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        }
        else if ( m_nCurrentElement == ISOParsePropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            m_pMapInfo->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOParsePropertyLayer )
        {
            // The parent element is the last layer
            ISOLayerInfo* layerInfo = (ISOLayerInfo*)m_pMapInfo->getLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layerInfo->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOParsePropertyObjectGroup )
        {
            // The parent element is the last object group
            ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)m_pMapInfo->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            const char* key = valueForKey("name", attributeDict);
            objectGroupInfo->getProperties()->setObject(value, key);
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOParsePropertyObject )
        {
            // The parent element is the last object
            ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)m_pMapInfo->getObjectGroups()->lastObject();
            ISOObjectInfo* objInfo = (ISOObjectInfo*)objectGroupInfo->getObjects()->lastObject();
            
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            objInfo->getProperties()->setObject(value,key.c_str());
            value->release();
        }
        else if ( m_nCurrentElement == ISOParsePropertyTile )
        {
            ISOTilesetInfo* tilesetInfo =(ISOTilesetInfo*)m_pMapInfo->getTilesets()->lastObject();
            ISOTileInfo* tileInfo=(ISOTileInfo*)tilesetInfo->getTiles()->lastObject();
            
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            tileInfo->getProperties()->setObject(value, key.c_str());
            value->release();
        }
    }
    else if (elementName == "polygon")
    {
        // find parent object's dict and add polygon-points to it
        // ISOObjectGroupInfo* objectGroup = (ISOObjectGroupInfo*)m_pObjectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject(attributeDict objectForKey:@"points"] forKey:@"polygonPoints"];
        
    }
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // ISOObjectGroupInfo* objectGroup = (ISOObjectGroupInfo*)m_pObjectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject:[attributeDict objectForKey:@"points"] forKey:@"polylinePoints"];
    }
    
    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void ISOXMLParser::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    
    int len = 0;
    
    if(elementName == "data" && m_nLayerAttribs&ISOParseLayerAttribBase64)
    {
        m_bStoringCharacters=false;
        
        ISOLayerInfo* layerInfo = (ISOLayerInfo*)m_pMapInfo->getLayers()->lastObject();
        
        std::string currentString = this->getCurrentString();
        unsigned char *buffer;
        len = base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer )
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }
        
        unsigned int* tiles;
        
        if( m_nLayerAttribs & (ISOParseLayerAttribGzip | ISOParseLayerAttribZlib) )
        {
            unsigned char *deflated;
            CCSize s = layerInfo->getLayerSize();
            // int sizeHint = s.width * s.height * sizeof(uint32_t);
            int sizeHint = (int)(s.width * s.height * sizeof(unsigned int));
            
            int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, len, &deflated, sizeHint);
            CCAssert(inflatedLen == sizeHint, "");
            
            inflatedLen = (size_t)&inflatedLen; // XXX: to avoid warnings in compiler
            
            delete [] buffer;
            buffer = NULL;
            
            if( ! deflated )
            {
                CCLOG("cocos2d: TiledMap: inflate data error");
                return;
            }

            tiles=(unsigned int*) deflated; 

        }
        else
        {
            tiles=(unsigned int*) buffer;
        }
        
        if(m_bTranslateLayerData){
            struct timeval startTime;
            gettimeofday(&startTime,0);
            
            unsigned int* translatedTiles;
            translateMapTiles(tiles, layerInfo, &translatedTiles);
            layerInfo->setTiles(translatedTiles);
            delete [] tiles;
            tiles=NULL;
            
            struct timeval endTime;
            gettimeofday(&endTime,0);
            CCLOG("trans use:%d,%d",endTime.tv_sec-startTime.tv_sec,endTime.tv_usec-startTime.tv_usec);
        }else{
            layerInfo->setTiles(tiles);
        }
        
        this->setCurrentString("");
        
    }
    else if (elementName == "map")
    {
        // The map element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
    else if (elementName == "tileset")
    {
        // The tileset element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
    else if (elementName == "layer")
    {
        // The layer element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
    else if (elementName == "object")
    {
        // The object element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
    else if (elementName == "tile")
    {
        // The tile element has ended
        m_nCurrentElement=ISOParsePropertyNone;
    }
}

void ISOXMLParser::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    std::string pText((char*)ch,0,len);
    
    if (m_bStoringCharacters)
    {
        std::string currentString = this->getCurrentString();
        currentString += pText;
        this->setCurrentString(currentString.c_str());
    }
}

/**
 * x'=layerHeight-y;
 * y'=layerWidth-x;
 *
 */
void ISOXMLParser::translateMapTiles(unsigned int * pTiles,ISOLayerInfo* layerInfo,unsigned int **out)
{
    CCSize layerSize=layerInfo->getLayerSize();
    unsigned int layerWidth=(unsigned int)layerSize.width;
    unsigned int layerHeight=(unsigned int)layerSize.height;
    
    *out=new unsigned int[layerWidth*layerHeight];
    if(*out){    
        //转换索引
        unsigned int currentIndex=0,currentId=0;
        unsigned int translatedIndex=0,translatedX=0,translatedY=0;
        
        unsigned int translatedLayerMaxX=layerHeight-1;
        unsigned int translatedLayerMaxY=layerWidth-1;
        
        for(unsigned int y=0;y<layerHeight;++y){
            for(unsigned int x=0;x<layerWidth;++x){
                currentIndex=y*layerWidth+x;
                currentId=pTiles[currentIndex];
                
                translatedX=translatedLayerMaxX-y;
                translatedY=translatedLayerMaxY-x;
                translatedIndex=translatedY*layerHeight+translatedX;
//                CCLOG("tran:%u,%u,%u,%u",translatedX,translatedY,translatedIndex,currentId);
                (*out)[translatedIndex]=currentId;
            }
        }
        CCSize translatedSize=CCSizeMake(layerSize.height, layerSize.width);
        //转换高宽
        layerInfo->setLayerSize(translatedSize);
    }
}

ISOMapInfo* ISOXMLParser::getMapInfo()
{
    return m_pMapInfo;
}


NS_CC_YHGE_END
