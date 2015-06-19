#include "ISOBatchTileLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include <yhge/Isometric/tile/base/ISOTileset.h>



NS_CC_YHGE_ISOMETRIC_BEGIN

// ISOBatchTileLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}


ISOBatchTileLayer::ISOBatchTileLayer()
:_tileset(NULL)
,_reusedTile(NULL)
,_spriteBatchNode(NULL)
,_atlasIndexArray(NULL)
,_contentScaleFactor(1.0f)
,_maxGID(0)
,_minGID(0)
{
	
}

ISOBatchTileLayer::~ISOBatchTileLayer()
{
    CC_SAFE_RELEASE(_tileset);
    CC_SAFE_RELEASE(_reusedTile);
    CC_SAFE_RELEASE(_spriteBatchNode);
    if (_atlasIndexArray)
    {
        yhge::ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = NULL;
    }
}

bool ISOBatchTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        _minGID = 100000;
        _maxGID = 0;
        
        return true;
    }
    
    return false;
}

void ISOBatchTileLayer::setutiles()
{
    // XXX: is 35% a good estimate ?
    float totalNumberOfTiles = _layerSize.width * _layerSize.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?
    
    Texture2D *texture = _tileset->getTexture();
    

    CCAssert(texture, "Texture is null");

	_spriteBatchNode = SpriteBatchNode::createWithTexture(texture, (unsigned int)capacity);//new SpriteBatchNode();
	_spriteBatchNode->retain();

	_atlasIndexArray = yhge::ccCArrayNew((unsigned int)totalNumberOfTiles);

	this->setContentSize(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height));

    _spriteBatchNode->getTextureAtlas()->getTexture()->setAliasTexParameters();
 
    // Parse cocos2d properties
    this->parseInternalProperties();

    for (unsigned int y=0; y < _layerSize.height; y++)
    {
        for (unsigned int x=0; x < _layerSize.width; x++)
        {
            unsigned int tileIndex = indexForPos(ccp(x,y));
            unsigned int gid = _tiles[ tileIndex ];
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
                _minGID = MIN(gid, _minGID);
                _maxGID = MAX(gid, _maxGID);
            }
        }
    }
    
    CCAssert( _maxGID >= _tileset->getFirstGid() &&
             _minGID >= _tileset->getFirstGid(), "TMX: Only 1 tileset per layer is supported");
    
    addChild(_spriteBatchNode);
}

void ISOBatchTileLayer::setupTileSprite(Sprite* sprite, Vec2 mapCoord, unsigned int gid)
{
    sprite->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(mapCoord)));
    sprite->setVertexZ((float)this->vertexZForPos(mapCoord));
    sprite->setAnchorPoint(ccp(0.5f,0.0f));
    sprite->setOpacity(_opacity);
    
    sprite->setFlipX(false);
    sprite->setFlipX(false);
    sprite->setRotation(0.0f);
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kCCTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(ccp(0.5f,0.5f));
        Vec2 viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(mapCoord));
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

Sprite* ISOBatchTileLayer::reusedTileWithRect(const Rect& rect)
{
    if (! _reusedTile)
    {
		_reusedTile = Sprite::createWithTexture(_spriteBatchNode->getTextureAtlas()->getTexture(), rect, false);//new Sprite();
        //_reusedTile->initWithTexture(_spriteBatchNode->getTextureAtlas()->getTexture(), rect, false);
		_reusedTile->retain();
        _reusedTile->setBatchNode(_spriteBatchNode);
    }
    else
    {
		_reusedTile->setBatchNode(nullptr);

		// Re-init the sprite
		_reusedTile->setTextureRect(rect, false, rect.size);

		// restore the batch node
		_reusedTile->setBatchNode(_spriteBatchNode);
    }
    
    return _reusedTile;
}


CCSprite * ISOBatchTileLayer::tileSpriteAt(const Vec2& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "ISOTileLayer: the tiles map has been released");
    
    Sprite *tile = NULL;
    unsigned int gid = this->tileGIDAt(pos);
    
    // if GID == 0, then no tile is present
    if (gid)
    {
        int z = zOrderForPos(pos);
        tile = (Sprite*) this->getChildByTag(z);
        
        // tile not created yet. create it
        if (! tile)
        {
            Rect rect = _tileset->rectForGid(gid);
            
			tile = Sprite::createWithTexture(_spriteBatchNode->getTexture(), rect);
            //tile->retain();
            tile->setBatchNode(_spriteBatchNode);
            tile->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(pos)));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(Vec2::ZERO);
            tile->setOpacity(_opacity);
            
            unsigned int indexForZ = this->atlasIndexForExistantZ(z);
            this->addSpriteWithoutQuad(tile, indexForZ, z);
            //tile->release();
        }
    }
    
    return tile;
}


// ISOBatchTileLayer - adding helper methods
Sprite * ISOBatchTileLayer::insertTileForGID(unsigned int gid, const Vec2& pos)
{
    Rect rect = _tileset->rectForGid(gid);
    
	int z=zOrderForPos(pos);
    
    Sprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile, pos, gid);
    
    // get atlas index
    unsigned int indexForZ = this->atlasIndexForNewZ(z);
    
    // Optimization: add the quad without adding a child
    this->addQuadFromSprite(tile, indexForZ);
    
    // insert it into the local atlasindex array
    yhge::ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);
    
    // update possible children
	Vector<Node*> children = _spriteBatchNode->getChildren();

	for (Vector<Node*>::iterator iter = children.begin(); iter != children.end();++iter){
		Sprite* child = (Sprite*)(*iter);
		if (child)
		{
			unsigned int ai = child->getAtlasIndex();
			if (ai >= indexForZ)
			{
				child->setAtlasIndex(ai + 1);
			}
		}
	}

	int tileIndex = indexForPos(pos);
    _tiles[tileIndex] = gid;
    return tile;
}

Sprite * ISOBatchTileLayer::updateTileForGID(unsigned int gid, const Vec2& pos)
{
    Rect rect = _tileset->rectForGid(gid);
    rect = CCRectMake(rect.origin.x / _contentScaleFactor, rect.origin.y / _contentScaleFactor, rect.size.width/ _contentScaleFactor, rect.size.height/ _contentScaleFactor);
    
	int z = zOrderForPos(pos);
    
    Sprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // get atlas index
    unsigned int indexForZ = atlasIndexForExistantZ(z);
    tile->setAtlasIndex(indexForZ);
    tile->setDirty(true);
    tile->updateTransform();

	int tileIndex = indexForPos(pos);
    _tiles[tileIndex] = gid;
    
    return tile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
Sprite * ISOBatchTileLayer::appendTileForGID(unsigned int gid, const Vec2& pos)
{
    Rect rect = _tileset->rectForGid(gid);
    
    int z = zOrderForPos(pos);
    
    Sprite *tile = reusedTileWithRect(rect);
    
    setupTileSprite(tile ,pos ,gid);
    
    // optimization:
    // The difference between appendTileForGID and insertTileforGID is that append is faster, since
    // it appends the tile at the end of the texture atlas
    unsigned int indexForZ = _atlasIndexArray->num;
    
    // don't add it using the "standard" way.
    addQuadFromSprite(tile, indexForZ);
    
    // append should be after addQuadFromSprite since it modifies the quantity values
    yhge::ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);
    
    return tile;
}

void ISOBatchTileLayer::removeTileSpriteAt(const Vec2& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");
    
    unsigned int gid = tileGIDAt(pos);
    
    if (gid)
    {
        int z = zOrderForPos(pos);
        unsigned int atlasIndex = atlasIndexForExistantZ(z);
        
		unsigned int tileIndex=indexForPos(pos);
        // remove tile from GID map
        _tiles[tileIndex] = 0;
        
        // remove tile from atlas position array
        yhge::ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);
        
        // remove it from sprites and/or texture atlas
        Sprite *sprite = (Sprite*)getChildByTag(z);
        if (sprite)
        {
            _spriteBatchNode->removeChild(sprite, true);
        }
        else
        {
            _spriteBatchNode->getTextureAtlas()->removeQuadAtIndex(atlasIndex);
            
            // update possible children
			Vector<Node*> children = _spriteBatchNode->getChildren();

			for (Vector<Node*>::iterator iter = children.begin(); iter != children.end(); ++iter){
                Sprite* pChild = (Sprite*) (*iter);
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

unsigned int ISOBatchTileLayer::atlasIndexForExistantZ(unsigned int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&_atlasIndexArray->arr[0], _atlasIndexArray->num, sizeof(void*), compareInts);
    
    CCAssert(item, "TMX atlas index not found. Shall not happen");
    
    int index = ((size_t)item - (size_t)_atlasIndexArray->arr) / sizeof(void*);
    return index;
}
unsigned int ISOBatchTileLayer::atlasIndexForNewZ(int z)
{
    // XXX: This can be improved with a sort of binary search
    unsigned int i=0;
    for (i=0; i< _atlasIndexArray->num ; i++)
    {
        int val = (size_t) _atlasIndexArray->arr[i];
        if (z < val)
        {
            break;
        }
    }
    
    return i;
}

void ISOBatchTileLayer::setTileGID(unsigned int gid, const Vec2& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");
    CCAssert(gid == 0 || gid >= _tileset->getFirstGid(), "TMXLayer: invalid gid" );
    
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
            Sprite *sprite = (Sprite*)_spriteBatchNode->getChildByTag(z);
            if (sprite)
            {
                Rect rect = _tileset->rectForGid(gid);
                
                sprite->setTextureRect(rect, false, rect.size);

                setupTileSprite(sprite, sprite->getPosition(), gid);

                _tiles[tileIndex] = gid;
            }
            else
            {
                updateTileForGID(gid, pos);
            }
        }
    }
}


void ISOBatchTileLayer::removeChild(Node* node, bool cleanup)
{
    Sprite *sprite = (Sprite*)node;
    // allows removing nil objects
    if (! sprite)
    {
        return;
    }
    
    CCAssert(_spriteBatchNode->getChildren()->containsObject(sprite), "Tile does not belong to TMXLayer");
    
    unsigned int atlasIndex = sprite->getAtlasIndex();
    int z = (size_t)_atlasIndexArray->arr[atlasIndex];
	unsigned int tileIndex=zOrderToIndex(z);
    _tiles[tileIndex] = 0;
    yhge::ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);
    _spriteBatchNode->removeChild(sprite, cleanup);
}

void ISOBatchTileLayer::addQuadFromSprite(Sprite *sprite, unsigned int index)
{
    CCAssert( sprite != NULL, "Argument must be non-NULL");
    CCAssert( dynamic_cast<Sprite*>(sprite), "CCSpriteBatchNode only supports CCSprites as children");
    
    TextureAtlas* pobTextureAtlas=_spriteBatchNode->getTextureAtlas();
    
    while(index >= pobTextureAtlas->getCapacity() || pobTextureAtlas->getCapacity() == pobTextureAtlas->getTotalQuads())
    {
        _spriteBatchNode->increaseAtlasCapacity();
    }
    //
    // update the quad directly. Don't add the sprite to the scene graph
    //
    sprite->setBatchNode(_spriteBatchNode);
    sprite->setAtlasIndex(index);
    
    ccV3F_C4B_T2F_Quad quad = sprite->getQuad();
    pobTextureAtlas->insertQuad(&quad, index);
    
    // XXX: updateTransform will update the textureAtlas too using updateQuad.
    // XXX: so, it should be AFTER the insertQuad
    sprite->setDirty(true);
    sprite->updateTransform();
}


void ISOBatchTileLayer::addSpriteWithoutQuad(Sprite*child, unsigned int z, int aTag)
{
	_spriteBatchNode->addSpriteWithoutQuad(child, z, aTag);
}


void ISOBatchTileLayer::setTileset(ISOTileset* tileset)
{
    CC_SAFE_RETAIN(tileset);
    CC_SAFE_RELEASE(_tileset);
    _tileset = tileset;
}

ISOTileset* ISOBatchTileLayer::getTileset()
{
    return _tileset;
}

NS_CC_YHGE_ISOMETRIC_END
