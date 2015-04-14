#include "ISOActiveSortLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOTileMap.h"
#include "../ISOInfos.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

enum ObjectType
{
    //静态物体
    kObjectTypeStatic,
    
    //动态物体
    kObjectTypeDynamic
};



ISOActiveSortLayer::ISOActiveSortLayer()
:_occlusion(NULL)
,_staticRootNode(NULL)
,_dynamicObjects(NULL)
,_staticObjects(NULL)
,_dynamicNodes(NULL)
{
	
}

ISOActiveSortLayer::~ISOActiveSortLayer()
{
    CC_SAFE_RELEASE_NULL(_occlusion);
    CC_SAFE_RELEASE_NULL(_staticRootNode);
    CC_SAFE_RELEASE_NULL(_staticObjects);
    CC_SAFE_RELEASE_NULL(_dynamicObjects);
    CC_SAFE_RELEASE_NULL(_dynamicNodes);
}

bool ISOActiveSortLayer::init()
{
    if (ISOActiveLayer::init()) {
        
        _occlusion=new SortZIndex();
        _occlusion->init();
        
        _dynamicObjects=new CCArray();
        
        _staticObjects=new CCArray();
        
        _dynamicNodes=new CCArray();
        
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
    if (_objects) {
        Ref* pObj=NULL;
        ISOObjectInfo* mapObject=NULL;
        CCARRAY_FOREACH(_objects, pObj){
            mapObject=static_cast<ISOObjectInfo*>(pObj);
            if (mapObject->getGid()!=0 && mapObject->getVisible()) {
                
                CCSprite* mapObjectSprite=createObject(mapObject->getGid(), mapObject->getPosition());
                
                addToOcclusion(mapObjectSprite,mapObject);
            }
        }
        
        //保存当前的静态物体的遮挡关系树
        setStaticRootNode(_occlusion->getRootNode()->clone());
        
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
            _staticObjects->addObject(mapObject);
            _occlusion->insert(createSortZIndexNode(mapObject, mapObjectDef));
            break;
            
        case kObjectTypeDynamic:
            _dynamicObjects->addObject(mapObject);
            _dynamicNodes->addObject(createSortZIndexNode(mapObject, mapObjectDef));
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
    Ref* pObj=NULL;
    SortZIndexNode* node=NULL;
    CCNode* mapObject=NULL;
    
    CCARRAY_FOREACH(_dynamicNodes, pObj){
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
        _occlusion->insert(node);
    }
}

NS_CC_YHGE_ISOMETRIC_END
