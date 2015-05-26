﻿#ifndef YHGE_ISOMETRIC_ISOGROUNDTILELAYER_H_
#define YHGE_ISOMETRIC_ISOGROUNDTILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "../ISOInfos.h"
#include "ISOTileLayer.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 直接把tile当做子元素进行渲染，没有进行任何优化。
 */
class ISOGroundTileLayer : public ISOTileLayer {

public:
	
	ISOGroundTileLayer();
    
	~ISOGroundTileLayer(void);

    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    /**
     * 获取tile
     */
    
	virtual CCSprite* tileSpriteAt(const Vec2& pos);
    
    /**
     * 删除tile
     */
    virtual void removeTileSpriteAt(const Vec2& pos);

public:
        
    void setTileSet(ISOTilesetInfo* pTileSet);
    ISOTilesetInfo* getTileSet();
    
    void setTileSets(CCArray* pTileSets);
    CCArray* getTileSets();


protected:
    
    /**
     * 添加tile
     */
	CCSprite* appendTile(unsigned int gid, const Vec2& pos);
    CCSprite* appendTile(unsigned int gid, float x,float y);
    
    /**
     * 插入tile
     */
    CCSprite* insertTile(unsigned int gid, const Vec2& pos);
    CCSprite* insertTile(unsigned int gid, float x,float y);
    
    /**
     * 更新tile
     */
    CCSprite* updateTile(unsigned int gid, const Vec2& pos);
    CCSprite* updateTile(unsigned int gid, float x,float y);
    
   
    /**
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, Vec2 mapCoord, unsigned int gid);
    
    CCSprite* appendTileForGID(unsigned int gid, const Vec2& pos);
    CCSprite* insertTileForGID(unsigned int gid, const Vec2& pos);
    CCSprite* updateTileForGID(unsigned int gid, const Vec2& pos);
    
protected:

};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOGROUNDTILELAYER_H_
