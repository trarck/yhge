#ifndef YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
#define YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 层的信息
 */
class ISOActiveLayerInfo : public Ref{

public:
    
    ISOActiveLayerInfo();
    ~ISOActiveLayerInfo();
    
    inline void setName(const std::string& name)
    {
        _name = name;
    }
    
    inline const std::string& getName()
    {
        return _name;
    }
    
    inline void setLayerSize(Size& tLayerSize)
    {
        _layerSize = tLayerSize;
    }
    
    inline Size& getLayerSize()
    {
        return _layerSize;
    }
    
    inline void setVisible(bool visible)
    {
        _visible = visible;
    }
    
    inline bool getVisible()
    {
        return _visible;
    }
    
    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    inline void seoffset(Vec2& offset)
    {
        _offset = offset;
    }
    
    inline Vec2& geoffset()
    {
        return _offset;
    }
    
    inline void setProperties(const ValueMap& pProperties)
    {
        _properties = pProperties;
    }
    
    inline ValueMap& getProperties()
    {
        return _properties;
    }
    
    inline void setRenderIndex(int renderIndex)
    {
        _renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return _renderIndex;
    }
    
    inline void setObjects(CCArray* objects)
    {
        CC_SAFE_RETAIN(objects);
        CC_SAFE_RELEASE(_objects);
        _objects = objects;
    }
    
    inline CCArray* getObjects()
    {
        return _objects;
    }


protected:
    /**
     * 名称
     */
    std::string         _name;
    
    /**
     * 大小。格子数，不是像素大小
     */
    Size              _layerSize;
    
    /**
     * 是否可见
     */
    bool                _visible;
    
    /**
     * 透明度
     */
    unsigned char _opacity;
    
    /**
     * 偏移量
     */
    Vec2             _offset;
    
    /**
     * 扩展属性
     */
    ValueMap _properties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;
    
    /**
     * 包含的对象
     */
    CCArray* _objects;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
