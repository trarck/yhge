#include "ISOMap.h"
#include "ISOLayer.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static const int kCoordLineZOrder=10000;

ISOMap::ISOMap()
:m_tMapSize(CCSizeZero)
,m_visibleSize(CCSizeZero)
,m_nIdentifier(0)
,m_nMapOrientation(0)
,m_pName("")
,m_tTileSize(CCSizeZero)
,m_pProperties(NULL)
,m_layers(NULL)
,m_activeLayer(NULL)
{
	
}

ISOMap::~ISOMap()
{
    CC_SAFE_RELEASE_NULL(m_pProperties);
    CC_SAFE_RELEASE_NULL(m_layers);
    CC_SAFE_RELEASE_NULL(m_activeLayer);
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
    
    m_pProperties=new CCDictionary();
    m_layers=new CCArray();
    
    m_visibleSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);

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
    
    if (m_layers && m_layers->count()>0){
        
        Ref* pObj = NULL;
        ISOLayer* layer =NULL;
        
        CCARRAY_FOREACH(m_layers, pObj)
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

CCString* ISOMap::propertyNamed(const std::string& propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void ISOMap::scrollLayer(const CCPoint& pos)
{
	CCPoint localPos=ccpMult(pos, 1/this->getScale());

    Ref* pObj=NULL;
    ISOLayer* layer=NULL;

    CCARRAY_FOREACH(m_layers, pObj){
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


CCSize ISOMap::getVisibleSize()
{
    if(m_fScaleX==0 || m_fScaleY==0) return m_visibleSize;
    
    return CCSizeMake(m_visibleSize.width/m_fScaleX, m_visibleSize.height/m_fScaleY);
}

void ISOMap::setActiveLayer(ISOLayer* activeLayer)
{
    CC_SAFE_RETAIN(activeLayer);
    CC_SAFE_RELEASE(m_activeLayer);
    m_activeLayer = activeLayer;
}

NS_CC_YHGE_ISOMETRIC_END
