#ifndef YHGE_ISOMETRIC_ISOMAPOBJECT_H_
#define YHGE_ISOMETRIC_ISOMAPOBJECT_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图上要显示的对象
 * 是一个整体
 */
class ISOMapObject : public Ref{

public:
    
    ISOMapObject();   
  
    ~ISOMapObject();
   
    bool init();
    
public:
    
    inline const std::string& getName(){ return _name; }
    inline void setName(const std::string& name){ _name = name; }
    
    inline void setType(const std::string&  pType)
    {
        _type = pType;
    }
    
    inline std::string& getType()
    {
        return _type;
    }
    
    inline void seposition(Vec2 position)
    {
        _position = position;
    }
    
    inline Vec2 geposition()
    {
        return _position;
    }
    
    inline void sesize(Size size)
    {
        _size = size;
    }
    
    inline Size gesize()
    {
        return _size;
    }
    
    inline void setGid(unsigned int uGid)
    {
        _uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return _uGid;
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
        _properties=pProperties;
        
    }
    
    inline CCDictionary* getProperties()
    {
        return _properties;
    }
    
    inline void setRotation(float rotation)
    {
        _rotation = rotation;
    }
    
    inline float getRotation()
    {
        return _rotation;
    }
    
protected:
    
    /**
     * 对象的名称
     */
    std::string _name;
    
    /**
     * 对象的类型
     */
    std::string _type;
    
    /**
     * 对象的位置
     * 是像素坐标
     */
    Vec2 _position;
    
    /**
     * 对象的大小
     * 不同的对象类型，对应的单位不同。
     */
    Size _size;
    
    /**
     * 对象的gid
     */
    unsigned int _uGid;
    
    /**
     * 旋转角度
     */
    float _rotation;
    
    /**
     * 对象是否可见
     */
    bool _visible;

    /**
     * 属性
     */
    CCDictionary* _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAPOBJECT_H_
