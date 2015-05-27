#include "ISOLayer.h"
#include "ISOMap.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayer::ISOLayer()
:_layerName("")
,_layerSize(CCSizeZero)
,_mapTileSize(CCSizeZero)
,_offset(CCPointZero)
,_properties(NULL)
,_opacity(255)
,_map(NULL)
,_uLayerOrientation(0)
,_layerType(kEmptyLayer)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
{
	
}

ISOLayer::~ISOLayer()
{
    CC_SAFE_RELEASE_NULL(_properties);
}

bool ISOLayer::init()
{
    _properties=new CCDictionary();
    
	return true;
}

bool ISOLayer::init(Size& mapTileSize)
{
    if(init()){
        _mapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool ISOLayer::init(Size& mapTileSize,Vec2& offset)
{
    if(init(mapTileSize)){
        _offset=offset;
        return true;
    }
    return false;
}


void ISOLayer::inioffset(const Vec2& offset)
{
	this->setOffset(offset);
}

void ISOLayer::inioffset(float x,float y)
{
	this->inioffset(ccp(x,y));
}


void ISOLayer::setupLayer()
{

}

void ISOLayer::releaseLayer()
{

}

void ISOLayer::scroll(const Vec2& offset)
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

int  ISOLayer::zOrderForPos(const Vec2& pos)
{
    return (int)(_layerSize.width*_layerSize.height -(pos.x + pos.y * _layerSize.width));
}

int ISOLayer::vertexZForPos(const Vec2& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        maxVal = (unsigned int)(_layerSize.width + _layerSize.height);
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
Value ISOLayer::getProperty(const std::string& propertyName)
{
	if (_properties.find(propertyName) != _properties.end())
		return _properties.at(propertyName);

	return Value::Null;
}

void ISOLayer::parseInternalProperties()
{

}

void ISOLayer::setMap(ISOMap* map)
{
    _map = map;
}

NS_CC_YHGE_ISOMETRIC_END
