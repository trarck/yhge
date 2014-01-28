#include "ISOActiveSortLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include <yhge/Isometric/ISOStaticCoordinate.h>
#include "../ISOTileMap.h"
#include "../ISOInfos.h"

NS_CC_YHGE_BEGIN

enum ObjectType
{
    //静态物体
    kObjectTypeStatic,
    
    //动态物体
    kObjectTypeDynamic
};



ISOActiveSortLayer::ISOActiveSortLayer()
:m_occlusion(NULL)
,m_staticRootNode(NULL)
,m_dynamicObjects(NULL)
,m_staticObjects(NULL)
,m_dynamicNodes(NULL)
{
	
}

ISOActiveSortLayer::~ISOActiveSortLayer()
{
    CC_SAFE_RELEASE_NULL(m_occlusion);
    CC_SAFE_RELEASE_NULL(m_staticRootNode);
    CC_SAFE_RELEASE_NULL(m_staticObjects);
    CC_SAFE_RELEASE_NULL(m_dynamicObjects);
    CC_SAFE_RELEASE_NULL(m_dynamicNodes);
}

bool ISOActiveSortLayer::init()
{
    if (ISOActiveLayer::init()) {
        
        m_occlusion=new SortZIndex();
        m_occlusion->init();
        
        m_dynamicObjects=new CCArray();
        
        m_staticObjects=new CCArray();
        
        m_dynamicNodes=new CCArray();
        
        return true;
    }
    
	return false;
}

ISOActiveSortLayer* ISOActiveSortLayer::create()
{
    ISOActiveSortLayer* pRet=new ISOActiveSortLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

/**
 * 设置层
 */
void ISOActiveSortLayer::setupLayer()
{
    ISOActiveLayer::setupLayer();
}

void ISOActiveSortLayer::releaseLayer()
{
    ISOActiveLayer::releaseLayer();
}

void ISOActiveSortLayer::setupObjects()
{
    if (m_objects) {
        CCObject* pObj=NULL;
        ISOObjectInfo* mapObject=NULL;
        CCARRAY_FOREACH(m_objects, pObj){
            mapObject=static_cast<ISOObjectInfo*>(pObj);
            if (mapObject->getGid()!=0 && mapObject->getVisible()) {
                
                CCSprite* mapObjectSprite=createObject(mapObject->getGid(), mapObject->getPosition());
                
                addToOcclusion(mapObjectSprite,mapObject);
            }
        }
        
        //保存当前的静态物体的遮挡关系树
        setStaticRootNode(m_occlusion->getRootNode()->clone());
        
        //把动态元素也加入进去
        updateDynamicObjectsZOrder(false);
    }
}

//对象添加到遮挡处理器中
void ISOActiveSortLayer::addToOcclusion(CCNode* mapObject,ISOObjectInfo* mapObjectDef)
{
    //取得对象的类型
    std::string objectTypeStr=mapObjectDef->getType();
    int objectType=kObjectTypeStatic;//默认为静态对象
    
    if (objectTypeStr!="") {
        objectType=atoi(objectTypeStr.c_str());
    }
    
    //按对象类型处理元素
    switch (objectType) {
        case kObjectTypeStatic:
            m_staticObjects->addObject(mapObject);
            m_occlusion->insert(createSortZIndexNode(mapObject, mapObjectDef));
            break;
            
        case kObjectTypeDynamic:
            m_dynamicObjects->addObject(mapObject);
            m_dynamicNodes->addObject(createSortZIndexNode(mapObject, mapObjectDef));
            break;
        default:
            break;
    }
}

//创建排序结点
SortZIndexNode* ISOActiveSortLayer::createSortZIndexNode(CCNode* mapObject,ISOObjectInfo* mapObjectDef)
{
    SortZIndexNode* node=new SortZIndexNode();
    node->setEntity(mapObject);
    node->setRect(CCRectMake(mapObject->getPosition().x,mapObjectDef->getPosition().y, mapObjectDef->getSize().width, mapObjectDef->getSize().height));
    
    node->autorelease();
    
    return node;
}

//更新动态物体的ZOrder
void ISOActiveSortLayer::updateDynamicObjectsZOrder(bool updateNode)
{
    CCObject* pObj=NULL;
    SortZIndexNode* node=NULL;
    CCNode* mapObject=NULL;
    
    CCARRAY_FOREACH(m_dynamicNodes, pObj){
        node=static_cast<SortZIndexNode*>(pObj);
        if (updateNode) {
            mapObject=static_cast<CCNode*>(node->getEntity());
            CCRect nodeRect=node->getRect();
            
            node->reset();
            node->setEntity(mapObject);
            
            //更新位置，直接把屏幕坐标转成地图坐标，根据不同的实现，这里可能不同
            nodeRect.origin=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(mapObject->getPosition()));
            node->setRect(nodeRect);
        }
        m_occlusion->insert(node);
    }
}

NS_CC_YHGE_END
