#ifndef YHGE_ISOMETRIC_ISOMAPINFO_H_
#define YHGE_ISOMETRIC_ISOMAPINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOLayerInfo.h"
#include "ISOTilesetInfo.h"
#include "ISOObjectGroupInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图的信息
 * 主要是layers和objectGroups。
 */
class ISOMapInfo : public Ref{

public:
	typedef Vector<ISOLayerInfo*> ISOLayerInfoVector;
	typedef Vector<ISOTilesetInfo*> ISOTilesetInfoVector;
	typedef Vector<ISOObjectGroupInfo*> ISOObjectGroupInfoVector;

    ISOMapInfo();
    
    ~ISOMapInfo();
    
    virtual bool init();
    
    virtual void setOrientation(int orientation);
    virtual int getOrientation();
    
    virtual void setMapSize(const Size& mapSize);
    virtual const Size& getMapSize();
    
    virtual void setTileSize(const Size& tileSize);
    virtual const Size& getTileSize();
    
	virtual void setLayers(const ISOLayerInfoVector& layers);
	virtual ISOLayerInfoVector& getLayers();
    
	virtual void setTilesets(const ISOTilesetInfoVector& tilesets);
	virtual ISOTilesetInfoVector& getTilesets();
    
	virtual void setObjectGroups(const ISOObjectGroupInfoVector& objectGroups);
	virtual ISOObjectGroupInfoVector& getObjectGroups();
       
    virtual void setProperties(const ValueMap& properties);
    virtual ValueMap& getProperties();
        
    inline void setBackgroundColor(Color3B& backgroundColor)
    {
        _backgroundColor = backgroundColor;
    }
    
    inline Color3B& getBackgroundColor()
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
    Color3B _backgroundColor;
    
    /**
     * map的layer信息
     */
	ISOLayerInfoVector& _layers;
    
    /**
     * map的tile set信息
     */
	ISOTilesetInfoVector _tilesets;
    
    /**
     * map的object group信息
     */
	ISOObjectGroupInfoVector _objectGroups;

    /**
     * map的扩展属性
     */
    ValueMap _properties;
   
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAPINFO_H_
