#include "ISOMapInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapInfo::ISOMapInfo()
:_mapSize(CCSizeZero)
,_tileSize(CCSizeZero)
{

}

ISOMapInfo::~ISOMapInfo()
{
    CCLOG("ISOMapInfo destroy");
}

bool ISOMapInfo::init()
{

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

void ISOMapInfo::setTileSize(const Size& tileSize)
{
    _tileSize = tileSize;
}

const Size& ISOMapInfo::getTileSize()
{
    return _tileSize;
}

void ISOMapInfo::setLayers(const ISOLayerInfoVector& layers)
{
    _layers = layers;
}

ISOMapInfo::ISOLayerInfoVector& ISOMapInfo::getLayers()
{
    return _layers;
}

void ISOMapInfo::setTilesets(const ISOTilesetInfoVector& tilesets)
{
    _tilesets = tilesets;
}

ISOMapInfo::ISOTilesetInfoVector& ISOMapInfo::getTilesets()
{
    return _tilesets;
}

/**
 * keep same for tmx
 */
void ISOMapInfo::setObjectGroups(const ISOObjectGroupInfoVector& objectGroups)
{
    _objectGroups = objectGroups;
}

ISOMapInfo::ISOObjectGroupInfoVector& ISOMapInfo::getObjectGroups()
{
    return _objectGroups;
}

void ISOMapInfo::setProperties(const ValueMap& properties)
{
    _properties = properties;
}

ValueMap& ISOMapInfo::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
