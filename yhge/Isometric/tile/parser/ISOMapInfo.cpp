#include "ISOMapInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapInfo::ISOMapInfo()
:_tMapSize(CCSizeZero)
,_tTileSize(CCSizeZero)
,_pLayers(NULL)
,_pTilesets(NULL)
,_pObjectGroups(NULL)
,_properties(NULL)
{

}

ISOMapInfo::~ISOMapInfo()
{
    CCLOG("ISOMapInfo destroy");
    CC_SAFE_RELEASE(_pTilesets);
    CC_SAFE_RELEASE(_pLayers);
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_pObjectGroups);
}

bool ISOMapInfo::init()
{
    _pTilesets = new CCArray();
    _pTilesets->init();
    
    _pLayers = new CCArray();
    _pLayers->init();

    _pObjectGroups = new CCArray();
    _pObjectGroups->initWithCapacity(4);
    
    _properties = new CCDictionary();

    return true;
}

void ISOMapInfo::setOrientation(int nOrientation)
{
    _nOrientation = nOrientation;
}

int ISOMapInfo::getOrientation()
{
    return _nOrientation;
}

void ISOMapInfo::setMapSize(const Size& tMapSize)
{
    _tMapSize = tMapSize;
}

const Size& ISOMapInfo::getMapSize()
{
    return _tMapSize;
}

void ISOMapInfo::setTileSize(const Size& tTileSize)
{
    _tTileSize = tTileSize;
}

const Size& ISOMapInfo::getTileSize()
{
    return _tTileSize;
}

void ISOMapInfo::setLayers(CCArray* pLayers)
{
    CC_SAFE_RETAIN(pLayers);
    CC_SAFE_RELEASE(_pLayers);
    _pLayers = pLayers;
}

CCArray* ISOMapInfo::getLayers()
{
    return _pLayers;
}

void ISOMapInfo::setTilesets(CCArray* pTilesets)
{
    CC_SAFE_RETAIN(pTilesets);
    CC_SAFE_RELEASE(_pTilesets);
    _pTilesets = pTilesets;
}

CCArray* ISOMapInfo::getTilesets()
{
    return _pTilesets;
}

/**
 * keep same for tmx
 */
void ISOMapInfo::setObjectGroups(CCArray* pObjectGroups)
{
    CC_SAFE_RETAIN(pObjectGroups);
    CC_SAFE_RELEASE(_pObjectGroups);
    _pObjectGroups = pObjectGroups;
}

CCArray* ISOMapInfo::getObjectGroups()
{
    return _pObjectGroups;
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
