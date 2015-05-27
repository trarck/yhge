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
    
    void removeChild(CCNode* node, bool cleanup);
    
    /**
     * 获取tile
     */
    
	virtual CCSprite* tileSpriteAt(const Vec2& pos);
    
    /**
     * 删除tile
     */
    void removeTileSpriteAt(const Vec2& pos);
    
public:
    
    void setTileset(ISOTileset* tileset);
    ISOTileset* getTileset();
    
    inline void setMinGID(unsigned int uMinGID)
    {
        _uMinGID = uMinGID;
    }
    
    inline unsigned int getMinGID()
    {
        return _uMinGID;
    }
    
    inline void setMaxGID(unsigned int uMaxGID)
    {
        _uMaxGID = uMaxGID;
    }
    
    inline unsigned int getMaxGID()
    {
        return _uMaxGID;
    }

protected:
   
    /**
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, Vec2 mapCoord, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    
    CCSprite* appendTileForGID(unsigned int gid, const Vec2& pos);
    CCSprite* insertTileForGID(unsigned int gid, const Vec2& pos);
    CCSprite* updateTileForGID(unsigned int gid, const Vec2& pos);
    
    unsigned int atlasIndexForExistantZ(unsigned int z);
    unsigned int atlasIndexForNewZ(int z);
    
    void addQuadFromSprite(CCSprite *sprite, unsigned int index);
    void addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag);
    
protected:

    //对于多个tileSet的支持。这样就不能使用batch node。所以最好一个layer使用一个tileSet
    ISOTileset* _tileset;
    
    CCSpriteBatchNode* _spriteBatchNode;
    
    unsigned int        _uMinGID;
    unsigned int        _uMaxGID;
       
    //! used for optimization
    CCSprite*           _reusedTile;
    yhge::ccCArray*           _atlasIndexArray;
    
    // used for retina display
    float               _contentScaleFactor;

};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_
