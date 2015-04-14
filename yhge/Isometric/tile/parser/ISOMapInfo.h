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
    
    virtual void setOrientation(int nOrientation);
    virtual int getOrientation();
    
    virtual void setMapSize(const CCSize& tMapSize);
    virtual const CCSize& getMapSize();
    
    virtual void setTileSize(const CCSize& tTileSize);
    virtual const CCSize& getTileSize();
    
    virtual void setLayers(CCArray* pLayers);
    virtual CCArray* getLayers();
    
    virtual void setTilesets(CCArray* pTilesets);
    virtual CCArray* getTilesets();
    
    virtual void setObjectGroups(CCArray* pObjectGroups);
    virtual CCArray* getObjectGroups();
       
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
        
    inline void setBackgroundColor(ccColor3B& tBackgroundColor)
    {
        m_tBackgroundColor = tBackgroundColor;
    }
    
    inline ccColor3B& getBackgroundColor()
    {
        return m_tBackgroundColor;
    }
    
protected:
    
    /**
     * 表示map的方向。是斜45还是直角还是六边形。
     * 目录只支持斜45
     */
    int m_nOrientation;
    
    /**
     * 表示map的格子数。不是像素大小
     */
    CCSize m_tMapSize;
    
    /**
     * 表示map的每个格子的像素大小
     */
    CCSize m_tTileSize;
   
    /**
     * 表示map的的背景色
     */
    ccColor3B m_tBackgroundColor;
    
    /**
     * map的layer信息
     */
    CCArray* m_pLayers;
    
    /**
     * map的tile set信息
     */
    CCArray* m_pTilesets;
    
    /**
     * map的object group信息
     */
    CCArray* m_pObjectGroups;

    /**
     * map的扩展属性
     */
    CCDictionary* m_pProperties;
   
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAPINFO_H_
