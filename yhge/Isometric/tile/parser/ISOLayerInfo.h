#ifndef YHGE_ISOMETRIC_ISOLAYERINFO_H_
#define YHGE_ISOMETRIC_ISOLAYERINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 层的信息
 */
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
    
    inline void setOwnTiles(bool bOwnTiles)
    {
        m_bOwnTiles = bOwnTiles;
    }
    
    inline bool getOwnTiles()
    {
        return m_bOwnTiles;
    }
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
    
    inline void setRenderIndex(int renderIndex)
    {
        m_renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return m_renderIndex;
    }


protected:
    /**
     * layer的名称
     */
    std::string         m_sName;
    
    /**
     * layer的大小。格子数，不是像素大小
     */
    CCSize              m_tLayerSize;
    
    /**
     * layer是否可见
     */
    bool                m_bVisible;
    
    /**
     * layer的透明度
     */
    unsigned char m_cOpacity;
    
    bool                m_bOwnTiles;
    
//    unsigned int        m_uMinGID;
//    unsigned int        m_uMaxGID;
    
    /**
     * layer的偏移量
     */
    CCPoint             m_tOffset;

    /**
     * layer的每个格子的信息。主要是tile id
     */
    unsigned int*       m_pTiles;
    
    /**
     * layer的扩展属性
     */
    CCDictionary* m_pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int m_renderIndex;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOLAYERINFO_H_
