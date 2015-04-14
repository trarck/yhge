#include "ISOLayer.h"
#include "ISOMap.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayer::ISOLayer()
:_sLayerName("")
,_tLayerSize(CCSizeZero)
,_tMapTileSize(CCSizeZero)
,_tOffset(CCPointZero)
,_pProperties(NULL)
,_cOpacity(255)
,_pMap(NULL)
,_uLayerOrientation(0)
,_layerType(kEmptyLayer)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
{
	
}

ISOLayer::~ISOLayer()
{
    CC_SAFE_RELEASE_NULL(_pProperties);
}

bool ISOLayer::init()
{
    _pProperties=new CCDictionary();
    
	return true;
}

bool ISOLayer::init(CCSize& mapTileSize)
{
    if(init()){
        _tMapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool ISOLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(init(mapTileSize)){
        _tOffset=offset;
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
    return (int)(_tLayerSize.width*_tLayerSize.height -(pos.x + pos.y * _tLayerSize.width));
}

int ISOLayer::vertexZForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        maxVal = (unsigned int)(_tLayerSize.width + _tLayerSize.height);
        ret = (int)(-(maxVal - (pos.x + pos.y)));
    }
    else
    {
        ret = _vertexZvalue;
    }
    
    return ret;
}

/**
 * 获取属性名称
 */
CCString* ISOLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)_pProperties->objectForKey(propertyName);
}

void ISOLayer::parseInternalProperties()
{

}

void ISOLayer::setMap(ISOMap* pMap)
{
    _pMap = pMap;
}

NS_CC_YHGE_ISOMETRIC_END
