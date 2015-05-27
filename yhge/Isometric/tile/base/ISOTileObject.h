#ifndef YHGE_ISOMETRIC_ISOTileObject_H_
#define YHGE_ISOMETRIC_ISOTileObject_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图上要显示的对象
 * 如果对象大于一个格子，则要拆分成几个部分
 */
class ISOTileObject : public Ref{

public:
    
    ISOTileObject();   
  
    ~ISOTileObject();
   
    bool init();
    
public:
    
    inline const std::string& getName(){ return _name; }
    inline void setName(const std::string& name){ _name = name; }
    
    virtual void setType(const std::string& pType);
    virtual std::string& getType();
    
    virtual void setPosition(Vec2 position);
    virtual Vec2 getPosition();
    
    virtual void setSize(Size size);
    virtual Size getSize();
    
    virtual void setGid(unsigned int uGid);
    virtual unsigned int getGid();
    
    virtual void setVisible(bool visible);
    virtual bool getVisible();
    
    inline void setParts(CCArray* parts)
    {
        CC_SAFE_RETAIN(parts);
        CC_SAFE_RELEASE(_parts);
        _parts = parts;
    }
    
    inline CCArray* getParts()
    {
        return _parts;
    }
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
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
     * 格子坐标
     */
    Vec2 _position;
    
    /**
     * 对象的大小
     */
    Size _size;
    
    /**
     * 对象的gid
     */
    unsigned int _uGid;
    
    /**
     * 对象是否可见
     */
    bool _visible;
    
    /**
     * 组成部分
     */
    CCArray* _parts;

    /**
     * 属性
     */
    CCDictionary* _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTileObject_H_
