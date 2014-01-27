#ifndef YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_
#define YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Isometric/occlusion/SortZIndex.h>
#include "../ISOBases.h"
#include "../ISOInfos.h"
#include "ISOActiveLayer.h"

NS_CC_YHGE_BEGIN

/**
 * 活动层。
 * 提供场景活动元素的层
 * 使用遮挡排序来管理，活动元素。
 */
class ISOActiveSortLayer : public ISOActiveLayer {

public:
	
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
        CC_SAFE_RELEASE(m_occlusion);
        m_occlusion = occlusion;
    }
    
    inline SortZIndex* getOcclusion()
    {
        return m_occlusion;
    }
    
    inline void setStaticObjects(CCArray* staticObjects)
    {
        CC_SAFE_RETAIN(staticObjects);
        CC_SAFE_RELEASE(m_staticObjects);
        m_staticObjects = staticObjects;
    }
    
    inline CCArray* getStaticObjects()
    {
        return m_staticObjects;
    }
    
    inline void setDynamicObjects(CCArray* dynamicObjects)
    {
        CC_SAFE_RETAIN(dynamicObjects);
        CC_SAFE_RELEASE(m_dynamicObjects);
        m_dynamicObjects = dynamicObjects;
    }
    
    inline CCArray* getDynamicObjects()
    {
        return m_dynamicObjects;
    }
    
    inline void setStaticRootNode(SortZIndexNode* staticRootNode)
    {
        CC_SAFE_RETAIN(staticRootNode);
        CC_SAFE_RELEASE(m_staticRootNode);
        m_staticRootNode = staticRootNode;
    }
    
    inline SortZIndexNode* getStaticRootNode()
    {
        return m_staticRootNode;
    }
    
    inline void setDynamicNodes(CCArray* dynamicNodes)
    {
        CC_SAFE_RETAIN(dynamicNodes);
        CC_SAFE_RELEASE(m_dynamicNodes);
        m_dynamicNodes = dynamicNodes;
    }
    
    inline CCArray* getDynamicNodes()
    {
        return m_dynamicNodes;
    }
    
protected:
    
    //对象添加到遮挡处理器中
    virtual void addToOcclusion(CCNode* mapObject,ISOObjectInfo* mapObjectDef);
    
    //创建排序结点
    virtual SortZIndexNode* createSortZIndexNode(CCNode* mapObject,ISOObjectInfo* mapObjectDef);
    
    //更新动态物体的ZOrder
    virtual void updateDynamicObjectsZOrder(bool updateNode=true);
    
protected:

    //遮挡处理
    SortZIndex* m_occlusion;
    
    //所有静态物体的遮挡关系树
    SortZIndexNode* m_staticRootNode;
    
    //静态物体
    CCArray* m_staticObjects;
    
    //动态物体
    CCArray* m_dynamicObjects;
    
    //动态元素结点
    CCArray* m_dynamicNodes;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOACTIVESORTLAYER_H_
