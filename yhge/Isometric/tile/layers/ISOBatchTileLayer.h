#ifndef YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_
#define YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/CocosExt/Support/ccCArray.h>
#include "../ISOInfos.h"
#include "ISOTileLayer.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 使用batch node来渲染layer.(TMX的渲染方式)
 * 一个layer只有一个tileset,tileset只有一个拼图。
 * 暂不支持多个tileset
 */
class ISOBatchTileLayer : public ISOTileLayer {

public:
	
	ISOBatchTileLayer();
    
	~ISOBatchTileLayer(void);

    bool init();
    /**
     * 初始化显示tiles
     */
    virtual void setutiles();
    
    void setTileGID(unsigned int gid, const Vec2& pos);
    
    void removeChild(Node* node, bool cleanup);
    
    /**
     * 获取tile
     */
    
	virtual Sprite* tileSpriteAt(const Vec2& pos);
    
    /**
     * 删除tile
     */
    void removeTileSpriteAt(const Vec2& pos);
    
public:
    
    void setTileset(ISOTileset* tileset);
    ISOTileset* getTileset();
    
    inline void setMinGID(unsigned int minGID)
    {
        _minGID = minGID;
    }
    
    inline unsigned int getMinGID()
    {
        return _minGID;
    }
    
    inline void setMaxGID(unsigned int maxGID)
    {
        _maxGID = maxGID;
    }
    
    inline unsigned int getMaxGID()
    {
        return _maxGID;
    }

protected:
   
    /**
     * 设置tile
     */
    void setupTileSprite(Sprite* sprite, Vec2 mapCoord, unsigned int gid);
    Sprite* reusedTileWithRect(const Rect& rect);
    
    Sprite* appendTileForGID(unsigned int gid, const Vec2& pos);
    Sprite* insertTileForGID(unsigned int gid, const Vec2& pos);
    Sprite* updateTileForGID(unsigned int gid, const Vec2& pos);
    
    unsigned int atlasIndexForExistantZ(unsigned int z);
    unsigned int atlasIndexForNewZ(int z);
    
    void addQuadFromSprite(Sprite *sprite, unsigned int index);
    void addSpriteWithoutQuad(Sprite*child, unsigned int z, int aTag);
    
protected:

    //对于多个tileSet的支持。这样就不能使用batch node。所以最好一个layer使用一个tileSet
    ISOTileset* _tileset;
    
    SpriteBatchNode* _spriteBatchNode;
    
    unsigned int        _minGID;
    unsigned int        _maxGID;
       
    //! used for optimization
    Sprite*           _reusedTile;
    yhge::ccCArray*           _atlasIndexArray;
    
    // used for retina display
    float               _contentScaleFactor;

};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_
