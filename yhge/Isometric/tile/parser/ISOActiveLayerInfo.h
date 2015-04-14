#ifndef YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
#define YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 层的信息
 */
class ISOActiveLayerInfo : public Ref{

public:
    
    ISOActiveLayerInfo();
    ~ISOActiveLayerInfo();
    
    inline void setName(const std::string& sName)
    {
        _sName = sName;
    }
    
    inline const std::string& getName()
    {
        return _sName;
    }
    
    inline void setLayerSize(CCSize& tLayerSize)
    {
        _tLayerSize = tLayerSize;
    }
    
    inline CCSize& getLayerSize()
    {
        return _tLayerSize;
    }
    
    inline void setVisible(bool bVisible)
    {
        _bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return _bVisible;
    }
    
    inline void setOpacity(unsigned char cOpacity)
    {
        _cOpacity = cOpacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _cOpacity;
    }
    
    inline void setOffset(CCPoint& tOffset)
    {
        _tOffset = tOffset;
    }
    
    inline CCPoint& getOffset()
    {
        return _tOffset;
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
    
    inline void setRenderIndex(int renderIndex)
    {
        _renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return _renderIndex;
    }
    
    inline void setObjects(CCArray* objects)
    {
        CC_SAFE_RETAIN(objects);
        CC_SAFE_RELEASE(_objects);
        _objects = objects;
    }
    
    inline CCArray* getObjects()
    {
        return _objects;
    }


protected:
    /**
     * 名称
     */
    std::string         _sName;
    
    /**
     * 大小。格子数，不是像素大小
     */
    CCSize              _tLayerSize;
    
    /**
     * 是否可见
     */
    bool                _bVisible;
    
    /**
     * 透明度
     */
    unsigned char _cOpacity;
    
    /**
     * 偏移量
     */
    CCPoint             _tOffset;
    
    /**
     * 扩展属性
     */
    CCDictionary* _pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;
    
    /**
     * 包含的对象
     */
    CCArray* _objects;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOACTIVELAYERINFO_H_
