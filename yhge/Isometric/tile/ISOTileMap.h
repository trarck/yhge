//
//  AstarNode.h
//  isometric
//
#ifndef YHGE_ISOMETRIC_ISOTILEMAP_H_
#define YHGE_ISOMETRIC_ISOTILEMAP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

#include "ISOTileInterfaces.h"
#include "base/ISOTilesetGroup.h"
#include "base/ISOObjectGroup.h"
#include "layers/ISOTileLayer.h"
//#include "ISOXMLParser.h"
#include "layers/ISODynamicGroup.h"

NS_CC_YHGE_BEGIN

/**
 * 地图分为二种层。
 * 一种是图块图层，通常只显示图形，覆盖整个地图坐标。通常坐为背景层或地表层，主要是静态的物体。
 * 一种是对象层，只记录出层的对象，对象包含出现在地图上的坐标和大小等。通常坐为中间层，显示人物，怪物，一些做为背景动态的东西，如动态水面，地上的火焰。
 * 
 * 注意:这里的实现和tmx里的实现不太一样,
 * tmx里tile layer是直接添加到显示子列表里，object layer做为属性，具体怎么用由游戏决定。
 * 这里都做为属性，具体怎么用由游戏来决定
 * 
 * batch compoent>componet>batch>normal
 * 关于layer层的优化。
 * 上层的layer会挡住下层的layer所以只需要显示上层的layer块。如果上层是透明的，那么可以只渲染上层的元素。但是透明的就不可以使用，如果不显示下层，会出现空洞。
 */
class ISOTileMap : public CCNode{

public:
	
	ISOTileMap();
    
	~ISOTileMap();
    
    static ISOTileMap* createWithXMLFile(const char* xmlFile);
    
    static ISOTileMap* createWithXML(const char* xmlString,const char* resourcePath);
    
    static ISOTileMap* createWithJSONFile(const char* mapFile);
    
    static ISOTileMap* createWithJSON(const char* jsonString,const char* resourcePath);
	
    bool init();
    
    bool initWithXMLFile(const char* xmlFile);
    
    bool initWithJSONFile(const char* jsonFile);
    
    bool initWithXML(const char* xmlString,const char* resourcePath);
    
    bool initWithJSON(const char* jsonString,const char* resourcePath);
    
    /**
     * 取得贴图
     */
	ISOTileset* tilesetNamed(const char* tilesetName);
    
    /**
     * 取得普通层
     */
	ISOTileLayer* layerNamed(const char* layerName);
    
    /**
     * 取得对象层
     */
    ISOObjectGroup* objectGroupNamed(const char *objectGroupName);
    
    /**
     * 取得属性
     */
	CCString *propertyNamed(const char *propertyName);
    
    /**
     * 通知layer，地图的显示位置改变。
     * 有可能是map的位置改变，有可能是game world改变引起
     */
    void scrollLayer(const CCPoint& pos);

	/**
	 * 显示地图的坐标线
	 */
	void showCoordLine();
    
public://==============属性===============//
	
	inline void setMapSize(CCSize tMapSize)
	{
		m_tMapSize = tMapSize;
	}

	inline CCSize getMapSize()
	{
		return m_tMapSize;
	}

	inline void setTileSize(const CCSize& tTileSize)
	{
		m_tTileSize = tTileSize;
	}

	inline const CCSize& getTileSize()
	{
		return m_tTileSize;
	}

	inline void setName(const char* pName)
	{
		m_pName = pName;
	}

	inline const char* getName()
	{
		return m_pName.c_str();
	}

	inline void setMapOrientation(int nMapOrientation)
	{
		m_nMapOrientation = nMapOrientation;
	}

	inline int getMapOrientation()
	{
		return m_nMapOrientation;
	}

	inline void setTileLayers(CCArray* pTileLayers)
	{
		CC_SAFE_RETAIN(pTileLayers);
		CC_SAFE_RELEASE(m_pTileLayers);
		m_pTileLayers = pTileLayers;
	}

	inline CCArray* getTileLayers()
	{
		return m_pTileLayers;
	}

	inline void setObjectGroups(CCArray* pObjectGroups)
	{
		CC_SAFE_RETAIN(pObjectGroups);
		CC_SAFE_RELEASE(m_pObjectGroups);
		m_pObjectGroups = pObjectGroups;
	}

	inline CCArray* getObjectGroups()
	{
		return m_pObjectGroups;
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

	inline void setIdentifier(int nIdentifier)
	{
		m_nIdentifier=nIdentifier;
	}

	inline int getIdentifier()
	{
		return m_nIdentifier;
	}

	inline void setTileProperties(CCDictionary* pTileProperties)
	{
		CC_SAFE_RETAIN(pTileProperties);
		CC_SAFE_RELEASE(m_pTileProperties);
		m_pTileProperties = pTileProperties;
	}

	inline CCDictionary* getTileProperties()
	{
		return m_pTileProperties;
	}

	inline void setTilesetGroup(ISOTilesetGroup* pTilesetGroup)
	{
		CC_SAFE_RETAIN(pTilesetGroup);
		CC_SAFE_RELEASE(m_pTilesetGroup);
		m_pTilesetGroup = pTilesetGroup;
	}

	inline ISOTilesetGroup* getTilesetGroup()
	{
		return m_pTilesetGroup;
	}
    
    inline void setVisibleSize(const CCSize& visibleSize)
    {
        m_visibleSize = visibleSize;
    }
    
    CCSize getVisibleSize();

	void setDynamicGroup(ISODynamicGroup* dynamicGroup)
	{
		CC_SAFE_RETAIN(dynamicGroup);
		CC_SAFE_RELEASE(m_pDynamicGroup);
		m_pDynamicGroup = dynamicGroup;
	}

	ISODynamicGroup* getDynamicGroup()
	{
		return m_pDynamicGroup;
	}

	void setUseDynamicGroup(bool useDynamicGroup);

	bool isUseDynamicGroup()
	{
		return m_useDynamicGroup;
	}

	void setTileDynamicLayers(CCArray* tileDynamicLayers)
	{
		CC_SAFE_RETAIN(tileDynamicLayers);
		CC_SAFE_RELEASE(m_pTileDynamicLayers);
		m_pTileDynamicLayers = tileDynamicLayers;
	}

	CCArray* getTileDynamicLayers()
	{
		return m_pTileDynamicLayers;
	}
    
protected:
    
//    virtual ISOTileLayer * parseLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo);
//    
//    virtual ISOTilesetInfo * tilesetForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo);
//    
//    virtual void buildWithMapInfo(ISOMapInfo* mapInfo);
//    
//    /**
//     * 主要是构建tile layer
//     */
//    virtual void buildMapLayers(ISOMapInfo* mapInfo);
    
protected:
    /**
     * 地图大小，格子数，单位为格子。
     */
	CCSize m_tMapSize;
    
    /**
     * 地图格子大小。
     */
    CCSize m_tTileSize;
    
    /**
     * 地图名称
     */
    std::string m_pName;
    
    /**
     * 地图编号
     */
    int m_nIdentifier;
    
    /**
     * 地图类型
     */
    int m_nMapOrientation;
    
    /**
     * 图块合集
     */
    ISOTilesetGroup* m_pTilesetGroup;
    
    /**
     * 对像分组
     */
    CCArray* m_pTileLayers;
    
    /**
     * 对像分组
     */
    CCArray* m_pObjectGroups;
    
    /**
     * 属性列表
     */
    CCDictionary* m_pProperties;
    
    /**
     * tile properties
     */
    CCDictionary* m_pTileProperties;
    
    /**
     * 地图的可视区域
     */
    CCSize m_visibleSize;
    
    /**
     * 管理动态层的组件
	 * 如果有多个动态层，统一管理会减少计算量。
     */
    ISODynamicGroup* m_pDynamicGroup;
   
	bool m_useDynamicGroup;

	/**
     * 动态layers
     */
    CCArray* m_pTileDynamicLayers;
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_IOSTILEMAP_H_
