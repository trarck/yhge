#include "ISOMapInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapInfo::ISOMapInfo()
:_mapSize(CCSizeZero)
,_tileSize(CCSizeZero)
,_layers(NULL)
,_tilesets(NULL)
,_objectGroups(NULL)
,_properties(NULL)
{

}

ISOMapInfo::~ISOMapInfo()
{
    CCLOG("ISOMapInfo destroy");
    CC_SAFE_RELEASE(_tilesets);
    CC_SAFE_RELEASE(_layers);
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_objectGroups);
}

bool ISOMapInfo::init()
{
    _tilesets = new CCArray();
    _tilesets->init();
    
    _layers = new CCArray();
    _layers->init();

    _objectGroups = new CCArray();
    _objectGroups->initWithCapacity(4);
    
    _properties = new CCDictionary();

    return true;
}

void ISOMapInfo::setOrientation(int orientation)
{
    _orientation = orientation;
}

int ISOMapInfo::getOrientation()
{
    return _orientation;
}

void ISOMapInfo::semapSize(const Size& mapSize)
{
    _mapSize = mapSize;
}

const Size& ISOMapInfo::gemapSize()
{
    return _mapSize;
}

void ISOMapInfo::setileSize(const Size& tileSize)
{
    _tileSize = tileSize;
}

const Size& ISOMapInfo::getileSize()
{
    return _tileSize;
}

void ISOMapInfo::setLayers(CCArray* layers)
{
    CC_SAFE_RETAIN(layers);
    CC_SAFE_RELEASE(_layers);
    _layers = layers;
}

CCArray* ISOMapInfo::getLayers()
{
    return _layers;
}

void ISOMapInfo::setTilesets(CCArray* tilesets)
{
    CC_SAFE_RETAIN(tilesets);
    CC_SAFE_RELEASE(_tilesets);
    _tilesets = tilesets;
}

CCArray* ISOMapInfo::getTilesets()
{
    return _tilesets;
}

/**
 * keep same for tmx
 */
void ISOMapInfo::setObjectGroups(CCArray* objectGroups)
{
    CC_SAFE_RETAIN(objectGroups);
    CC_SAFE_RELEASE(_objectGroups);
    _objectGroups = objectGroups;
}

CCArray* ISOMapInfo::getObjectGroups()
{
    return _objectGroups;
}

void ISOMapInfo::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties = pProperties;
}

CCDictionary* ISOMapInfo::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
