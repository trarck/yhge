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
		_tLayerSize = tLayerSize;
	}

	inline CCSize getLayerSize()
	{
		return _tLayerSize;
	}


	inline void setOffset(const CCPoint& tOffset)
	{
		_tOffset = tOffset;
	}

	inline void setOffset(float x,float y)
	{
		_tOffset.x=x;
		_tOffset.y=y;
	}

	inline CCPoint getOffset()
	{
		return _tOffset;
	}

	inline void setMapTileSize(float width,float height)
	{
		_tMapTileSize.width=width;
		_tMapTileSize.height=height;
	}

	inline void setMapTileSize(const CCSize& tMapTileSize)
	{
		_tMapTileSize = tMapTileSize;
	}

	inline const CCSize& getMapTileSize()
	{
		return _tMapTileSize;
	}


	inline void setLayerOrientation(unsigned int uLayerOrientation)
	{
		_uLayerOrientation = uLayerOrientation;
	}

	inline unsigned int getLayerOrientation()
	{
		return _uLayerOrientation;
	}

	inline void setProperties(CCDictionary* pProperties)
	{
		CC_SAFE_RETAIN(pProperties);
		CC_SAFE_RELEASE(_pProperties);
		_pProperties = pProperties;
	}

	inline CCDictionary* getProperties()
	{
		return _pProperties;
	}
    
    inline const std::string& getLayerName(){ return _sLayerName; }
    
    inline void setLayerName(const std::string& layerName){ _sLayerName = layerName; }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        _cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _cOpacity;
    }
    
    virtual void setMap(ISOMap* pMap);
    
    inline ISOMap* getMap()
    {
        return _pMap;
    }
    
    inline void setLayerType(LayerType layerType)
    {
        _layerType = layerType;
    }
    
    inline LayerType getLayerType()
    {
        return _layerType;
    }
    
    inline void setVertexZvalue(int vertexZvalue)
    {
        _vertexZvalue = vertexZvalue;
    }
    
    inline int getVertexZvalue()
    {
        return _vertexZvalue;
    }
    
    inline void setUseAutomaticVertexZ(bool useAutomaticVertexZ)
    {
        _useAutomaticVertexZ = useAutomaticVertexZ;
    }
    
    inline bool isUseAutomaticVertexZ()
    {
        return _useAutomaticVertexZ;
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
    std::string _sLayerName;
    
    /**
     * 层的地图大小
     */
	CCSize _tLayerSize;
    
    /**
      地图的一个图块大小
     */
    CCSize _tMapTileSize;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint _tOffset;
        
    /**
     * 地图属性
     */
    CCDictionary* _pProperties;
       
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int _uLayerOrientation;
    
    //! Layer supports opacity
    unsigned char       _cOpacity;

    //对地图文件的弱引用
    ISOMap* _pMap;
    
    //层的类型
    LayerType _layerType;
    
    
    //! Only used when vertexZ is used
    int _vertexZvalue;
    
    //自动计算vertex值
    bool _useAutomaticVertexZ;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOLAYER_H_
