#ifndef YHGE_ISOMETRIC_ISOTILELAYER_H_
#define YHGE_ISOMETRIC_ISOTILELAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "ISOTile.h"

NS_CC_YHGE_BEGIN

class ISOTileMap;

/**
 * tile layer 图块图层。
 * 没有复杂的游戏逻辑，通常只做显示。
 * 只显示图形，覆盖整个地图坐标。
 * 坐为背景层或地表层，主要是静态的物体。
 */

class ISOTileLayer : public CCNode {

public:
	
	ISOTileLayer();
    
	virtual ~ISOTileLayer(void);
	
    virtual bool init();
        
    virtual bool init(CCSize& mapTileSize);
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);
    
    static ISOTileLayer* create();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();

    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    
    virtual void initOffset(float x,float y);
    
    /**
     * 添加tile
     */
	virtual void addTileAt(float x,float y);
    
	virtual void addTileAt(const CCPoint& pos);
    
    /**
     * 获取tile
     */
	virtual ISOTile* tileAt(float x,float y);
    
	virtual ISOTile* tileAt(const CCPoint& pos);
    
    /**
     * 删除tile
     */    
	virtual void removeTileAt(float x,float y);
    
    virtual void removeTileAt(const CCPoint& pos);
    
    
    /**
     * 获取tile gid
     */
    unsigned int  tileGIDAt(float x,float y);
    
    unsigned int  tileGIDAt(const CCPoint& pos);
    
    /**
     * 设置tile gid
     */
    virtual void setTileGID(unsigned int gid, float x,float y);
    virtual void setTileGID(unsigned int gid, const CCPoint& pos);

    
    
    //===============tile sprite===============
    
    /**
     * 添加tile
     */
//    virtual void addTileSprite(CCSprite* tileSprite);
//    
//    virtual void addTileSpriteAt(CCSprite* tileSprite,float x,float y);
//    
//	virtual void addTileSpriteAt(CCSprite* tileSprite,const CCPoint& pos);
    
    
    /**
     * 获取tile sprite
     */
	virtual CCSprite* tileSpriteAt(float x,float y);
    
	virtual CCSprite* tileSpriteAt(const CCPoint& pos);
    
    /**
     * 删除tile sprite
     */   
	virtual void removeTileSpriteAt(float x,float y);
    
    virtual void removeTileSpriteAt(const CCPoint& pos);
    
 
    //移动
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
    
	/**
     * 地图格子对应到数组
     */
    unsigned int indexForPos(const CCPoint& pos);

    /**
     * 取得zOrder值，处理遮挡使用.zOrder vertexZ二者使用一
     */
    int zOrderForPos(const CCPoint& pos);
    
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
	unsigned int zOrderToIndex(int z);
    /**
     * 获取属性名称
     */
    CCString *propertyNamed(const char *propertyName);

public:
    //===================get set 属性====================//
    
	virtual void setLayerSize(const CCSize& tLayerSize);
    
	virtual CCSize getLayerSize();

    virtual void setMapTileSize(const CCSize& tMapTileSize);
    
    virtual void setMapTileSize(float width,float height);
    
    virtual const CCSize& getMapTileSize();

	virtual void setOffset(const CCPoint& tOffset);
    
	virtual void setOffset(float x,float y);
    
	virtual CCPoint getOffset();
    
    inline const char* getLayerName(){ return m_sLayerName.c_str(); }
    
    inline void setLayerName(const char *layerName){ m_sLayerName = layerName; }
       
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setLayerOrientation(unsigned int uLayerOrientation);
    
    virtual unsigned int getLayerOrientation();
    
    virtual void setTiles(unsigned int* pTiles);
    
    virtual unsigned int* getTiles();
    
    inline void setOpacity(unsigned char cOpacity)
    {
        m_cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return m_cOpacity;
    }
    
    inline void setMap(ISOTileMap* pMap)
    {
        m_pMap = pMap;
    }
    
    inline ISOTileMap* getMap()
    {
        return m_pMap;
    }
    
protected:
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
    
protected:
    
    /**
     * 层的名称
     */
    std::string m_sLayerName;
    
    /**
     * 层的地图大小
     */
	CCSize m_tLayerSize;
    
    /**
      地图的一个图块大小
     */
    CCSize m_tMapTileSize;
    
    unsigned int* m_pTiles;
    
    CCArray* m_pTilesetInfos;
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint m_tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int m_iStartX;
	int m_iStartY;
    
    /**
     * 地图属性
     */
    CCDictionary* m_pProperties;
       
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int m_uLayerOrientation;
    
    //! Layer supports opacity
    unsigned char       m_cOpacity;
    
    //! Only used when vertexZ is used
    int                 m_nVertexZvalue;
    
    bool                m_bUseAutomaticVertexZ;
        
    // used for retina display
    float               m_fContentScaleFactor;

    ISOTileMap* m_pMap;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILELAYER_H_
