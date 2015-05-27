#include "ISOXMLParser.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include <yhge/CocosExt/Support/base64.h>
#include "ISOObjectGroupInfo.h"
#include "ISOObjectInfo.h"
#include "ISOLayerInfo.h"
#include "ISOTileInfo.h"
#include "ISOTilesetInfo.h"


using namespace std;

NS_CC_YHGE_ISOMETRIC_BEGIN

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
:_mapInfo(NULL)
,_translateLayerData(false)
,_translateObjectCoord(false)
,_childIndex(0)
{

}

ISOXMLParser::~ISOXMLParser()
{
    CCLOG("ISOXMLParser destroy");
    CC_SAFE_RELEASE(_mapInfo);
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
    _mapInfo=new ISOMapInfo();
    _mapInfo->init();
    
        
    if (tmxFileName != NULL)
    {
        _tMXFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        _resources = resourcePath;
    }
    _currentString = "";
        
}
bool ISOXMLParser::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool ISOXMLParser::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(_tMXFileName.c_str());
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
            CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %s", version.c_str());
        }
        
        Size s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        _mapInfo->setMapSize(s);
        
        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        _mapInfo->setTileSize(s);
        
        //#RRGGBB
        const char* backgroundColor=valueForKey("backgroundcolor", attributeDict);
        
        long backgroundColorValue=strtol(backgroundColor+1, NULL, 16);
        ccColor3B color=ccc3(backgroundColorValue>>16,backgroundColorValue>>8 & 0xFF,backgroundColorValue &0xFF);
        _mapInfo->setBackgroundColor(color);
        
        
        // The parent element is now "map"
        _currentElement=ISOParsePropertyMap;
    }
    else if(elementName == "tileset")
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            if (_tMXFileName.find_last_of("/") != string::npos)
            {
                string dir = _tMXFileName.substr(0, _tMXFileName.find_last_of("/") + 1);
                externalTilesetFilename = dir + externalTilesetFilename;
            }
            else
            {
                externalTilesetFilename = _resources + "/" + externalTilesetFilename;
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
            Size s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->setTileSize(s);
            
            _mapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
        _currentElement=ISOParsePropertyTileset;
    }
    else if(elementName == "tile")
    {
        ISOTilesetInfo* tilesetInfo = (ISOTilesetInfo*)_mapInfo->getTilesets()->lastObject();
        unsigned int tileId= atoi(valueForKey("id", attributeDict));
        
        ISOTileInfo* tileInfo=new ISOTileInfo();
        tileInfo->setId(tileId);
        
        tilesetInfo->getTiles()->addObject(tileInfo);
        tileInfo->release();
       
        _currentElement=ISOParsePropertyTile;
        
    }
    else if(elementName == "layer")
    {
        ISOLayerInfo *layerInfo = new ISOLayerInfo();
        layerInfo->setName(valueForKey("name", attributeDict));
        
        Size s;
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
        Vec2 pos;
        
        pos.x = (float)atof(valueForKey("x", attributeDict));
        pos.y = (float)atof(valueForKey("y", attributeDict));
        layerInfo->setOffset(pos);
        
        layerInfo->setRenderIndex(_childIndex++);
        
        _mapInfo->getLayers()->addObject(layerInfo);
        layerInfo->release();
        
        // The parent element is now "layer"
        _currentElement=ISOParsePropertyLayer;
        
    }
    else if(elementName == "objectgroup")
    {
        ISOObjectGroupInfo *objectGroup = new ISOObjectGroupInfo();
        objectGroup->setName(valueForKey("name", attributeDict));
        Vec2 positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * _mapInfo->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * _mapInfo->getTileSize().height;
        objectGroup->setPositionOffset(positionOffset);
        
        objectGroup->setRenderIndex(_childIndex++);
        
        _mapInfo->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();
        
        // The parent element is now "objectgroup"
        _currentElement=ISOParsePropertyObjectGroup;
        
    }
    else if(elementName == "image")
    {
        
        
        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        
        if (_tMXFileName.find_last_of("/") != string::npos)
        {
            string dir = _tMXFileName.substr(0, _tMXFileName.find_last_of("/") + 1);
            imagename=dir+imagename;
        }
        else
        {
            imagename=_resources + (_resources.size() ? "/" : "") + imagename;
        }
        
        //check width and height
        const char* widthValue = valueForKey("width", attributeDict);
        const char* heightValue = valueForKey("height", attributeDict);
        
        ISOTilesetInfo* tilesetInfo = (ISOTilesetInfo*)_mapInfo->getTilesets()->lastObject();
        //use by tileset or tile
        if ( _currentElement == ISOParsePropertyTileset ){
            
            tilesetInfo->setImageSource(imagename.c_str());
            
            if(widthValue && heightValue){
                Size s;
                s.width=(float)atof(widthValue);
                s.height=(float)atof(heightValue);
                tilesetInfo->setImageSize(s);
            }
            
        }else if(_currentElement == ISOParsePropertyTile){
            
            ISOTileInfo* tileInfo=(ISOTileInfo*)tilesetInfo->getTiles()->lastObject();
            
            tileInfo->setImageSource(imagename.c_str());
            
            if(widthValue && heightValue){
                Size s;
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

            _layerAttribs |=ISOParseLayerAttribBase64;
            _storingCharacters=true;
            
            if( compression == "gzip" )
            {
                _layerAttribs |=ISOParseLayerAttribGzip;
            } else
                if (compression == "zlib")
                {
                    _layerAttribs |=ISOParseLayerAttribZlib;
                }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert(_layerAttribs != ISOParseLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );
        
    }
    else if(elementName == "object")
    {
        ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)_mapInfo->getObjectGroups()->lastObject();

		ISOObjectInfo *objInfo = new ISOObjectInfo();
        
        objInfo->setName(valueForKey("name", attributeDict));
        
        objInfo->setType(valueForKey("type", attributeDict));
        
		//object的size和position是地图的像素值，不是屏幕的像素值。
		//一个地图的单位坐标像素值和yUnit相等。

        Size s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        objInfo->setSize(s);
        
        Vec2 pos;
        std::string value = valueForKey("x", attributeDict);
        if( value!="" )
        {
            pos.x = (float)atof(value.c_str());
        }
        
        // Y
        value = valueForKey("y", attributeDict);
        if( value!="" )  {
            pos.y = (float)atof(value.c_str());
        }
        
        if (_translateObjectCoord) {
            pos=this->translateObjectCoord(pos);
        }
        
        objInfo->setPosition(pos);
        
        //rotation
        value = valueForKey("opacity", attributeDict);
        if (value!="") {
            objInfo->setRotation((float)atof(value.c_str()));
        }
        
        //gid
        value = valueForKey("gid", attributeDict);
        if (value!="") {
            objInfo->setGid(atoi(value.c_str()));
        }
        
        //visible
        value = valueForKey("visible", attributeDict);
        if (value!="") {
            objInfo->setVisible(atoi(value.c_str()));
        }
        
        // Add the object to the objectGroup
        objectGroupInfo->getObjects()->addObject(objInfo);
        objInfo->release();
        
        // The parent element is now "object"
        _currentElement=ISOParsePropertyObject;
        
    }
    else if(elementName == "property")
    {
        if ( _currentElement == ISOParsePropertyNone )
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                  valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        }
        else if ( _currentElement == ISOParsePropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            _mapInfo->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( _currentElement == ISOParsePropertyLayer )
        {
            // The parent element is the last layer
            ISOLayerInfo* layerInfo = (ISOLayerInfo*)_mapInfo->getLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layerInfo->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( _currentElement == ISOParsePropertyObjectGroup )
        {
            // The parent element is the last object group
            ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)_mapInfo->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            const char* key = valueForKey("name", attributeDict);
            objectGroupInfo->getProperties()->setObject(value, key);
            value->release();
            
        }
        else if ( _currentElement == ISOParsePropertyObject )
        {
            // The parent element is the last object
            ISOObjectGroupInfo* objectGroupInfo = (ISOObjectGroupInfo*)_mapInfo->getObjectGroups()->lastObject();
            ISOObjectInfo* objInfo = (ISOObjectInfo*)objectGroupInfo->getObjects()->lastObject();
            
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            objInfo->getProperties()->setObject(value,key.c_str());
            value->release();
        }
        else if ( _currentElement == ISOParsePropertyTile )
        {
            ISOTilesetInfo* tilesetInfo =(ISOTilesetInfo*)_mapInfo->getTilesets()->lastObject();
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
        // ISOObjectGroupInfo* objectGroup = (ISOObjectGroupInfo*)_objectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject(attributeDict objectForKey:@"points"] forKey:@"polygonPoints"];
        
    }
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // ISOObjectGroupInfo* objectGroup = (ISOObjectGroupInfo*)_objectGroups->lastObject();
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
    
    if(elementName == "data" && _layerAttribs&ISOParseLayerAttribBase64)
    {
        _storingCharacters=false;
        
        ISOLayerInfo* layerInfo = (ISOLayerInfo*)_mapInfo->getLayers()->lastObject();
        
        std::string currentString = this->getCurrentString();
        unsigned char *buffer;
        len = yhge::base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer )
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }
        
        unsigned int* tiles;
        
        if( _layerAttribs & (ISOParseLayerAttribGzip | ISOParseLayerAttribZlib) )
        {
            unsigned char *deflated;
            Size s = layerInfo->getLayerSize();
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
        
        if(_translateLayerData){
            struct timeval startTime;
            gettimeofday(&startTime,0);
            
            unsigned int* translatedTiles;
            translateMapTiles(tiles, layerInfo, &translatedTiles);
            layerInfo->setTiles(translatedTiles);
            delete [] tiles;
            tiles=NULL;
            
            struct timeval endTime;
            gettimeofday(&endTime,0);
            CCLOG("trans use:%ld,%d",endTime.tv_sec-startTime.tv_sec,endTime.tv_usec-startTime.tv_usec);
        }else{
            layerInfo->setTiles(tiles);
        }
        
        this->setCurrentString("");
        
    }
    else if (elementName == "map")
    {
        // The map element has ended
        _currentElement=ISOParsePropertyNone;
    }
    else if (elementName == "tileset")
    {
        // The tileset element has ended
        _currentElement=ISOParsePropertyNone;
    }
    else if (elementName == "layer")
    {
        // The layer element has ended
        _currentElement=ISOParsePropertyNone;
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        _currentElement=ISOParsePropertyNone;
    }
    else if (elementName == "object")
    {
        // The object element has ended
        _currentElement=ISOParsePropertyNone;
    }
    else if (elementName == "tile")
    {
        // The tile element has ended
        _currentElement=ISOParsePropertyNone;
    }
}

void ISOXMLParser::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    std::string pText((char*)ch,0,len);
    
    if (_storingCharacters)
    {
        std::string currentString = this->getCurrentString();
        currentString += pText;
        this->setCurrentString(currentString.c_str());
    }
}

/**
 * tmx中使用的坐标系是。x正方朝右下，y正方向朝左下。
 * 而在游戏中由于和opengl的坐标系统相统一。x正方向朝右上，y正方向朝左上。
 * tmx到游戏转换要交换x,y坐标系统。
 * x'=layerHeight-y;
 * y'=layerWidth-x;
 */
void ISOXMLParser::translateMapTiles(unsigned int * pTiles,ISOLayerInfo* layerInfo,unsigned int **out)
{
    Size layerSize=layerInfo->getLayerSize();
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
        Size translatedSize=CCSizeMake(layerSize.height, layerSize.width);
        //转换高宽
        layerInfo->setLayerSize(translatedSize);
    }
}

/**
 * 把tiled里的object坐标转成地图格子坐标
 * 注意坐标系的交换
 */
Vec2 ISOXMLParser::translateObjectCoord(const Vec2& pos)
{
    Vec2 coord;
    
    Size tileSize=_mapInfo->getTileSize();
	Size mapSize=_mapInfo->getMapSize();
    
    CCAssert(tileSize.height!=0, "tilesize must big then zero");
    
    coord.x=mapSize.height-pos.y/tileSize.height;
    coord.y=mapSize.width-pos.x/tileSize.height;

    return coord;
}

//把tiled里的object格式像素大小转成坐标大小
Size ISOXMLParser::translateObjectSize(const Size& size)
{
    Size gridSize;
    
    Size tileSize=_mapInfo->getTileSize();
    
    CCAssert(tileSize.height!=0, "tilesize must big then zero");
    
    gridSize.width=size.width/tileSize.height;
    gridSize.height=size.height/tileSize.height;

    return gridSize;
}

ISOMapInfo* ISOXMLParser::getMapInfo()
{
    return _mapInfo;
}


NS_CC_YHGE_ISOMETRIC_END
