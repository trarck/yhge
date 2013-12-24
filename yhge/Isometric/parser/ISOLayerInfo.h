#ifndef YHGE_ISOMETRIC_ISOLAYERINFO_H_
#define YHGE_ISOMETRIC_ISOLAYERINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ISOLayerInfo : public CCObject{

public:
    
    ISOLayerInfo();
    ~ISOLayerInfo();
    
    inline void setName(const char* sName)
    {
        m_sName = sName;
    }
    
    inline const char* getName()
    {
        return m_sName.c_str();
    }
    
    inline void setLayerSize(CCSize& tLayerSize)
    {
        m_tLayerSize = tLayerSize;
    }
    
    inline CCSize& getLayerSize()
    {
        return m_tLayerSize;
    }
    
    inline void setTiles(unsigned int* pTiles)
    {
        m_pTiles = pTiles;
    }
    
    inline unsigned int* getTiles()
    {
        return m_pTiles;
    }
    
    inline void setVisible(bool bVisible)
    {
        m_bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return m_bVisible;
    }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        m_cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return m_cOpacity;
    }
    
//    inline void setOwnTiles(bool bOwnTiles)
//    {
//        m_bOwnTiles = bOwnTiles;
//    }
//    
//    inline bool getOwnTiles()
//    {
//        return m_bOwnTiles;
//    }
//    
//    inline void setMinGID( unsigned int  MinGID)
//    {
//        m_ MinGID =  MinGID;
//    }
//    
//    inline  unsigned int getMinGID()
//    {
//        return m_ MinGID;
//    }
//    
//    inline void setMaxGID(unsigned int uMaxGID)
//    {
//        m_uMaxGID = uMaxGID;
//    }
//    
//    inline unsigned int getMaxGID()
//    {
//        return m_uMaxGID;
//    }
    
    inline void setOffset(CCPoint& tOffset)
    {
        m_tOffset = tOffset;
    }
    
    inline CCPoint& getOffset()
    {
        return m_tOffset;
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
    std::string         m_sName;
    CCSize              m_tLayerSize;
    bool                m_bVisible;
    unsigned char m_cOpacity;
//    bool                m_bOwnTiles;
//    unsigned int        m_uMinGID;
//    unsigned int        m_uMaxGID;
    CCPoint             m_tOffset;

    unsigned int*       m_pTiles;
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOLAYERINFO_H_
