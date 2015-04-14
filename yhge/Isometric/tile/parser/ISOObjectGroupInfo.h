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
        _sName = sName;
    }
    
    inline const char* getName()
    {
        return _sName.c_str();
    }
    
    inline void setColor(ccColor3B& tColor)
    {
        _tColor = tColor;
    }
    
    inline ccColor3B& getColor()
    {
        return _tColor;
    }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        _cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _cOpacity;
    }
    
    inline void setVisible(bool bVisible)
    {
        _bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return _bVisible;
    }
    
    inline void setObjects(CCArray* pObjects)
    {
        CC_SAFE_RETAIN(pObjects);
        CC_SAFE_RELEASE(_pObjects);
        _pObjects = pObjects;
    }
    
    inline CCArray* getObjects()
    {
        return _pObjects;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(_pProperties);
        _pProperties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return _pProperties;
    }
    
    inline void setPositionOffset(CCPoint& tPositionOffset)
    {
        _tPositionOffset = tPositionOffset;
    }
    
    inline CCPoint& getPositionOffset()
    {
        return _tPositionOffset;
    }
    
    inline void setRenderIndex(int renderIndex)
    {
        _renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return _renderIndex;
    }


protected:
    /**
     * 组的名称。
     * 用于标识此组
     */
    std::string _sName;
    
    /**
     * 组的颜色。平常不会不用到
     * 组内的所有元素受到影响
     */
    ccColor3B _tColor;
    
    //cocos2dx use 0-255
    /**
     * 组的透明度。平常不会用到。
     * 组内的所有元素受到影响
     */
    unsigned char _cOpacity;
    
    /**
     * 组是否可见
     */
    bool _bVisible;
    
    /**
     * 组的位置偏移
     */
    CCPoint _tPositionOffset;
    
    /**
     * 组所包含的对象
     */
    CCArray* _pObjects;
    
    /**
     * 组是扩展属性
     */
    CCDictionary* _pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUPINFO_H_
