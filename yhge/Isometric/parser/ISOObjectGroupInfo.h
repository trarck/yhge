#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class ISOObjectGroupInfo : public CCObject{

public:
    
    ISOObjectGroupInfo();
    
    ~ISOObjectGroupInfo();
    
    inline void setName(const char* sName)
    {
        m_sName = sName;
    }
    
    inline const char* getName()
    {
        return m_sName.c_str();
    }
    
    inline void setColor(ccColor3B& tColor)
    {
        m_tColor = tColor;
    }
    
    inline ccColor3B& getColor()
    {
        return m_tColor;
    }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        m_cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return m_cOpacity;
    }
    
    inline void setVisible(bool bVisible)
    {
        m_bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return m_bVisible;
    }
    
    inline void setObjects(CCArray* pObjects)
    {
        CC_SAFE_RETAIN(pObjects);
        CC_SAFE_RELEASE(m_pObjects);
        m_pObjects = pObjects;
    }
    
    inline CCArray* getObjects()
    {
        return m_pObjects;
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
    
    inline void setPositionOffset(CCPoint& tPositionOffset)
    {
        m_tPositionOffset = tPositionOffset;
    }
    
    inline CCPoint& getPositionOffset()
    {
        return m_tPositionOffset;
    }

protected:
    
    std::string m_sName;
    ccColor3B m_tColor;
    //cocos2dx use 0-255
    unsigned char m_cOpacity;
    bool m_bVisible;
    CCArray* m_pObjects;
    CCDictionary* m_pProperties;

    CCPoint m_tPositionOffset;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
