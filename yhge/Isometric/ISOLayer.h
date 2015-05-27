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
        
    virtual bool init(Size& mapTileSize);
    
    virtual bool init(Size& mapTileSize,Vec2& offset);
    
    /**
     * 初始化偏移
     */
	virtual void inioffset(const Vec2& offset);
    
    virtual void inioffset(float x,float y);
    
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
    virtual void scroll(const Vec2& offset);
    virtual void scroll(float x,float y);
    
    /**
     * 地图的缩放值
     */
    virtual void onMapScaleChange(float orignalScale,float newScale);

    
    /**
     * 取得zOrder值，处理遮挡使用.zOrder vertexZ二者使用一
     */
    int zOrderForPos(const Vec2& pos);
    
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const Vec2& pos);
    
	/**
     * 获取属性名称
     */
	
	Value getProperty(const std::string& propertyName);

public:
    
    enum LayerType
    {
        kEmptyLayer=0,
        kTileLayer=1,
        kObjectLayer=2,
        kImageLayer=3
    };
    
    //===================get set 属性====================//
	inline void setLayerSize(const Size& tLayerSize)
	{
		_layerSize = tLayerSize;
	}

	inline Size getLayerSize()
	{
		return _layerSize;
	}


	inline void seoffset(const Vec2& offset)
	{
		_offset = offset;
	}

	inline void seoffset(float x,float y)
	{
		_offset.x=x;
		_offset.y=y;
	}

	inline Vec2 geoffset()
	{
		return _offset;
	}

	inline void setMapTileSize(float width,float height)
	{
		_mapTileSize.width=width;
		_mapTileSize.height=height;
	}

	inline void setMapTileSize(const Size& mapTileSize)
	{
		_mapTileSize = mapTileSize;
	}

	inline const Size& getMapTileSize()
	{
		return _mapTileSize;
	}


	inline void setLayerOrientation(unsigned int layerOrientation)
	{
		_layerOrientation = layerOrientation;
	}

	inline unsigned int getLayerOrientation()
	{
		return _layerOrientation;
	}

	inline void setProperties(const ValueMap& pProperties)
	{
		_properties = pProperties;
	}

	inline ValueMap& getProperties()
	{
		return _properties;
	}
    
    inline const std::string& getLayerName(){ return _layerName; }
    
    inline void setLayerName(const std::string& layerName){ _layerName = layerName; }
    
    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    virtual void setMap(ISOMap* map);
    
    inline ISOMap* getMap()
    {
        return _map;
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
    std::string _layerName;
    
    /**
     * 层的地图大小
     */
	Size _layerSize;
    
    /**
      地图的一个图块大小
     */
    Size _mapTileSize;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	Vec2 _offset;
        
    /**
     * 地图属性
     */
    ValueMap _properties;
       
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int _layerOrientation;
    
    //! Layer supports opacity
    unsigned char       _opacity;

    //对地图文件的弱引用
    ISOMap* _map;
    
    //层的类型
    LayerType _layerType;
    
    
    //! Only used when vertexZ is used
    int _vertexZvalue;
    
    //自动计算vertex值
    bool _useAutomaticVertexZ;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOLAYER_H_
