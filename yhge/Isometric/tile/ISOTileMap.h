//
//  AstarNode.h
//  isometric
//
#ifndef YHGE_ISOMETRIC_ISOTILEMAP_H_
#define YHGE_ISOMETRIC_ISOTILEMAP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Isometric/ISOMap.h>

#include "ISOTileInterfaces.h"
#include "base/ISOTilesetGroup.h"
#include "base/ISOObjectGroup.h"
#include "layers/ISOTileLayer.h"
#include "layers/ISOObjectLayer.h"
#include "layers/ISOActiveLayer.h"
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
 *
 * 关于object group
 * 通常object group不是用于显示的，用来定义一些事件或地图上的特殊信息。
 * 如果地图上的元素要参与遮挡，则不能放在tile layer里。比如一堆火，一颗树。而这些必须放在一个层里。这个层就是ActiveLayer.
 */
class ISOTileMap : public ISOMap{

public:
	
	ISOTileMap();
    
	~ISOTileMap();
    
    static ISOTileMap* createWithXMLFile(const char* xmlFile);
    
    static ISOTileMap* createWithXML(const char* xmlString,const char* resourcePath);
    
    static ISOTileMap* createWithJSONFile(const char* mapFile);
    
    static ISOTileMap* createWithJSON(const char* jsonString,const char* resourcePath);
	
    bool init();
    
    /**
     * 取得贴图
     */
	ISOTileset* tilesetNamed(const std::string& tilesetName);
    
    /**
     * 取得对象层
     */
    ISOObjectGroup* objectGroupNamed(const std::string& objectGroupName);
    
    /**
     * 通知layer，地图的显示位置改变。
     * 有可能是map的位置改变，有可能是game world改变引起
     */
    void scrollLayer(const CCPoint& pos);

	/**
	 * 显示地图的坐标线
	 */
	void showCoordLine();
    
    /**
	 *检查某个单元是否可以通过
	 */
	virtual bool isWorkable(int x,int y);

	//==============dynamic group===============//
	
	/**
	 * 添加动态组件
	 * 如果动态组件不一样，可能会有多个组。目前只支持一个组
	 */
	void addDynamicComponent(ISODynamicComponent* dynamicComponent);

	/**
	 * 设置动态组
	 */
	void setupDynamicGroup();

	/**
	 * 设置动态组
	 */
	void setupDynamicGroup(ISODynamicGroup* dynamicGroup,const CCPoint& offset);

    /**
	 * 设置一些动态组
	 */
	void setupDynamicGroups();
    
    //==============active layer===============//
    


public://==============属性===============//

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

	void setDynamicComponents(CCArray* dynamicComponents)
	{
		CC_SAFE_RETAIN(dynamicComponents);
		CC_SAFE_RELEASE(m_dynamicComponents);
		m_dynamicComponents = dynamicComponents;
	}

	CCArray* getDynamicComponents()
	{
		return m_dynamicComponents;
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
     * 图块合集
     */
    ISOTilesetGroup* m_pTilesetGroup;
    
    /**
     * 对像分组
     */
    CCArray* m_pObjectGroups;
    
    /**
     * 管理动态层的组件
	 * 如果有多个动态层，统一管理会减少计算量。如果层数少，则性能发变不是很明显
     */
    ISODynamicGroup* m_pDynamicGroup;
   
	bool m_useDynamicGroup;

	/**
     * 需要集中管理的DynamicComponent
     */
    CCArray* m_dynamicComponents;
//    
//    /**
//     * 活动层。
//     * 不能是TileLayer
//     * 提供场景内活动元素的层
//     * 通常是在map的显示子结点
//     */
//    ISOActiveLayer* m_activeLayer;
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_IOSTILEMAP_H_
