﻿#ifndef YHGE_ISOMETRIC_ISOACTIVETILELAYER_H_
#define YHGE_ISOMETRIC_ISOACTIVETILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "../base/ISOObjectGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileMap;

/**
 * 活动层。
 * 提供场景活动元素的层
 * 对于tiled创建的地图文件，可以是tile layer,也可以是object layer。
 */
class ISOActiveTileLayer : public Node {

public:
	
	ISOActiveTileLayer();
    
	virtual ~ISOActiveTileLayer(void);
	
    virtual bool init();
    
    static ISOActiveTileLayer* create();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupObjects();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    
    //移动
    virtual void scroll(const Vec2& tOffset);
    virtual void scroll(float x,float y);
    
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
    
    inline void setLayerName(const std::string& layerName)
    {
        _layerName = layerName;
    }
    
    inline const std::string& getLayerName()
    {
        return _layerName;
    }
    
    inline void setOffset(const Vec2& offset)
    {
        _offset = offset;
    }
    
    inline const Vec2& getOffset()
    {
        return _offset;
    }
    
	inline void setProperties(const ValueMap& properties)
    {
        _properties = properties;
    }
    
	inline ValueMap& getProperties()
    {
        return _properties;
    }
    
    inline void setLayerOrientation(unsigned int layerOrientation)
    {
        _layerOrientation = layerOrientation;
    }
    
    inline unsigned int getLayerOrientation()
    {
        return _layerOrientation;
    }
    
    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    inline void setVertexZvalue(int vertexZvalue)
    {
        _vertexZvalue = vertexZvalue;
    }
    
    inline int getVertexZvalue()
    {
        return _vertexZvalue;
    }
    
    inline void setMap(ISOTileMap* map)
    {
        _map = map;
    }
    
    inline ISOTileMap* getMap()
    {
        return _map;
    }
    
    inline void setObjectGroup(ISOObjectGroup* objectGroup)
    {
        CC_SAFE_RETAIN(objectGroup);
        CC_SAFE_RELEASE(_objectGroup);
        _objectGroup = objectGroup;
    }
    
    inline ISOObjectGroup* getObjectGroup()
    {
        return _objectGroup;
    }
    
protected:
    
    /**
     * 使用gid从tileset中取出一个图片显示
     */
    Sprite* createObject(int gid,const Vec2& position);
    
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
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
    Vec2 _offset;
    
    /**
     * 属性
     */
	ValueMap _properties;
    
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int _layerOrientation;
    
    /**
     * 透明度。
     */
    unsigned char _opacity;
    
    //! Only used when vertexZ is used
    int _vertexZvalue;
    
    //对地图的引用。
    ISOTileMap* _map;

    /**
     * 使用object group
     */
    ISOObjectGroup* _objectGroup;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOACTIVETILELAYER_H_
