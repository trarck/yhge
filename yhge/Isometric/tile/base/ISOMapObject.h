#ifndef YHGE_ISOMETRIC_ISOMAPOBJECT_H_
#define YHGE_ISOMETRIC_ISOMAPOBJECT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 地图上要显示的对象
 * 是一个整体
 */
class ISOMapObject : public CCObject{

public:
    
    ISOMapObject();   
  
    ~ISOMapObject();
   
    bool init();
    
public:
    
    inline const char* getName(){ return m_sName.c_str(); }
    inline void setName(const char *name){ m_sName = name; }
    
    inline void setType(const char * pType)
    {
        m_sType = pType;
    }
    
    inline std::string& getType()
    {
        return m_sType;
    }
    
    inline void setPosition(CCPoint tPosition)
    {
        m_tPosition = tPosition;
    }
    
    inline CCPoint getPosition()
    {
        return m_tPosition;
    }
    
    inline void setSize(CCSize tSize)
    {
        m_tSize = tSize;
    }
    
    inline CCSize getSize()
    {
        return m_tSize;
    }
    
    inline void setGid(unsigned int uGid)
    {
        m_uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return m_uGid;
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
        m_pProperties=pProperties;
        
    }
    
    inline CCDictionary* getProperties()
    {
        return m_pProperties;
    }
    
    inline void setRotation(float rotation)
    {
        m_rotation = rotation;
    }
    
    inline float getRotation()
    {
        return m_rotation;
    }
    
protected:
    
    /**
     * 对象的名称
     */
    std::string m_sName;
    
    /**
     * 对象的类型
     */
    std::string m_sType;
    
    /**
     * 对象的位置
     * 是像素坐标
     */
    CCPoint m_tPosition;
    
    /**
     * 对象的大小
     */
    CCSize m_tSize;
    
    /**
     * 对象的gid
     */
    unsigned int m_uGid;
    
    /**
     * 旋转角度
     */
    float m_rotation;
    
    /**
     * 对象是否可见
     */
    bool m_bVisible;

    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOMAPOBJECT_H_
