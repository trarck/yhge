#include "ISOLayer.h"
#include "ISOMap.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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
,m_vertexZvalue(0)
,m_useAutomaticVertexZ(false)
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

int  ISOLayer::zOrderForPos(const CCPoint& pos)
{
    return (int)(m_tLayerSize.width*m_tLayerSize.height -(pos.x + pos.y * m_tLayerSize.width));
}

int ISOLayer::vertexZForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (m_useAutomaticVertexZ)
    {
        maxVal = (unsigned int)(m_tLayerSize.width + m_tLayerSize.height);
        ret = (int)(-(maxVal - (pos.x + pos.y)));
    }
    else
    {
        ret = m_vertexZvalue;
    }
    
    return ret;
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

NS_CC_YHGE_ISOMETRIC_END
