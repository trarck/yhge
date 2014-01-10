#include "ISOTileLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../base/ISOTileset.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOTileLayer::ISOTileLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_tOffset(CCPointZero)
,m_pProperties(NULL)
,m_sLayerName("")
,m_pTiles(NULL)
,m_bUseAutomaticVertexZ(false)
,m_nVertexZvalue(0)
{
	
}

ISOTileLayer::~ISOTileLayer()
{
    CC_SAFE_RELEASE(m_pProperties);
    if(m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

bool ISOTileLayer::init()
{
    m_pProperties=new CCDictionary();
    
	return true;
}

bool ISOTileLayer::init(CCSize& mapTileSize)
{
    if(init()){
        m_tMapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool ISOTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(init(mapTileSize)){
        m_tOffset=offset;
        return true;
    }
    return false;
}


void ISOTileLayer::initOffset(const CCPoint& tOffset)
{
//    this->setPosition(tOffset);
	this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
}

void ISOTileLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

ISOTileLayer* ISOTileLayer::create()
{
    ISOTileLayer* pRet=new ISOTileLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

void ISOTileLayer::releaseLayer()
{
    if (m_pTiles)
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

void ISOTileLayer::setupTiles()
{
    CCAssert(false, "you must impl ISOTileLayer::setupTiles");
}

void ISOTileLayer::addTileAt(float x,float y)
{
    addTileAt(ccp(x,y));
}

void ISOTileLayer::addTileAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl ISOTileLayer::addTileAt");
}

/**
 * 获取tile
 */
ISOTile* ISOTileLayer::tileAt(float x,float y)
{
    return tileAt(ccp(x,y));
}


ISOTile* ISOTileLayer::tileAt(const CCPoint& pos)
{
    ISOTile* tile=NULL;
    unsigned int gid=tileGIDAt(pos);
    
    if(gid>0){
        ISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
        tile=tileset->tileForGid(gid);
    }
    
    return tile;
}

void ISOTileLayer::removeTileAt(float x,float y)
{
    removeTileAt(ccp(x,y));
}

void ISOTileLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::removeTileAt: invalid position");
    
    int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
    m_pTiles[idx]=0;
}

unsigned int ISOTileLayer::tileGIDAt(float x,float y)
{
    return tileGIDAt(ccp(x,y));
}

unsigned int ISOTileLayer::tileGIDAt(const CCPoint& pos)
{
    if(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0){
        int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
        unsigned int gid = m_pTiles[idx];
        
        return gid;
    }
    return 0;
}


//TODO 
void ISOTileLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::setTileGID: invalid position");
    int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
    m_pTiles[idx]=gid;
}

void ISOTileLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid,ccp(x,y));
}

void ISOTileLayer::scroll(const CCPoint& tOffset)
{
//    CCLOG("ISOTileLayer::scroll");
}

void ISOTileLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

void ISOTileLayer::parseInternalProperties()
{
    CCLOG("ISOTileLayer::parseInternalProperties");
    // if cc_vertex=automatic, then tiles will be rendered using vertexz
    
    CCString *vertexz = propertyNamed("cc_vertexz");
    if (vertexz)
    {
        // If "automatic" is on, then parse the "cc_alpha_func" too
        if (vertexz->m_sString == "automatic")
        {
            m_bUseAutomaticVertexZ = true;
            CCString *alphaFuncVal = propertyNamed("cc_alpha_func");
            float alphaFuncValue = 0.0f;
            if (alphaFuncVal != NULL)
            {
                alphaFuncValue = alphaFuncVal->floatValue();
            }
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));
            
            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformAlphaTestValue);
            
            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
        }
        else
        {
            m_nVertexZvalue = vertexz->intValue();
        }
    }
}

unsigned int  ISOTileLayer::indexForPos(const CCPoint& pos)
{
    unsigned int index=(unsigned int)(pos.x + pos.y * m_tLayerSize.width);
    return index;
}

int  ISOTileLayer::zOrderForPos(const CCPoint& pos)
{
    int ret=(int)(m_tLayerSize.width*m_tLayerSize.height -(pos.x + pos.y * m_tLayerSize.width));
    return ret;
}

int ISOTileLayer::vertexZForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (m_bUseAutomaticVertexZ)
    {
        maxVal = (unsigned int)(m_tLayerSize.width + m_tLayerSize.height);
        ret = (int)(-(maxVal - (pos.x + pos.y)));
    }
    else
    {
        ret = m_nVertexZvalue;
    }
    
    return ret;
}

unsigned int ISOTileLayer::zOrderToIndex(int z)
{
	return (unsigned int)(m_tLayerSize.width*m_tLayerSize.height-z);
}

CCString* ISOTileLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}


void ISOTileLayer::setLayerSize(const CCSize& tLayerSize)
{
    m_tLayerSize = tLayerSize;
}

CCSize ISOTileLayer::getLayerSize()
{
    return m_tLayerSize;
}


void ISOTileLayer::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void ISOTileLayer::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint ISOTileLayer::getOffset()
{
    return m_tOffset;
}

void ISOTileLayer::setMapTileSize(float width,float height)
{
    m_tMapTileSize.width=width;
    m_tMapTileSize.height=height;
}

void ISOTileLayer::setMapTileSize(const CCSize& tMapTileSize)
{
    m_tMapTileSize = tMapTileSize;
}

const CCSize& ISOTileLayer::getMapTileSize()
{
    return m_tMapTileSize;
}


void ISOTileLayer::setLayerOrientation(unsigned int uLayerOrientation)
{
    m_uLayerOrientation = uLayerOrientation;
}

unsigned int ISOTileLayer::getLayerOrientation()
{
    return m_uLayerOrientation;
}

void ISOTileLayer::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* ISOTileLayer::getProperties()
{
    return m_pProperties;
}

void ISOTileLayer::setTiles(unsigned int* pTiles)
{
    m_pTiles = pTiles;
}

unsigned int* ISOTileLayer::getTiles()
{
    return m_pTiles;
}

//===============tile sprite===============

/**
 * 获取tile
 */
CCSprite* ISOTileLayer::tileSpriteAt(float x,float y)
{
    return tileSpriteAt(ccp(x,y));
}

CCSprite* ISOTileLayer::tileSpriteAt(const CCPoint& pos)
{
    CCSprite* sprite=NULL;
    
    ISOTile* tile=tileAt(pos);
    if(tile){
        sprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    }
    
    return sprite;
}

/**
 * 删除tile
 */
void ISOTileLayer::removeTileSpriteAt(float x,float y)
{
    removeTileSpriteAt(ccp(x,y));
}

void ISOTileLayer::removeTileSpriteAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl ISOTileLayer::removeSpriteTileAt");
}
NS_CC_YHGE_END
