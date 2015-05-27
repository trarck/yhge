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
    
    inline void setName(const std::string& name)
    {
        _name = name;
    }
    
    inline const std::string& getName()
    {
        return _name;
    }
    
    inline void setLayerSize(Size& tLayerSize)
    {
        _layerSize = tLayerSize;
    }
    
    inline Size& getLayerSize()
    {
        return _layerSize;
    }
    
    inline void setTiles(unsigned int* tiles)
    {
        _tiles = tiles;
    }
    
    inline unsigned int* getTiles()
    {
        return _tiles;
    }
    
    inline void setVisible(bool visible)
    {
        _visible = visible;
    }
    
    inline bool getVisible()
    {
        return _visible;
    }
    
    inline void setOpacity(unsigned char opacity)
    {
        _opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return _opacity;
    }
    
    inline void setOwnTiles(bool ownTiles)
    {
        _ownTiles = ownTiles;
    }
    
    inline bool getOwnTiles()
    {
        return _ownTiles;
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
    
    inline void setOffset(Vec2& offset)
    {
        _offset = offset;
    }
    
    inline Vec2& getOffset()
    {
        return _offset;
    }
    
    inline void setProperties(const ValueMap& pProperties)
    {
        _properties = pProperties;
    }
    
    inline ValueMap& getProperties()
    {
        return _properties;
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
    std::string         _name;
    
    /**
     * layer的大小。格子数，不是像素大小
     */
    Size              _layerSize;
    
    /**
     * layer是否可见
     */
    bool                _visible;
    
    /**
     * layer的透明度
     */
    unsigned char _opacity;
    
    bool                _ownTiles;
    
//    unsigned int        _uMinGID;
//    unsigned int        _uMaxGID;
    
    /**
     * layer的偏移量
     */
    Vec2             _offset;

    /**
     * layer的每个格子的信息。主要是tile id
     */
    unsigned int*       _tiles;
    
    /**
     * layer的扩展属性
     */
    ValueMap _properties;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOLAYERINFO_H_
