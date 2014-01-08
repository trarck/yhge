#include "ISOGroundTileLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../ISOTileMap.h"

NS_CC_YHGE_BEGIN

// ISOGroundTileLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}


ISOGroundTileLayer::ISOGroundTileLayer()
{
	
}

ISOGroundTileLayer::~ISOGroundTileLayer()
{

}

//bool ISOGroundTileLayer::init(ISOTileMap *pMap)
//{
//    setMap(pMap);
//    return true;
//}

void ISOGroundTileLayer::setupTiles()
{
    CCLOG("setupTiles");
    // Parse cocos2d properties
    this->parseInternalProperties();
    
    for (unsigned int y=0; y < m_tLayerSize.height; y++)
    {
        for (unsigned int x=0; x < m_tLayerSize.width; x++)
        {
            unsigned int pos = (unsigned int)(x + m_tLayerSize.width * y);
            unsigned int gid = m_pTiles[ pos ];
            
            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/
            
            // XXX: gid == 0 --> empty tile
            if (gid != 0)
            {
                //需要转换
                CCPoint pos;
                pos.x=x;
                pos.y=y;
//                pos.x=m_tLayerSize.height-y;
//                pos.y=m_tLayerSize.width-x;
                this->appendTileForGID(gid, pos);
                
            }
        }
    }
}

void ISOGroundTileLayer::setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid)
{
    sprite->setPosition(isoGameToViewPoint(mapCoord));
    sprite->setVertexZ((float)this->vertexZForPos(mapCoord));
    sprite->setAnchorPoint(CCPointZero);
    sprite->setOpacity(m_cOpacity);
    sprite->setFlipX(false);
    sprite->setFlipX(false);
    sprite->setRotation(0.0f);
    sprite->setAnchorPoint(ccp(0,0));
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kCCTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(ccp(0.5f,0.5f));
        CCPoint viewPos=isoGameToViewPoint(mapCoord);
        sprite->setPosition(ccp(viewPos.x + sprite->getContentSize().height/2,
                                viewPos.y + sprite->getContentSize().width/2 ) );
        
        unsigned int flag = gid & (kCCTMXTileHorizontalFlag | kCCTMXTileVerticalFlag );
        
        // handle the 4 diagonally flipped states.
        if (flag == kCCTMXTileHorizontalFlag)
        {
            sprite->setRotation(90.0f);
        }
        else if (flag == kCCTMXTileVerticalFlag)
        {
            sprite->setRotation(270.0f);
        }
        else if (flag == (kCCTMXTileVerticalFlag | kCCTMXTileHorizontalFlag) )
        {
            sprite->setRotation(90.0f);
            sprite->setFlipX(true);
        }
        else
        {
            sprite->setRotation(270.0f);
            sprite->setFlipX(true);
        }
    }
    else
    {
        if (gid & kCCTMXTileHorizontalFlag)
        {
            sprite->setFlipX(true);
        }
        
        if (gid & kCCTMXTileVerticalFlag)
        {
            sprite->setFlipY(true);
        }
    }
}


CCSprite * ISOGroundTileLayer::tileSpriteAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer: invalid position");
    
    CCSprite *tile = NULL;
    unsigned int gid = this->tileGIDAt(pos);
    
    // if GID == 0, then no tile is present
    if (gid)
    {
        int z = (int)(pos.x + pos.y * m_tLayerSize.width);
        tile = (CCSprite*) this->getChildByTag(z);
        
        // tile not created yet. create it
        if (! tile)
        {
            ISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
            tile = tileset->tileSpriteForGid(gid);
            tile->setPosition(isoGameToViewPoint(pos));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(CCPointZero);
            tile->setOpacity(m_cOpacity);
            
            this->addChild(tile,-z,z);
        }
    }
    
    return tile;
}

void ISOGroundTileLayer::removeSpriteTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    
    unsigned int gid = tileGIDAt(pos);
    
    if (gid)
    {
        int z = (int)(pos.x + pos.y * m_tLayerSize.width);
        
        // remove tile from GID map
        m_pTiles[z] = 0;
        removeChildByTag(z, true);
        
    }
}

// ISOGroundTileLayer - adding helper methods
CCSprite * ISOGroundTileLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
{
    ISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    CCSprite *tile = tileset->tileSpriteForGid(gid);
    
    int z = (int)(pos.x + pos.y * m_tLayerSize.width);
    
    setupTileSprite(tile, pos, gid);
    
    addChild(tile,-z,z);
    return tile;
}

CCSprite * ISOGroundTileLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)
{
    int z = (int)(pos.x + pos.y * m_tLayerSize.width);

    this->removeChildByTag(z, true);
  
    ISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    CCSprite *newTile = tileset->tileSpriteForGid(gid);
    
    setupTileSprite(newTile ,pos ,gid);

    addChild(newTile,-z,z);
    
    m_pTiles[z] = gid;
    
    return newTile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
CCSprite * ISOGroundTileLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
{
//    CCLOG("appendTileForGID[%s]:%d,%f,%f,z:%.9lf",m_sLayerName.c_str(),gid,pos.x,pos.y,this->vertexZForPos(pos));

    int z = (int)(pos.x + pos.y * m_tLayerSize.width);
    
    ISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
   
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    setupTileSprite(tileSprite ,pos ,gid);
    this->addChild(tileSprite,-z,z);
    
    return tileSprite;
}
NS_CC_YHGE_END
