#include "ISOLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "ISOMap.h"

NS_CC_YHGE_BEGIN

ISOLayer::ISOLayer()
:m_sLayerName("")
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_tOffset(CCPointZero)
,m_pProperties(NULL)
,m_cOpacity(255)
,m_pMap(NULL)
,m_uLayerOrientation(0)
,m_layerType(kEmptyLayer)
{
	
}

ISOLayer::~ISOLayer()
{
    CC_SAFE_RELEASE_NULL(m_pProperties);
}

bool ISOLayer::init()
{
    m_pProperties=new CCDictionary();
    
	return true;
}

bool ISOLayer::init(CCSize& mapTileSize)
{
    if(init()){
        m_tMapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool ISOLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(init(mapTileSize)){
        m_tOffset=offset;
        return true;
    }
    return false;
}


void ISOLayer::initOffset(const CCPoint& tOffset)
{
	this->setOffset(tOffset);
}

void ISOLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}


void ISOLayer::setupLayer()
{

}

void ISOLayer::releaseLayer()
{

}

void ISOLayer::scroll(const CCPoint& tOffset)
{
//    CCLOG("ISOLayer::scroll");
}

void ISOLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

/**
 * 地图的缩放值
 */
void ISOLayer::onMapScaleChange(float orignalScale,float newScale)
{
    
}

/**
 * 获取属性名称
 */
CCString* ISOLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void ISOLayer::parseInternalProperties()
{

}

void ISOLayer::setMap(ISOMap* pMap)
{
    m_pMap = pMap;
}

NS_CC_YHGE_END
