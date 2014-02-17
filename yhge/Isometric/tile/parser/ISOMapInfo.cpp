#include "ISOMapInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapInfo::ISOMapInfo()
:m_tMapSize(CCSizeZero)
,m_tTileSize(CCSizeZero)
,m_pLayers(NULL)
,m_pTilesets(NULL)
,m_pObjectGroups(NULL)
,m_pProperties(NULL)
{

}

ISOMapInfo::~ISOMapInfo()
{
    CCLOG("ISOMapInfo destroy");
    CC_SAFE_RELEASE(m_pTilesets);
    CC_SAFE_RELEASE(m_pLayers);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pObjectGroups);
}

bool ISOMapInfo::init()
{
    m_pTilesets = new CCArray();
    m_pTilesets->init();
    
    m_pLayers = new CCArray();
    m_pLayers->init();

    m_pObjectGroups = new CCArray();
    m_pObjectGroups->initWithCapacity(4);
    
    m_pProperties = new CCDictionary();

    return true;
}

void ISOMapInfo::setOrientation(int nOrientation)
{
    m_nOrientation = nOrientation;
}

int ISOMapInfo::getOrientation()
{
    return m_nOrientation;
}

void ISOMapInfo::setMapSize(const CCSize& tMapSize)
{
    m_tMapSize = tMapSize;
}

const CCSize& ISOMapInfo::getMapSize()
{
    return m_tMapSize;
}

void ISOMapInfo::setTileSize(const CCSize& tTileSize)
{
    m_tTileSize = tTileSize;
}

const CCSize& ISOMapInfo::getTileSize()
{
    return m_tTileSize;
}

void ISOMapInfo::setLayers(CCArray* pLayers)
{
    CC_SAFE_RETAIN(pLayers);
    CC_SAFE_RELEASE(m_pLayers);
    m_pLayers = pLayers;
}

CCArray* ISOMapInfo::getLayers()
{
    return m_pLayers;
}

void ISOMapInfo::setTilesets(CCArray* pTilesets)
{
    CC_SAFE_RETAIN(pTilesets);
    CC_SAFE_RELEASE(m_pTilesets);
    m_pTilesets = pTilesets;
}

CCArray* ISOMapInfo::getTilesets()
{
    return m_pTilesets;
}

/**
 * keep same for tmx
 */
void ISOMapInfo::setObjectGroups(CCArray* pObjectGroups)
{
    CC_SAFE_RETAIN(pObjectGroups);
    CC_SAFE_RELEASE(m_pObjectGroups);
    m_pObjectGroups = pObjectGroups;
}

CCArray* ISOMapInfo::getObjectGroups()
{
    return m_pObjectGroups;
}

void ISOMapInfo::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* ISOMapInfo::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_ISOMETRIC_END
