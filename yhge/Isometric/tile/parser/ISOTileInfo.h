#ifndef YHGE_ISOMETRIC_ISOTILEINFO_H_
#define YHGE_ISOMETRIC_ISOTILEINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 格子信息
 */
class ISOTileInfo : public CCObject{

public:
    
    ISOTileInfo();
    
    ~ISOTileInfo();

    
public:
           
    inline void setId(unsigned int uId)
    {
        m_uId = uId;
    }
    
    inline unsigned int getId()
    {
        return m_uId;
    }

    inline void setImageSource(const char * pImageSource)
    {
        m_sImageSource = pImageSource;
    }
    
    inline const char * getImageSource()
    {
        return m_sImageSource.c_str();
    }
    
    inline void setImageSize(CCSize& tImageSize)
    {
        m_tImageSize = tImageSize;
    }
    
    inline CCSize& getImageSize()
    {
        return m_tImageSize;
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
     * 格子id
     */
    unsigned int m_uId;
    
    /**
     * 图像路径
     */
    std::string m_sImageSource;
    
    /**
     * 图像大小。像素大小
     */
    CCSize m_tImageSize;
    
    /**
     * 格子扩展属性
     */
    CCDictionary* m_pProperties;
    

};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILEINFO_H_
