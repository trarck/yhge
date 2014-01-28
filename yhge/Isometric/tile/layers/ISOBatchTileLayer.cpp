#include "ISOBatchTileLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include <yhge/Isometric/ISOStaticCoordinate.h>
#include <yhge/Isometric/tile/base/ISOTileset.h>



NS_CC_YHGE_BEGIN

// ISOBatchTileLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}


ISOBatchTileLayer::ISOBatchTileLayer()
:m_pTileset(NULL)
,m_pReusedTile(NULL)
,m_pSpriteBatchNode(NULL)
,m_pAtlasIndexArray(NULL)
,m_fContentScaleFactor(1.0f)
,m_uMaxGID(0)
,m_uMinGID(0)
{
	
}

ISOBatchTileLayer::~ISOBatchTileLayer()
{
    CC_SAFE_RELEASE(m_pTileset);
    CC_SAFE_RELEASE(m_pReusedTile);
    CC_SAFE_RELEASE(m_pSpriteBatchNode);
    if (m_pAtlasIndexArray)
    {
        yhge::ccCArrayFree(m_pAtlasIndexArray);
        m_pAtlasIndexArray = NULL;
    }
}

bool ISOBatchTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        m_uMinGID = 100000;
        m_uMaxGID = 0;
        
        return true;
    }
    
    return false;
}

void ISOBatchTileLayer::setupTiles()
{
    // XXX: is 35% a good estimate ?
    float totalNumberOfTiles = m_tLayerSize.width * m_tLayerSize.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?
    
    CCTexture2D *texture = m_pTileset->getTexture();
    

    CCAssert(texture, "Texture is null");

    m_pSpriteBatchNode=new CCSpriteBatchNode();
    
    if (m_pSpriteBatchNode->initWithTexture(texture, (unsigned int)capacity))
    {               
        m_pAtlasIndexArray = yhge::ccCArrayNew((unsigned int)totalNumberOfTiles);
        
        this->setContentSize(CCSizeMake(m_tLayerSize.width * m_tMapTileSize.width, m_tLayerSize.height * m_tMapTileSize.height));
    }

    m_pSpriteBatchNode->getTextureAtlas()->getTexture()->setAliasTexParameters();
 
    // Parse cocos2d properties
    this->parseInternalProperties();

    for (unsigned int y=0; y < m_tLayerSize.height; y++)
    {
        for (unsigned int x=0; x < m_tLayerSize.width; x++)
        {
            unsigned int tileIndex = indexForPos(ccp(x,y));
            unsigned int gid = m_pTiles[ tileIndex ];
            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/
            
            // XXX: gid == 0 --> empty tile
            if (gid != 0)
            {
                this->insertTileForGID(gid, ccp(x, y));
                
                // Optimization: update min and max GID rendered by the layer
                m_uMinGID = MIN(gid, m_uMinGID);
                m_uMaxGID = MAX(gid, m_uMaxGID);
            }
        }
    }
    
    CCAssert( m_uMaxGID >= m_pTileset->getFirstGid() &&
             m_uMinGID >= m_pTileset->getFirstGid(), "TMX: Only 1 tileset per layer is supported");
    
    addChild(m_pSpriteBatchNode);
}

void ISOBatchTileLayer::setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid)
{
    sprite->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(mapCoord)));
    sprite->setVertexZ((float)this->vertexZForPos(mapCoord));
    sprite->setAnchorPoint(ccp(0.5f,0.0f));
    sprite->setOpacity(m_cOpacity);
    
    sprite->setFlipX(false);
    sprite->setFlipX(false);
    sprite->setRotation(0.0f);
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kCCTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(ccp(0.5f,0.5f));
        CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(mapCoord));
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

CCSprite* ISOBatchTileLayer::reusedTileWithRect(CCRect rect)
{
    if (! m_pReusedTile)
    {
        m_pReusedTile = new CCSprite();
        m_pReusedTile->initWithTexture(m_pSpriteBatchNode->getTextureAtlas()->getTexture(), rect, false);
        m_pReusedTile->setBatchNode(m_pSpriteBatchNode);
    }
    else
    {
        // XXX: should not be re-init. Potential memory leak. Not following best practices
        // XXX: it shall call directory  [setRect:rect]
        m_pReusedTile->initWithTexture(m_pSpriteBatchNode->getTextureAtlas()->getTexture(), rect, false);
        
        // Since initWithTexture resets the batchNode, we need to re add it.
        // but should be removed once initWithTexture is not called again
        m_pReusedTile->setBatchNode(m_pSpriteBatchNode);
    }
    
    return m_pReusedTile;
}


CCSprite * ISOBatchTileLayer::tileSpriteAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "ISOTileLayer: the tiles map has been released");
    
    CCSprite *tile = NULL;
    unsigned int gid = this->tileGIDAt(pos);
    
    // if GID == 0, then no tile is present
    if (gid)
    {
        int z = zOrderForPos(pos);
        tile = (CCSprite*) this->getChildByTag(z);
        
        // tile not created yet. create it
        if (! tile)
        {
            CCRect rect = m_pTileset->rectForGid(gid);
            
            tile = new CCSprite();
            tile->initWithTexture(m_pSpriteBatchNode->getTexture(), rect);
            tile->setBatchNode(m_pSpriteBatchNode);
            tile->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(pos)));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(CCPointZero);
            tile->setOpacity(m_cOpacity);
            
            unsigned int indexForZ = this->atlasIndexForExistantZ(z);
            this->addSpriteWithoutQuad(tile, indexForZ, z);
            tile->release();
        }
    }
    
    return tile;
}


// ISOBatchTileLayer - adding helper methods
CCSprite * ISOBatchTileLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileset->rectForGid(gid);
    
	int z=zOrderForPos(pos);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile, pos, gid);
    
    // get atlas index
    unsigned int indexForZ = this->atlasIndexForNewZ(z);
    
    // Optimization: add the quad without adding a child
    this->addQuadFromSprite(tile, indexForZ);
    
    // insert it into the local atlasindex array
    yhge::ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);
    
    // update possible children
    CCArray* pChildren=m_pSpriteBatchNode->getChildren();
    if (pChildren && pChildren->count()>0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(pChildren, pObject)
        {
            CCSprite* pChild = (CCSprite*) pObject;
            if (pChild)
            {
                unsigned int ai = pChild->getAtlasIndex();
                if ( ai >= indexForZ )
                {
                    pChild->setAtlasIndex(ai+1);
                }
            }
        }
    }
	int tileIndex = indexForPos(pos);
    m_pTiles[tileIndex] = gid;
    return tile;
}

CCSprite * ISOBatchTileLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileset->rectForGid(gid);
    rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);
    
	int z = zOrderForPos(pos);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // get atlas index
    unsigned int indexForZ = atlasIndexForExistantZ(z);
    tile->setAtlasIndex(indexForZ);
    tile->setDirty(true);
    tile->updateTransform();

	int tileIndex = indexForPos(pos);
    m_pTiles[tileIndex] = gid;
    
    return tile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
CCSprite * ISOBatchTileLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = m_pTileset->rectForGid(gid);
    
    int z = zOrderForPos(pos);
    
    CCSprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // optimization:
    // The difference between appendTileForGID and insertTileforGID is that append is faster, since
    // it appends the tile at the end of the texture atlas
    unsigned int indexForZ = m_pAtlasIndexArray->num;
    
    // don't add it using the "standard" way.
    addQuadFromSprite(tile, indexForZ);
    
    // append should be after addQuadFromSprite since it modifies the quantity values
    yhge::ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);
    
    return tile;
}

void ISOBatchTileLayer::removeTileSpriteAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
    
    unsigned int gid = tileGIDAt(pos);
    
    if (gid)
    {
        int z = zOrderForPos(pos);
        unsigned int atlasIndex = atlasIndexForExistantZ(z);
        
		unsigned int tileIndex=indexForPos(pos);
        // remove tile from GID map
        m_pTiles[tileIndex] = 0;
        
        // remove tile from atlas position array
        yhge::ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);
        
        // remove it from sprites and/or texture atlas
        CCSprite *sprite = (CCSprite*)getChildByTag(z);
        if (sprite)
        {
            m_pSpriteBatchNode->removeChild(sprite, true);
        }
        else
        {
            m_pSpriteBatchNode->getTextureAtlas()->removeQuadAtIndex(atlasIndex);
            
            // update possible children
            CCArray* pChildren=m_pSpriteBatchNode->getChildren();
            if (pChildren && pChildren->count()>0)
            {
                CCObject* pObject = NULL;
                CCARRAY_FOREACH(pChildren, pObject)
                {
                    CCSprite* pChild = (CCSprite*) pObject;
                    if (pChild)
                    {
                        unsigned int ai = pChild->getAtlasIndex();
                        if ( ai >= atlasIndex )
                        {
                            pChild->setAtlasIndex(ai-1);
                        }
                    }
                }
            }
        }
    }
}

unsigned int ISOBatchTileLayer::atlasIndexForExistantZ(unsigned int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&m_pAtlasIndexArray->arr[0], m_pAtlasIndexArray->num, sizeof(void*), compareInts);
    
    CCAssert(item, "TMX atlas index not found. Shall not happen");
    
    int index = ((size_t)item - (size_t)m_pAtlasIndexArray->arr) / sizeof(void*);
    return index;
}
unsigned int ISOBatchTileLayer::atlasIndexForNewZ(int z)
{
    // XXX: This can be improved with a sort of binary search
    unsigned int i=0;
    for (i=0; i< m_pAtlasIndexArray->num ; i++)
    {
        int val = (size_t) m_pAtlasIndexArray->arr[i];
        if (z < val)
        {
            break;
        }
    }
    
    return i;
}

void ISOBatchTileLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
    CCAssert(gid == 0 || gid >= m_pTileset->getFirstGid(), "TMXLayer: invalid gid" );
    
    unsigned int currentGID = tileGIDAt(pos);
    
    if (currentGID != gid )
    {
        
        // setting gid=0 is equal to remove the tile
        if (gid == 0)
        {
            removeTileAt(pos);
        }
        // empty tile. create a new one
        else if (currentGID == 0)
        {
            insertTileForGID(gid,pos);
        }
        // modifying an existing tile with a non-empty tile
        else
        {
            unsigned int tileIndex = indexForPos(pos);
            int z=zOrderForPos(pos);
            CCSprite *sprite = (CCSprite*)m_pSpriteBatchNode->getChildByTag(z);
            if (sprite)
            {
                CCRect rect = m_pTileset->rectForGid(gid);
                
                sprite->setTextureRect(rect, false, rect.size);

                setupTileSprite(sprite, sprite->getPosition(), gid);

                m_pTiles[tileIndex] = gid;
            }
            else
            {
                updateTileForGID(gid, pos);
            }
        }
    }
}


void ISOBatchTileLayer::removeChild(CCNode* node, bool cleanup)
{
    CCSprite *sprite = (CCSprite*)node;
    // allows removing nil objects
    if (! sprite)
    {
        return;
    }
    
    CCAssert(m_pSpriteBatchNode->getChildren()->containsObject(sprite), "Tile does not belong to TMXLayer");
    
    unsigned int atlasIndex = sprite->getAtlasIndex();
    int z = (size_t)m_pAtlasIndexArray->arr[atlasIndex];
	unsigned int tileIndex=zOrderToIndex(z);
    m_pTiles[tileIndex] = 0;
    yhge::ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);
    m_pSpriteBatchNode->removeChild(sprite, cleanup);
}

void ISOBatchTileLayer::addQuadFromSprite(CCSprite *sprite, unsigned int index)
{
    CCAssert( sprite != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(sprite), "CCSpriteBatchNode only supports CCSprites as children");
    
    CCTextureAtlas* pobTextureAtlas=m_pSpriteBatchNode->getTextureAtlas();
    
    while(index >= pobTextureAtlas->getCapacity() || pobTextureAtlas->getCapacity() == pobTextureAtlas->getTotalQuads())
    {
        m_pSpriteBatchNode->increaseAtlasCapacity();
    }
    //
    // update the quad directly. Don't add the sprite to the scene graph
    //
    sprite->setBatchNode(m_pSpriteBatchNode);
    sprite->setAtlasIndex(index);
    
    ccV3F_C4B_T2F_Quad quad = sprite->getQuad();
    pobTextureAtlas->insertQuad(&quad, index);
    
    // XXX: updateTransform will update the textureAtlas too using updateQuad.
    // XXX: so, it should be AFTER the insertQuad
    sprite->setDirty(true);
    sprite->updateTransform();
}


void ISOBatchTileLayer::addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag)
{
    CCAssert( child != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<CCSprite*>(child), "CCSpriteBatchNode only supports CCSprites as children");
    
    // quad index is Z
    child->setAtlasIndex(z);
    
    // XXX: optimize with a binary search
    int i=0;
    
    CCArray* pobDescendants=m_pSpriteBatchNode->getDescendants();
    
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pobDescendants, pObject)
    {
        CCSprite* pChild = (CCSprite*) pObject;
        if (pChild && (pChild->getAtlasIndex() >= z))
        {
            ++i;
        }
    }
    
    pobDescendants->insertObject(child, i);
    
    // IMPORTANT: Call super, and not self. Avoid adding it to the texture atlas array
    m_pSpriteBatchNode->addChild(child, z, aTag);
    //#issue 1262 don't use lazy sorting, tiles are added as quads not as sprites, so sprites need to be added in order
    m_pSpriteBatchNode->reorderBatch(false);
}


void ISOBatchTileLayer::setTileset(ISOTileset* pTileset)
{
    CC_SAFE_RETAIN(pTileset);
    CC_SAFE_RELEASE(m_pTileset);
    m_pTileset = pTileset;
}

ISOTileset* ISOBatchTileLayer::getTileset()
{
    return m_pTileset;
}

NS_CC_YHGE_END
