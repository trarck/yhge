#ifndef YHGE_ISOMETRIC_ISOTILEINFO_H_
#define YHGE_ISOMETRIC_ISOTILEINFO_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

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
    unsigned int m_uId;
    std::string m_sImageSource;
    //! size in pixels of the image
    CCSize m_tImageSize;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
    

};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILEINFO_H_
