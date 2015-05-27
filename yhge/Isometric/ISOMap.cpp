#include "ISOMap.h"
#include "ISOLayer.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static const int kCoordLineZOrder=10000;

ISOMap::ISOMap()
:_mapSize(Vec2(0,0))
,_visibleSize(Size(0,0))
,_nIdentifier(0)
,_nMapOrientation(0)
,_pName("")
, _tileSize(Size(0, 0))
,_activeLayer(NULL)
{
	
}

ISOMap::~ISOMap()
{
    CC_SAFE_RELEASE_NULL(_activeLayer);
}

ISOMap * ISOMap::createWithXMLFile(const char *xmlFile)
{
    ISOMap *pRet = new ISOMap();
    if (pRet->initWithXMLFile(xmlFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOMap * ISOMap::createWithJSONFile(const char *jsonFile)
{
    ISOMap *pRet = new ISOMap();
    if (pRet->initWithJSONFile(jsonFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOMap* ISOMap::createWithXML(const char* tmxString, const char* resourcePath)
{
    ISOMap *pRet = new ISOMap();
    if (pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOMap* ISOMap::createWithJSON(const char* jsonString, const char* resourcePath)
{
    ISOMap *pRet = new ISOMap();
    if (pRet->initWithJSON(jsonString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ISOMap::init()
{
    
    _properties=new CCDictionary();
    _layers=new CCArray();
    
    _visibleSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);

	return true;
}

bool ISOMap::initWithXMLFile(const char *xmlFile)
{
    CCAssert(xmlFile != NULL && strlen(xmlFile)>0, "ISOMap: map file should not bi NULL");
    
    setContentSize(CCSizeZero);
    
//    ISOXMLParser *xmlParser = ISOXMLParser::formatWithXMLFile(xmlFile);
//    
//    ISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    if (! mapInfo)
//    {
//        return false;
//    }
//    CCAssert( mapInfo->getTilesets()->count() != 0, "ISOMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool ISOMap::initWithJSONFile(const char *jsonFile)
{
    CCAssert( false, "ISOMap::initWithJSONFile not support.");
    
    return true;
}

bool ISOMap::initWithXML(const char* xmlString, const char* resourcePath)
{
    setContentSize(CCSizeZero);
        
//    ISOXMLParser *xmlParser = ISOXMLParser::formatWithXML(xmlString, resourcePath);
//    ISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    CCAssert( mapInfo->getTilesets()->count() != 0, "ISOMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool ISOMap::initWithJSON(const char* jsonString, const char* resourcePath)
{
    CCAssert( false, "ISOMap::initWithJSON not support.");
    
    return true;
}

ISOLayer * ISOMap::layerNamed(const std::string& layerName)
{
    CCAssert(layerName!="", "Invalid layer name!");
    
    if (_layers && _layers->count()>0){
        
        Ref* pObj = NULL;
        ISOLayer* layer =NULL;
        
        CCARRAY_FOREACH(_layers, pObj)
        {
            layer = dynamic_cast<ISOLayer*>(pObj);
            if(layer)
            {
                if(layerName==layer->getLayerName())
                {
                    return layer;
                }
            }
        }
    }
    
    // layer not found
    return NULL;
}

Value ISOMap::getProperty(const std::string& propertyName)
{
	if (_properties.find(propertyName) != _properties.end())
		return _properties.at(propertyName);

	return Value::Null;
}

void ISOMap::scrollLayer(const Vec2& pos)
{
	Vec2 localPos=ccpMult(pos, 1/this->getScale());

    Ref* pObj=NULL;
    ISOLayer* layer=NULL;

    CCARRAY_FOREACH(_layers, pObj){
        layer=(ISOLayer*) pObj;
        layer->scroll(localPos);
    }
}

/**
 * 显示地图的坐标线
 */
void ISOMap::showCoordLine()
{
    
}

/**
 *检查某个单元是否可以通过
 */
bool ISOMap::isWorkable(int x,int y)
{
    //根据具体地图类型来实现。比如用某个层来标识路径情况。
    //如果地图上可移动物体是不能穿透，则也要算在路径里。
    return true;
}


Size ISOMap::getVisibleSize()
{
    if(_fScaleX==0 || _fScaleY==0) return _visibleSize;
    
    return CCSizeMake(_visibleSize.width/_fScaleX, _visibleSize.height/_fScaleY);
}

void ISOMap::setActiveLayer(ISOLayer* activeLayer)
{
    CC_SAFE_RETAIN(activeLayer);
    CC_SAFE_RELEASE(_activeLayer);
    _activeLayer = activeLayer;
}

NS_CC_YHGE_ISOMETRIC_END
