﻿#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图中对象组信息，和layer是同一级别
 */
class ISOObjectGroupInfo : public Ref{

public:
    
    ISOObjectGroupInfo();
    
    ~ISOObjectGroupInfo();
    
    inline void setName(const std::string& name)
    {
        _name = name;
    }
    
    inline const std::string& getName()
    {
        return _name.c_str();
    }
    
    inline void secolor(ccColor3B& color)
    {
        _color = color;
    }
    
    inline ccColor3B& gecolor()
    {
        return _color;
    }
    
    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    inline void setVisible(bool visible)
    {
        _visible = visible;
    }
    
    inline bool getVisible()
    {
        return _visible;
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
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(_properties);
        _properties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return _properties;
    }
    
    inline void sepositionOffset(Vec2& positionOffset)
    {
        _positionOffset = positionOffset;
    }
    
    inline Vec2& gepositionOffset()
    {
        return _positionOffset;
    }
    
    inline void setRenderIndex(int renderIndex)
    {
        _renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return _renderIndex;
    }


protected:
    /**
     * 组的名称。
     * 用于标识此组
     */
    std::string _name;
    
    /**
     * 组的颜色。平常不会不用到
     * 组内的所有元素受到影响
     */
    ccColor3B _color;
    
    //cocos2dx use 0-255
    /**
     * 组的透明度。平常不会用到。
     * 组内的所有元素受到影响
     */
    unsigned char _opacity;
    
    /**
     * 组是否可见
     */
    bool _visible;
    
    /**
     * 组的位置偏移
     */
    Vec2 _positionOffset;
    
    /**
     * 组所包含的对象
     */
    CCArray* _objects;
    
    /**
     * 组是扩展属性
     */
    CCDictionary* _properties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
