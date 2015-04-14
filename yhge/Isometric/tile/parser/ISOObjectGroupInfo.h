#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图中对象组信息，和layer是同一级别
 */
class ISOObjectGroupInfo : public Ref{

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
     * 组的名称。
     * 用于标识此组
     */
    std::string m_sName;
    
    /**
     * 组的颜色。平常不会不用到
     * 组内的所有元素受到影响
     */
    ccColor3B m_tColor;
    
    //cocos2dx use 0-255
    /**
     * 组的透明度。平常不会用到。
     * 组内的所有元素受到影响
     */
    unsigned char m_cOpacity;
    
    /**
     * 组是否可见
     */
    bool m_bVisible;
    
    /**
     * 组的位置偏移
     */
    CCPoint m_tPositionOffset;
    
    /**
     * 组所包含的对象
     */
    CCArray* m_pObjects;
    
    /**
     * 组是扩展属性
     */
    CCDictionary* m_pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int m_renderIndex;

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
