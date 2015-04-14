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
    
    inline void setName(const char* sName)
    {
        _sName = sName;
    }
    
    inline const char* getName()
    {
        return _sName.c_str();
    }
    
    inline void setType(const char* sType)
    {
        _sType = sType;
    }
    
    inline const char* getType()
    {
        return _sType.c_str();
    }
    
    inline void setGid(unsigned int uGid)
    {
        _uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return _uGid;
    }
    
    inline void setPosition(const CCPoint& tPosition)
    {
        _tPosition = tPosition;
    }
    
    inline CCPoint& getPosition()
    {
        return _tPosition;
    }
    
    inline void setSize(CCSize& tSize)
    {
        _tSize = tSize;
    }
    
    inline CCSize& getSize()
    {
        return _tSize;
    }
    
    inline void setRotation(float fRotation)
    {
        _fRotation = fRotation;
    }
    
    inline float getRotation()
    {
        return _fRotation;
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
        _pProperties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return _pProperties;
    }
    
protected:
    /**
     * 对像名称
     */
    std::string _sName;
    
    /**
     * 对像类型
     */
    std::string _sType;
    
    /**
     * 对像全局id
     */
    unsigned int _uGid;
    
    /**
     * 对像位置。像素坐标，不是格子坐标。
     */
    CCPoint _tPosition;
    
    /**
     * 对像大小
     */
    CCSize _tSize;
    
    /**
     * 对像角度
     */
    float _fRotation;
    
    /**
     * 对像是否可见
     */
    bool _bVisible;
    
    /**
     * 对像扩展属性
     */
    CCDictionary* _pProperties;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTINFO_H_
