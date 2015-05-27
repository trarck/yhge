#ifndef YHGE_ISOMETRIC_ISOOBJECTINFO_H_
#define YHGE_ISOMETRIC_ISOOBJECTINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 对象信息
 * 用于描述每个组的元素信息。
 */
class ISOObjectInfo : public Ref{

public:
    
    ISOObjectInfo();
    
    ~ISOObjectInfo();
    
    inline void setName(const std::string& name)
    {
        _name = name;
    }
    
    inline const std::string& getName()
    {
        return _name.c_str();
    }
    
    inline void setType(const std::string& type)
    {
        _type = type;
    }
    
    inline const std::string& getType()
    {
        return _type.c_str();
    }
    
    inline void setGid(unsigned int uGid)
    {
        _uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return _uGid;
    }
    
    inline void seposition(const Vec2& position)
    {
        _position = position;
    }
    
    inline Vec2& geposition()
    {
        return _position;
    }
    
    inline void sesize(Size& size)
    {
        _size = size;
    }
    
    inline Size& gesize()
    {
        return _size;
    }
    
    inline void setRotation(float rotation)
    {
        _rotation = rotation;
    }
    
    inline float getRotation()
    {
        return _rotation;
    }
    
    inline void setVisible(bool visible)
    {
        _visible = visible;
    }
    
    inline bool getVisible()
    {
        return _visible;
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
    
protected:
    /**
     * 对像名称
     */
    std::string _name;
    
    /**
     * 对像类型
     */
    std::string _type;
    
    /**
     * 对像全局id
     */
    unsigned int _uGid;
    
    /**
     * 对像位置。像素坐标，不是格子坐标。
     */
    Vec2 _position;
    
    /**
     * 对像大小
     */
    Size _size;
    
    /**
     * 对像角度
     */
    float _rotation;
    
    /**
     * 对像是否可见
     */
    bool _visible;
    
    /**
     * 对像扩展属性
     */
    CCDictionary* _properties;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTINFO_H_
