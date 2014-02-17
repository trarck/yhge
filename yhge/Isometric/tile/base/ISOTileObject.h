#ifndef YHGE_ISOMETRIC_ISOTileObject_H_
#define YHGE_ISOMETRIC_ISOTileObject_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图上要显示的对象
 * 如果对象大于一个格子，则要拆分成几个部分
 */
class ISOTileObject : public CCObject{

public:
    
    ISOTileObject();   
  
    ~ISOTileObject();
   
    bool init();
    
public:
    
    inline const char* getName(){ return m_sName.c_str(); }
    inline void setName(const char *name){ m_sName = name; }
    
    virtual void setType(const char *pType);
    virtual std::string& getType();
    
    virtual void setPosition(CCPoint tPosition);
    virtual CCPoint getPosition();
    
    virtual void setSize(CCSize tSize);
    virtual CCSize getSize();
    
    virtual void setGid(unsigned int uGid);
    virtual unsigned int getGid();
    
    virtual void setVisible(bool bVisible);
    virtual bool getVisible();
    
    inline void setParts(CCArray* pParts)
    {
        CC_SAFE_RETAIN(pParts);
        CC_SAFE_RELEASE(m_pParts);
        m_pParts = pParts;
    }
    
    inline CCArray* getParts()
    {
        return m_pParts;
    }
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
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
     * 格子坐标
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
     * 对象是否可见
     */
    bool m_bVisible;
    
    /**
     * 组成部分
     */
    CCArray* m_pParts;

    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTileObject_H_
