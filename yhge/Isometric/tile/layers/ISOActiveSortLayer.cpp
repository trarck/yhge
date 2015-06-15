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
{
	
}

ISOActiveSortLayer::~ISOActiveSortLayer()
{
    CC_SAFE_RELEASE_NULL(_occlusion);
    CC_SAFE_RELEASE_NULL(_staticRootNode);
}

bool ISOActiveSortLayer::init()
{
    if (ISOActiveLayer::init()) {
        
        _occlusion=new SortZIndex();
        _occlusion->init();
               
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
    if (!_objects.empty()) {
		ISOObjectInfo* objInfo = NULL;
		for (ISOObjectInfoVector::iterator iter = _objects.begin(); iter != _objects.end(); ++iter){
			objInfo = *iter;
			if (objInfo->getGid() != 0 && objInfo->getVisible()) {

				Sprite* mapObjectSprite = createObject(objInfo->getGid(), objInfo->getPosition());

				addToOcclusion(mapObjectSprite, objInfo);
			}
		}
        
        //保存当前的静态物体的遮挡关系树
        setStaticRootNode(_occlusion->getRootNode()->clone());
        
        //把动态元素也加入进去
        updateDynamicObjectsZOrder(false);
    }
}

//对象添加到遮挡处理器中
void ISOActiveSortLayer::addToOcclusion(Node* mapObject,ISOObjectInfo* mapObjectDef)
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
            _staticObjects.pushBack(mapObject);
            _occlusion->insert(createSortZIndexNode(mapObject, mapObjectDef));
            break;
            
        case kObjectTypeDynamic:
            _dynamicObjects.pushBack(mapObject);
            _dynamicNodes.pushBack(createSortZIndexNode(mapObject, mapObjectDef));
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
    SortZIndexNode* node=NULL;
    Node* mapObject=NULL;
    
	for (SortZIndexNodeVector::iterator iter = _dynamicNodes.begin(); iter != _dynamicNodes.end();++iter){
		node = *iter;
		if (updateNode) {
			mapObject = static_cast<Node*>(node->getEntity());
			Rect nodeRect = node->getRect();

			node->reset();
			node->setEntity(mapObject);

			//更新位置，直接把屏幕坐标转成地图坐标，根据不同的实现，这里可能不同
			nodeRect.origin = YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(mapObject->getPosition()));
			node->setRect(nodeRect);
		}
		_occlusion->insert(node);
	}
}

NS_CC_YHGE_ISOMETRIC_END
