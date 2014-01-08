#ifndef YHGE_ISOMETRIC_ISOTILEMAPBUILDER_H_
#define YHGE_ISOMETRIC_ISOTILEMAPBUILDER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "../ISOInfos.h"

#include "../base/ISOTilesetGroup.h"
#include "../layers/ISOTileLayer.h"
#include "../layers/ISODynamicComponent.h"
#include "../layers/ISOObjectGroup.h"


NS_CC_YHGE_BEGIN

class ISOTileMap;
/**
 * 地图分为二种层。
 * 一种是图块图层，通常只显示图形，覆盖整个地图坐标。通常坐为背景层或地表层，主要是静态的物体。
 * 一种是对象层，只记录出层的对象，对象包含出现在地图上的坐标和大小等。通常坐为中间层，显示人物，怪物，一些做为背景动态的东西，如动态水面，地上的火焰。
 * 
 * 注意:这里的实现和tmx里的实现不太一样,
 * tmx里tile layer是直接添加到显示子列表里，object layer做为属性，具体怎么用由游戏决定。
 * 这里都做为属性，具体怎么用由游戏来决定
 */
class ISOTileMapBuilder : public CCObject{

public:
	
	ISOTileMapBuilder();
    
	~ISOTileMapBuilder();
    
    virtual bool init();
    
    virtual bool init(ISOTileMap* pMap);
    
    virtual void buildWithMapInfo(ISOMapInfo* mapInfo);
    
    /**
     * 构建tilesets
     */
    virtual void buildMapTilesets(ISOMapInfo* mapInfo);
    
    /**
     * 构建tileset
     */
    virtual void buildMapTileset(ISOTilesetInfo* tilesetInfo,ISOTilesetGroup* tilesetGroup);
    
    /**
     * 构建tiles
     */
    virtual void buildMapTiles(CCArray* tileInfos,ISOTileset* tileset);
    
    /**
     * 设置tile属性
     */
    virtual void setMapTilesProperties(CCArray* tileInfos,ISOTileset* tileset);
    /**
     * 构建object groups
     */
    virtual void buildMapObjectGroups(ISOMapInfo* mapInfo);
    /**
     * 构建objects
     */
    virtual void buildMapObjects(CCArray* objects,ISOObjectGroup* objectGroup);
    /**
     * 构建map object
     */
    virtual void buildMapObject(ISOObjectInfo* objectInfo,ISOObjectGroup* objectGroup);
    
    /**
     * 构建tile layer
     */
    virtual void buildMapLayers(ISOMapInfo* mapInfo);
    
    virtual void buildMapLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo);

    virtual void setLayerAttribute(ISOTileLayer* tileLayer,ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo);
    
    virtual ISOTileset * tilesetForLayer(ISOLayerInfo *layerInfo);
    
    virtual ISOTilesetInfo * tilesetInfoForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo);
    
public:
    
    inline void setMap(ISOTileMap* pMap){
        m_pMap=pMap;
    }
    
    inline ISOTileMap* getMap(){
        return m_pMap;
    }
    
    inline void setMapLayerType(unsigned int uMapLayerType)
    {
        m_uMapLayerType = uMapLayerType;
    }
    
    inline unsigned int getMapLayerType()
    {
        return m_uMapLayerType;
    }
   
public:
    
    enum BuildMapLayerType{
        NormalLayerType,
        DynamicLayerType,
        BatchLayerType,
		BatchDynamicLayerType
    };
    
protected:
    
    ISOTileMap* m_pMap;
    
    unsigned int m_uMapLayerType;
    
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILEMAPBUILDER_H_
