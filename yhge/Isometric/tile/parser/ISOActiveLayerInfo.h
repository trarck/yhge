#ifndef YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
#define YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 层的信息
 */
class ISOActiveLayerInfo : public CCObject{

public:
    
    ISOActiveLayerInfo();
    ~ISOActiveLayerInfo();
    
    inline void setName(const std::string& sName)
    {
        m_sName = sName;
    }
    
    inline const std::string& getName()
    {
        return m_sName;
    }
    
    inline void setLayerSize(CCSize& tLayerSize)
    {
        m_tLayerSize = tLayerSize;
    }
    
    inline CCSize& getLayerSize()
    {
        return m_tLayerSize;
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
    
    inline void setObjects(CCArray* objects)
    {
        CC_SAFE_RETAIN(objects);
        CC_SAFE_RELEASE(m_objects);
        m_objects = objects;
    }
    
    inline CCArray* getObjects()
    {
        return m_objects;
    }


protected:
    /**
     * 名称
     */
    std::string         m_sName;
    
    /**
     * 大小。格子数，不是像素大小
     */
    CCSize              m_tLayerSize;
    
    /**
     * 是否可见
     */
    bool                m_bVisible;
    
    /**
     * 透明度
     */
    unsigned char m_cOpacity;
    
    /**
     * 偏移量
     */
    CCPoint             m_tOffset;
    
    /**
     * 扩展属性
     */
    CCDictionary* m_pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int m_renderIndex;
    
    /**
     * 包含的对象
     */
    CCArray* m_objects;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
