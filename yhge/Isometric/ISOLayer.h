#ifndef YHGE_ISOMETRIC_ISOLAYER_H_
#define YHGE_ISOMETRIC_ISOLAYER_H_

#include "cocos2d.h"
#include "IsometricMacros.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOMap;

class ISOLayer : public CCNode {

public:
	
	ISOLayer();
    
	virtual ~ISOLayer(void);
	
    virtual bool init();
        
    virtual bool init(CCSize& mapTileSize);
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);
    
    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    
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
     * 移动到某个偏移量
     * 注意不是scroll by
     * layer的scroll不要设置layer的position，如果layer的position改变，地图会乱掉。
     * layer的scroll主要提供地图位置改变的通知。
     */
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
    
    /**
     * 地图的缩放值
     */
    virtual void onMapScaleChange(float orignalScale,float newScale);

    
    /**
     * 取得zOrder值，处理遮挡使用.zOrder vertexZ二者使用一
     */
    int zOrderForPos(const CCPoint& pos);
    
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
	/**
     * 获取属性名称
     */
    CCString *propertyNamed(const char *propertyName);

public:
    
    enum LayerType
    {
        kEmptyLayer=0,
        kTileLayer=1,
        kObjectLayer=2,
        kImageLayer=3
    };
    
    //===================get set 属性====================//
	inline void setLayerSize(const CCSize& tLayerSize)
	{
		m_tLayerSize = tLayerSize;
	}

	inline CCSize getLayerSize()
	{
		return m_tLayerSize;
	}


	inline void setOffset(const CCPoint& tOffset)
	{
		m_tOffset = tOffset;
	}

	inline void setOffset(float x,float y)
	{
		m_tOffset.x=x;
		m_tOffset.y=y;
	}

	inline CCPoint getOffset()
	{
		return m_tOffset;
	}

	inline void setMapTileSize(float width,float height)
	{
		m_tMapTileSize.width=width;
		m_tMapTileSize.height=height;
	}

	inline void setMapTileSize(const CCSize& tMapTileSize)
	{
		m_tMapTileSize = tMapTileSize;
	}

	inline const CCSize& getMapTileSize()
	{
		return m_tMapTileSize;
	}


	inline void setLayerOrientation(unsigned int uLayerOrientation)
	{
		m_uLayerOrientation = uLayerOrientation;
	}

	inline unsigned int getLayerOrientation()
	{
		return m_uLayerOrientation;
	}

	inline void setProperties(CCDictionary* pProperties)
	{
		CC_SAFE_RETAIN(pProperties);
		CC_SAFE_RELEASE(m_pProperties);
		m_pProperties = pProperties;
	}

	inline CCDictionary* getProperties()
	{
		return m_pProperties;
	}
    
    inline const std::string& getLayerName(){ return m_sLayerName; }
    
    inline void setLayerName(const std::string& layerName){ m_sLayerName = layerName; }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        m_cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return m_cOpacity;
    }
    
    virtual void setMap(ISOMap* pMap);
    
    inline ISOMap* getMap()
    {
        return m_pMap;
    }
    
    inline void setLayerType(LayerType layerType)
    {
        m_layerType = layerType;
    }
    
    inline LayerType getLayerType()
    {
        return m_layerType;
    }
    
    inline void setVertexZvalue(int vertexZvalue)
    {
        m_vertexZvalue = vertexZvalue;
    }
    
    inline int getVertexZvalue()
    {
        return m_vertexZvalue;
    }
    
    inline void setUseAutomaticVertexZ(bool useAutomaticVertexZ)
    {
        m_useAutomaticVertexZ = useAutomaticVertexZ;
    }
    
    inline bool isUseAutomaticVertexZ()
    {
        return m_useAutomaticVertexZ;
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
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint m_tOffset;
        
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

    //对地图文件的弱引用
    ISOMap* m_pMap;
    
    //层的类型
    LayerType m_layerType;
    
    
    //! Only used when vertexZ is used
    int m_vertexZvalue;
    
    //自动计算vertex值
    bool m_useAutomaticVertexZ;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOLAYER_H_
