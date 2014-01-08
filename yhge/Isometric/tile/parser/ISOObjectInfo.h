#ifndef YHGE_ISOMETRIC_ISOOBJECTINFO_H_
#define YHGE_ISOMETRIC_ISOOBJECTINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 对象信息
 * 用于描述每个组的元素信息。
 */
class ISOObjectInfo : public CCObject{

public:
    
    ISOObjectInfo();
    
    ~ISOObjectInfo();
    
    inline void setName(const char* sName)
    {
        m_sName = sName;
    }
    
    inline const char* getName()
    {
        return m_sName.c_str();
    }
    
    inline void setType(const char* sType)
    {
        m_sType = sType;
    }
    
    inline const char* getType()
    {
        return m_sType.c_str();
    }
    
    inline void setGid(unsigned int uGid)
    {
        m_uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return m_uGid;
    }
    
    inline void setPosition(CCPoint& tPosition)
    {
        m_tPosition = tPosition;
    }
    
    inline CCPoint& getPosition()
    {
        return m_tPosition;
    }
    
    inline void setSize(CCSize& tSize)
    {
        m_tSize = tSize;
    }
    
    inline CCSize& getSize()
    {
        return m_tSize;
    }
    
    inline void setRotation(float fRotation)
    {
        m_fRotation = fRotation;
    }
    
    inline float getRotation()
    {
        return m_fRotation;
    }
    
    inline void setVisible(bool bVisible)
    {
        m_bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return m_bVisible;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(m_pProperties);
        m_pProperties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return m_pProperties;
    }
    
protected:
    /**
     * 对像名称
     */
    std::string m_sName;
    
    /**
     * 对像类型
     */
    std::string m_sType;
    
    /**
     * 对像全局id
     */
    unsigned int m_uGid;
    
    /**
     * 对像位置。像素坐标，不是格子坐标。
     */
    CCPoint m_tPosition;
    
    /**
     * 对像大小
     */
    CCSize m_tSize;
    
    /**
     * 对像角度
     */
    float m_fRotation;
    
    /**
     * 对像是否可见
     */
    bool m_bVisible;
    
    /**
     * 对像扩展属性
     */
    CCDictionary* m_pProperties;
    
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOOBJECTINFO_H_
