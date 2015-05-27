#ifndef YHGE_ISOMETRIC_ISOMAPINFO_H_
#define YHGE_ISOMETRIC_ISOMAPINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图的信息
 * 主要是layers和objectGroups。
 */
class ISOMapInfo : public Ref{

public:
    
    ISOMapInfo();
    
    ~ISOMapInfo();
    
    virtual bool init();
    
    virtual void setOrientation(int orientation);
    virtual int getOrientation();
    
    virtual void semapSize(const Size& mapSize);
    virtual const Size& gemapSize();
    
    virtual void setileSize(const Size& tileSize);
    virtual const Size& getileSize();
    
    virtual void setLayers(CCArray* layers);
    virtual CCArray* getLayers();
    
    virtual void setTilesets(CCArray* tilesets);
    virtual CCArray* getTilesets();
    
    virtual void setObjectGroups(CCArray* objectGroups);
    virtual CCArray* getObjectGroups();
       
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
        
    inline void sebackgroundColor(ccColor3B& backgroundColor)
    {
        _backgroundColor = backgroundColor;
    }
    
    inline ccColor3B& gebackgroundColor()
    {
        return _backgroundColor;
    }
    
protected:
    
    /**
     * 表示map的方向。是斜45还是直角还是六边形。
     * 目录只支持斜45
     */
    int _orientation;
    
    /**
     * 表示map的格子数。不是像素大小
     */
    Size _mapSize;
    
    /**
     * 表示map的每个格子的像素大小
     */
    Size _tileSize;
   
    /**
     * 表示map的的背景色
     */
    ccColor3B _backgroundColor;
    
    /**
     * map的layer信息
     */
    CCArray* _layers;
    
    /**
     * map的tile set信息
     */
    CCArray* _tilesets;
    
    /**
     * map的object group信息
     */
    CCArray* _objectGroups;

    /**
     * map的扩展属性
     */
    CCDictionary* _properties;
   
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAPINFO_H_
