#ifndef YHGE_ISOMETRIC_ISOLAYERINFO_H_
#define YHGE_ISOMETRIC_ISOLAYERINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 层的信息
 */
class ISOLayerInfo : public Ref{

public:
    
    ISOLayerInfo();
    ~ISOLayerInfo();
    
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
    
    inline void setTiles(unsigned int* pTiles)
    {
        _pTiles = pTiles;
    }
    
    inline unsigned int* getTiles()
    {
        return _pTiles;
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
    
    inline void setOwnTiles(bool bOwnTiles)
    {
        _bOwnTiles = bOwnTiles;
    }
    
    inline bool getOwnTiles()
    {
        return _bOwnTiles;
    }
//
//    inline void setMinGID( unsigned int  MinGID)
//    {
//        _ MinGID =  MinGID;
//    }
//    
//    inline  unsigned int getMinGID()
//    {
//        return _ MinGID;
//    }
//    
//    inline void setMaxGID(unsigned int uMaxGID)
//    {
//        _uMaxGID = uMaxGID;
//    }
//    
//    inline unsigned int getMaxGID()
//    {
//        return _uMaxGID;
//    }
    
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


protected:
    /**
     * layer的名称
     */
    std::string         _sName;
    
    /**
     * layer的大小。格子数，不是像素大小
     */
    CCSize              _tLayerSize;
    
    /**
     * layer是否可见
     */
    bool                _bVisible;
    
    /**
     * layer的透明度
     */
    unsigned char _cOpacity;
    
    bool                _bOwnTiles;
    
//    unsigned int        _uMinGID;
//    unsigned int        _uMaxGID;
    
    /**
     * layer的偏移量
     */
    CCPoint             _tOffset;

    /**
     * layer的每个格子的信息。主要是tile id
     */
    unsigned int*       _pTiles;
    
    /**
     * layer的扩展属性
     */
    CCDictionary* _pProperties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOLAYERINFO_H_
