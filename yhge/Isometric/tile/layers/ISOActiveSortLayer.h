#ifndef YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_
#define YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/Isometric/occlusion/SortZIndex.h>
#include "../ISOBases.h"
#include "../ISOInfos.h"
#include "ISOActiveLayer.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 活动层。
 * 提供场景活动元素的层
 * 使用遮挡排序来管理，活动元素。
 */
class ISOActiveSortLayer : public ISOActiveLayer {

public:
	typedef Vector<Node*> MapObjectVector;
	typedef Vector<SortZIndexNode*> SortZIndexNodeVector;

	ISOActiveSortLayer();
    
	virtual ~ISOActiveSortLayer(void);
	
    virtual bool init();
    
    static ISOActiveSortLayer* create();

    /**
     * 设置层
     */
    virtual void setupLayer();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    

    /**
     * 初始化显示tiles
     */
    virtual void setupObjects();
    
public:
    
    inline void setOcclusion(SortZIndex* occlusion)
    {
        CC_SAFE_RETAIN(occlusion);
        CC_SAFE_RELEASE(_occlusion);
        _occlusion = occlusion;
    }
    
    inline SortZIndex* getOcclusion()
    {
        return _occlusion;
    }
    
	inline void setStaticObjects(const MapObjectVector& staticObjects)
    {
        _staticObjects = staticObjects;
    }
    
	inline MapObjectVector& getStaticObjects()
    {
        return _staticObjects;
    }
    
	inline void setDynamicObjects(const MapObjectVector& dynamicObjects)
    {
        _dynamicObjects = dynamicObjects;
    }
    
	inline MapObjectVector& getDynamicObjects()
    {
        return _dynamicObjects;
    }
    
    inline void setStaticRootNode(SortZIndexNode* staticRootNode)
    {
        CC_SAFE_RETAIN(staticRootNode);
        CC_SAFE_RELEASE(_staticRootNode);
        _staticRootNode = staticRootNode;
    }
    
    inline SortZIndexNode* getStaticRootNode()
    {
        return _staticRootNode;
    }
    
	inline void setDynamicNodes(const SortZIndexNodeVector& dynamicNodes)
    {
        _dynamicNodes = dynamicNodes;
    }
    
	inline SortZIndexNodeVector& getDynamicNodes()
    {
        return _dynamicNodes;
    }
    
protected:
    
    //对象添加到遮挡处理器中
    virtual void addToOcclusion(Node* mapObject,ISOObjectInfo* mapObjectDef);
    
    //创建排序结点
    virtual SortZIndexNode* createSortZIndexNode(Node* mapObject,ISOObjectInfo* mapObjectDef);
    
    //更新动态物体的ZOrder
    virtual void updateDynamicObjectsZOrder(bool updateNode=true);
    
protected:

    //遮挡处理
    SortZIndex* _occlusion;
    
    //所有静态物体的遮挡关系树
    SortZIndexNode* _staticRootNode;
    
    //静态物体
	MapObjectVector _staticObjects;
    
    //动态物体
	MapObjectVector _dynamicObjects;
    
    //动态元素结点
	SortZIndexNodeVector _dynamicNodes;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_
