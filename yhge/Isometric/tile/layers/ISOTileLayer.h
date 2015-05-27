#ifndef YHGE_ISOMETRIC_ISOTILELAYER_H_
#define YHGE_ISOMETRIC_ISOTILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/Isometric/ISOLayer.h>
#include "../base/ISOTile.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileMap;

/**
 * tile layer 图块图层。
 * 没有复杂的游戏逻辑，通常只做显示。
 * 只显示图形，覆盖整个地图坐标。
 * 坐为背景层或地表层，主要是静态的物体。
 */

class ISOTileLayer : public ISOLayer {

public:
	
	ISOTileLayer();
    
	virtual ~ISOTileLayer(void);
	
//    virtual bool init();
//        
//    virtual bool init(Size& mapTileSize);
//    
//    virtual bool init(Size& mapTileSize,Vec2& offset);
    
    static ISOTileLayer* create();
    
    /**
     * 初始化偏移
     */
	virtual void initOffset(const Vec2& tOffset);
    
    virtual void initOffset(float x,float y);
    
    /**
     * 初始化显示
     */
    virtual void setupLayer();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    
    
    /**
     * 初始化显示tiles
     */
    virtual void setutiles();
    
    /**
     * 添加tile
     */
	virtual void addTileAt(float x,float y);
    
	virtual void addTileAt(const Vec2& pos);
    
    /**
     * 获取tile
     */
	virtual ISOTile* tileAt(float x,float y);
    
	virtual ISOTile* tileAt(const Vec2& pos);
    
    /**
     * 删除tile
     */    
	virtual void removeTileAt(float x,float y);
    
    virtual void removeTileAt(const Vec2& pos);
    
    
    /**
     * 获取tile gid
     */
    unsigned int  tileGIDAt(float x,float y);
    
    unsigned int  tileGIDAt(const Vec2& pos);
    
    /**
     * 设置tile gid
     */
    virtual void setTileGID(unsigned int gid, float x,float y);
    virtual void setTileGID(unsigned int gid, const Vec2& pos);
    
 
    /**
     * 移动到某个偏移量
     * 注意不是scroll by
     * layer的scroll不要设置layer的position，如果layer的position改变，地图会乱掉。
     * layer的scroll主要提供地图位置改变的通知。
     */
    virtual void scroll(const Vec2& tOffset);
    virtual void scroll(float x,float y);
    
    /**
     * 地图的缩放值
     */
    virtual void onMapScaleChange(float orignalScale,float newScale);
    
	/**
     * 地图格子对应到数组
     */
    unsigned int indexForPos(const Vec2& pos);
    
	unsigned int zOrderToIndex(int z);
    
    
    //===============tile sprite tools function===============
    /**
     * 获取tile sprite
     */
	virtual CCSprite* tileSpriteAt(float x,float y);
    
	virtual CCSprite* tileSpriteAt(const Vec2& pos);
    
    /**
     * 删除tile sprite
     * 从地图数据中删除gid，并从渲染树中删除
     * 一般不会使用
     */
	virtual void removeTileSpriteAt(float x,float y);
    
    virtual void removeTileSpriteAt(const Vec2& pos);
    

public:
    //===================get set 属性====================//
    
    virtual void setTiles(unsigned int* tiles);
    
    virtual unsigned int* getTiles();
    
    virtual void setMap(ISOMap* pMap);
    
protected:
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
    
protected:
    
    unsigned int* _tiles;

    /**
     * 偏移量的地图坐标
     */
	int _startX;
	int _startY;
    
    ISOTileMap* _tileMap;

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILELAYER_H_
