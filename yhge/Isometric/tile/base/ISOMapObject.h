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
    
    inline const char* getName(){ return _sName.c_str(); }
    inline void setName(const char *name){ _sName = name; }
    
    inline void setType(const char * pType)
    {
        _sType = pType;
    }
    
    inline std::string& getType()
    {
        return _sType;
    }
    
    inline void setPosition(CCPoint tPosition)
    {
        _tPosition = tPosition;
    }
    
    inline CCPoint getPosition()
    {
        return _tPosition;
    }
    
    inline void setSize(CCSize tSize)
    {
        _tSize = tSize;
    }
    
    inline CCSize getSize()
    {
        return _tSize;
    }
    
    inline void setGid(unsigned int uGid)
    {
        _uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return _uGid;
    }
    
    inline void setVisible(bool bVisible)
    {
        _bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return _bVisible;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(_pProperties);
        _pProperties=pProperties;
        
    }
    
    inline CCDictionary* getProperties()
    {
        return _pProperties;
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
    std::string _sName;
    
    /**
     * 对象的类型
     */
    std::string _sType;
    
    /**
     * 对象的位置
     * 是像素坐标
     */
    CCPoint _tPosition;
    
    /**
     * 对象的大小
     * 不同的对象类型，对应的单位不同。
     */
    CCSize _tSize;
    
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
    bool _bVisible;

    /**
     * 属性
     */
    CCDictionary* _pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAPOBJECT_H_
