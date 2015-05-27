#include "ISOXMLReader.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include <yhge/CocosExt/Support/base64.h>
#include <yhge/Isometric/ISOCoordinate.h>

#include "../ISOBase.h"
#include "../layers/ISOTileLayer.h"
#include "../ISOTileMap.h"

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

ISOXMLReader::ISOXMLReader()
:m_map(NULL)
,m_currentElement(0)
,m_uCurrentGid(0)
,m_layerAttribs(0)
,m_storingCharacters(0)
{

}

ISOXMLReader::~ISOXMLReader()
{
    CCLOG("ISOXMLReader destroy");
}

ISOXMLReader * ISOXMLReader::formatWithXMLFile(ISOTileMap* map,const char *tmxFile)
{
    ISOXMLReader *pRet = new ISOXMLReader();
    pRet->setMap(map);
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOXMLReader * ISOXMLReader::formatWithXML(ISOTileMap* map,const char* tmxString, const char* resourcePath)
{
    ISOXMLReader *pRet = new ISOXMLReader();
    pRet->setMap(map);
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void ISOXMLReader::internalInit(const char* tmxFileName, const char* resourcePath)
{
    CCAssert(m_map!=NULL, "ISOXMLReader::internalInit must set map before reader");
    
    if (tmxFileName != NULL)
    {
        m_tMXFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        m_resources = resourcePath;
    }
    m_currentString = "";
        
}

bool ISOXMLReader::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool ISOXMLReader::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(m_tMXFileName.c_str());
}

bool ISOXMLReader::parseXMLString(const char *xmlString)
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

bool ISOXMLReader::parseXMLFile(const char *xmlFilename)
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
void ISOXMLReader::startElement(void *ctx, const char *name, const char **atts)
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
//        std::string orientationStr = valueForKey("orientation", attributeDict);
//        if ( orientationStr  == "isometric")
//            m_map->setOrientation(CCTMXOrientationIso);
//        else
//            CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", m_map->getOrientation());
        
        Size s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        m_map->setMapSize(s);
        
        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        m_map->setTileSize(s);
        
        // The parent element is now "map"
        m_currentElement=ISOPropertyMap;
        
    }
    else if(elementName == "tileset")
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            if (m_tMXFileName.find_last_of("/") != string::npos)
            {
                string dir = m_tMXFileName.substr(0, m_tMXFileName.find_last_of("/") + 1);
                externalTilesetFilename = dir + externalTilesetFilename;
            }
            else
            {
                externalTilesetFilename = m_resources + "/" + externalTilesetFilename;
            }
            externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathForFilename(externalTilesetFilename.c_str());
            
            this->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            ISOTileset *tileset = new ISOTileset();
            tileset->setName(valueForKey("name", attributeDict));
            tileset->setFirstGid((unsigned int)atoi(valueForKey("firstgid", attributeDict)));
            tileset->setTileSpacing((unsigned int)atoi(valueForKey("spacing", attributeDict)));
            tileset->setMargin((unsigned int)atoi(valueForKey("margin", attributeDict)));

            tileset->setTileWidth(atoi(valueForKey("tilewidth", attributeDict)));
            tileset->setTileHeight(atoi(valueForKey("tileheight", attributeDict)));
            
            m_map->getTilesetGroup()->addTileset(tileset);
            
            tileset->release();
        }
        m_currentElement=ISOPropertyTileset;
    }
    else if(elementName == "tile")
    {
        
        ISOTileset* tileset = (ISOTileset*) m_map->getTilesetGroup()->getTilesets()->lastObject();
        
        m_uCurrentGid= atoi(valueForKey("id", attributeDict));//+tileset->getFirstGid();
        
//        CCDictionary *dict = new CCDictionary();
//   
//        tileset->getTileProperties()->setObject(dict, m_uCurrentGid);
//        CC_SAFE_RELEASE(dict);
        
        ISOTile* tile=new ISOTile();
        tile->init(m_uCurrentGid, tileset);
        
        tileset->getTiles()->addObject(tile);
        tile->release();
        
        m_currentElement=ISOPropertyTile;
        
    }
    else if(elementName == "layer")
    {
        CCTMXLayerInfo *layer = new CCTMXLayerInfo();
        layer->m_name = valueForKey("name", attributeDict);
        
        Size s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        layer->m_layerSize = s;
        
        std::string visible = valueForKey("visible", attributeDict);
        layer->m_visible = !(visible == "0");
        
        std::string opacity = valueForKey("opacity", attributeDict);
        if( opacity != "" )
        {
            layer->m_opacity = (unsigned char)(255 * atof(opacity.c_str()));
        }
        else
        {
            layer->m_opacity = 255;
        }
        
        float x = (float)atof(valueForKey("x", attributeDict));
        float y = (float)atof(valueForKey("y", attributeDict));
        layer->m_offset = ccp(x,y);
        
        m_map->getTileLayers()->addObject(layer);
        layer->release();
        
        // The parent element is now "layer"
        m_currentElement=ISOPropertyLayer;
        
    }
    else if(elementName == "objectgroup")
    {
        ISOObjectGroup *objectGroup = new ISOObjectGroup();
        objectGroup->setName(valueForKey("name", attributeDict));
        Vec2 positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * m_map->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * m_map->getTileSize().height;
        objectGroup->setOffset(positionOffset);
        
        m_map->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();
        
        // The parent element is now "objectgroup"
        m_currentElement=ISOPropertyObjectGroup;
        
    }
    else if(elementName == "image")
    {
        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        
        if (m_tMXFileName.find_last_of("/") != string::npos)
        {
            string dir = m_tMXFileName.substr(0, m_tMXFileName.find_last_of("/") + 1);
            imagename=dir+imagename;
            
        }
        else
        {
            imagename=m_resources + (m_resources.size() ? "/" : "") + imagename;

        }
        
        //check width and height
        const char* widthValue = valueForKey("width", attributeDict);
        const char* heightValue = valueForKey("height", attributeDict);
        
        //use by tileset or tile
        if ( m_currentElement == ISOPropertyTileset ){

            ISOTileset* tileset = (ISOTileset*)m_map->getTilesetGroup()->getTilesets()->lastObject();
            
            tileset->setImageSource(imagename.c_str());
            
            if(widthValue && heightValue){
                Size s;
                s.width=(float)atof(widthValue);
                s.height=(float)atof(heightValue);
                tileset->setImageSize(s);
            }
            
        }else if(m_currentElement == ISOPropertyTile){
            ISOTileset* tileset = (ISOTileset*)m_map->getTilesetGroup()->getTilesets()->lastObject();
            ISOTile* tile=(ISOTile*)tileset->getTiles()->lastObject();
            
            CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(imagename.c_str());
            tile->setTexture(pTexture);
            
            CCRect rect;
            rect.origin=ccp(0, 0);
            
            if(widthValue && heightValue){
                
                //support origin 
                const char* originXValue = valueForKey("originX", attributeDict);
                const char* originYValue = valueForKey("originY", attributeDict);
                if(originXValue && originYValue){
                    rect.origin.x=(float)atof(originXValue);
                    rect.origin.y=(float)atof(originYValue);
                }
                
                rect.size.width=(float)atof(widthValue);
                rect.size.height=(float)atof(heightValue);
                
            }else{
                rect.size=pTexture->getContentSizeInPixels();
            }
            tile->setTextureRect(rect);
        }
    }
    else if(elementName == "data")
    {
        std::string encoding = valueForKey("encoding", attributeDict);
        std::string compression = valueForKey("compression", attributeDict);
        
        if( encoding == "base64" )
        {
            m_layerAttribs|=ISOLayerAttribBase64;
            m_storingCharacters=true;
            
            if( compression == "gzip" )
            {
                m_layerAttribs|=ISOLayerAttribGzip;
            } else
                if (compression == "zlib")
                {
                    m_layerAttribs|=ISOLayerAttribZlib;
                }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert( m_layerAttribs != ISOLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );
    }
    else if(elementName == "object")
    {

        ISOObjectGroup* objectGroup = (ISOObjectGroup*)m_map->getObjectGroups()->lastObject();
        
        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        ISOTileMapObject *obj = new ISOTileMapObject();
        
        obj->setName(valueForKey("name", attributeDict));
        
        obj->setType(valueForKey("type", attributeDict));
        
        Size s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        obj->setSize(s);
               
        // But X and Y since they need special treatment
        // X
        Vec2 pos;
        const char* value = valueForKey("x", attributeDict);
        if( value )
        {
            pos.x = (float)atof(value) + objectGroup->getOffset().x;
        }
        
        // Y
        value = valueForKey("y", attributeDict);
        if( value )  {
            float y = (float)atof(value) + objectGroup->getOffset().y;
            
            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            pos.y = (m_map->getMapSize().height * m_map->getTileSize().height) - y - s.height;
            
        }
        obj->setPosition(pos);
        
        // Add the object to the objectGroup
        objectGroup->getObjects()->addObject(obj);
        obj->release();
        
        // The parent element is now "object"
        m_currentElement=ISOPropertyObject;
        
    }
    else if(elementName == "property")
    {
        if ( m_currentElement == ISOPropertyNone )
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                  valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        }
        else if ( m_currentElement == ISOPropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            m_map->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_currentElement == ISOPropertyLayer )
        {
            // The parent element is the last layer
            ISOTileLayer* layer = (ISOTileLayer*)m_map->getTileLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layer->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_currentElement == ISOPropertyObjectGroup )
        {
            // The parent element is the last object group
            ISOObjectGroup* objectGroup = (ISOObjectGroup*)m_map->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            objectGroup->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_currentElement == ISOPropertyObject )
        {
            // The parent element is the last object
            ISOObjectGroup* objectGroup = (ISOObjectGroup*)m_map->getObjectGroups()->lastObject();
            ISOTileMapObject* obj = (ISOTileMapObject*)objectGroup->getObjects()->lastObject();
            
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            obj->getProperties()->setObject(value,key.c_str());
            value->release();
        }
        else if ( m_currentElement == ISOPropertyTile )
        {
            ISOTileset* tileset =(ISOTileset*)m_map->getTilesetGroup()->getTilesets()->lastObject();
//            CCDictionary* tileProperties=tileset->getTileProperties();
//            CCDictionary* dict = (CCDictionary*)tileProperties->objectForKey(m_uCurrentGid);
            
            ISOTile* tile=(ISOTile*)tileset->getTiles()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            tile->getProperties()->setObject(value, key.c_str());
            value->release();
        }
    }
    else if (elementName == "polygon")
    {
        // find parent object's dict and add polygon-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_objectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject(attributeDict objectForKey:@"points"] forKey:@"polygonPoints"];
        
    }
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_objectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject:[attributeDict objectForKey:@"points"] forKey:@"polylinePoints"];
    }
    
    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void ISOXMLReader::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    
    int len = 0;
    
    if(elementName == "data" && m_layerAttribs&ISOLayerAttribBase64)
    {
        m_storingCharacters=false;
        
        ISOTileLayer* layer = (ISOTileLayer*)m_map->getTileLayers()->lastObject();
        
        std::string currentString = this->getCurrentString();
        unsigned char *buffer;
        len = yhge::base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer )
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }
        
        if( m_layerAttribs & (ISOLayerAttribGzip | ISOLayerAttribZlib) )
        {
            unsigned char *deflated;
            Size s = layer->getLayerSize();
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
            
            layer->setTiles((unsigned int*) deflated);
        }
        else
        {
            layer->setTiles( (unsigned int*) buffer);
        }
        
        this->setCurrentString("");
        
    }
    else if (elementName == "map")
    {
        // The map element has ended
        m_currentElement=ISOPropertyNone;
    }
    else if (elementName == "tileset")
    {
        // The tileset element has ended
        m_currentElement=ISOPropertyNone;
    }
    else if (elementName == "layer")
    {
        // The layer element has ended
        m_currentElement=ISOPropertyNone;
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        m_currentElement=ISOPropertyNone;
    }
    else if (elementName == "object")
    {
        // The object element has ended
        m_currentElement=ISOPropertyNone;
    }
    else if (elementName == "tile")
    {
        // The tile element has ended
        m_currentElement=ISOPropertyNone;
    }
}

void ISOXMLReader::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    std::string pText((char*)ch,0,len);
    
    if (m_storingCharacters)
    {
        std::string currentString = this->getCurrentString();
        currentString += pText;
        this->setCurrentString(currentString.c_str());
    }
}

ISOTileMap* ISOXMLReader::getMap()
{
    return m_map;
}

void ISOXMLReader::setMap(ISOTileMap* map)
{
    m_map=map;
}


NS_CC_YHGE_ISOMETRIC_END
