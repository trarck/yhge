#include "ISOTileMap.h"
#include "base/ISOTileset.h"
#include "layers/ISOCoordinateLayer.h"
#include "IsoTileUtils.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static const int kCoordLineZOrder=10000;

ISOTileMap::ISOTileMap()
:_objectGroups(NULL)
,_pDynamicGroup(NULL)
,_tilesetGroup(NULL)
,_useDynamicGroup(false)
,_dynamicComponents(NULL)
{
	
}

ISOTileMap::~ISOTileMap()
{
    CC_SAFE_RELEASE_NULL(_tilesetGroup);
    CC_SAFE_RELEASE_NULL(_objectGroups);
    CC_SAFE_RELEASE_NULL(_pDynamicGroup);
	CC_SAFE_RELEASE_NULL(_dynamicComponents);
}

ISOTileMap * ISOTileMap::createWithXMLFile(const char *xmlFile)
{
    ISOTileMap *pRet = new ISOTileMap();
    if (pRet->initWithXMLFile(xmlFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOTileMap * ISOTileMap::createWithJSONFile(const char *jsonFile)
{
    ISOTileMap *pRet = new ISOTileMap();
    if (pRet->initWithJSONFile(jsonFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOTileMap* ISOTileMap::createWithXML(const char* tmxString, const char* resourcePath)
{
    ISOTileMap *pRet = new ISOTileMap();
    if (pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

ISOTileMap* ISOTileMap::createWithJSON(const char* jsonString, const char* resourcePath)
{
    ISOTileMap *pRet = new ISOTileMap();
    if (pRet->initWithJSON(jsonString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ISOTileMap::init()
{

    if (ISOMap::init()) {
        _objectGroups=new CCArray();
        
        _dynamicComponents=new CCArray();
        
        return true;
    }
    

    return false;
}

//=================build from info======================//
// protected
//ISOTileLayer * ISOTileMap::parseLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
//{
//    //ISOTilesetInfo *tileset = this->tilesetForLayer(layerInfo, mapInfo);
//    //ISOTileLayer *layer = ISOTileLayer::create(tileset, layerInfo, mapInfo);
//    //
//    //// tell the layerinfo to release the ownership of the tiles map.
//    //layerInfo->_ownTiles = false;
//    //layer->setutiles();
//    //
//    //return layer;
//	return NULL;
//}
//
//ISOTilesetInfo * ISOTileMap::tilesetForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
//{
//    Size size = layerInfo->_layerSize;
//    CCArray* tilesets = mapInfo->getTilesets();
//    if (tilesets && tilesets->count()>0)
//    {
//        ISOTilesetInfo* tileset = NULL;
//        Ref* pObj = NULL;
//        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
//        {
//            tileset = (ISOTilesetInfo*)pObj;
//            if (tileset)
//            {
//                for( unsigned int y=0; y < size.height; y++ )
//                {
//                    for( unsigned int x=0; x < size.width; x++ )
//                    {
//                        unsigned int pos = (unsigned int)(x + size.width * y);
//                        unsigned int gid = layerInfo->_tiles[ pos ];
//                        
//                        // gid are stored in little endian.
//                        // if host is big endian, then swap
//                        //if( o == CFByteOrderBigEndian )
//                        //    gid = CFSwapInt32( gid );
//                        /* We support little endian.*/
//                        
//                        // XXX: gid == 0 --> empty tile
//                        if( gid != 0 )
//                        {
//                            // Optimization: quick return
//                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
//                            if( (gid & kCCFlippedMask) >= tileset->_uFirstGid )
//                                return tileset;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    
//    // If all the tiles are 0, return empty tileset
//    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->_name.c_str());
//    return NULL;
//}
//
//void ISOTileMap::buildWithMapInfo(ISOMapInfo* mapInfo)
//{
//    _mapSize = mapInfo->gemapSize();
//    _tileSize = mapInfo->getileSize();
//    _nMapOrientation = mapInfo->getOrientation();
//    
//    this->setTileLayers(mapInfo->getLayers());
//    this->setObjectGroups( mapInfo->getObjectGroups());
//    this->setProperties(mapInfo->getProperties());
//    this->setTileProperties(mapInfo->getTileProperties());
//
//    this->buildMapLayers(mapInfo);
//}
//
//void ISOTileMap::buildMapLayers(ISOMapInfo* mapInfo)
//{
//    int idx=0;
//    
//    CCArray* layers = mapInfo->getLayers();
//    if (layers && layers->count()>0)
//    {
//        ISOLayerInfo* layerInfo = NULL;
//        Ref* pObj = NULL;
//        CCARRAY_FOREACH(layers, pObj)
//        {
//            layerInfo = (ISOLayerInfo*)pObj;
//            if (layerInfo && layerInfo->_visible)
//            {
//                ISOTileLayer *child = parseLayer(layerInfo, mapInfo);
//                addChild((CCNode*)child, idx, idx);
//                
//                // update content size with the max size
//                const Size& childSize = child->getContentSize();
//                Size currentSize = this->getContentSize();
//                currentSize.width = MAX( currentSize.width, childSize.width );
//                currentSize.height = MAX( currentSize.height, childSize.height );
//                this->setContentSize(currentSize);
//                
//                idx++;
//            }
//        }
//    }
//}

// public

ISOTileset* ISOTileMap::tilesetNamed(const std::string& tilesetName)
{
    CCAssert(tilesetName!="", "Invalid tileset name!");
    
    if (_tilesetGroup && _tilesetGroup->tilesetCount()>0){
        CCArray* tilesets=_tilesetGroup->getTilesets();
        Ref* pObj = NULL;
        ISOTileset* tileset =NULL;
        
        CCARRAY_FOREACH(tilesets, pObj)
        {
            tileset = dynamic_cast<ISOTileset*>(pObj);
            if(tileset)
            {
                if(tilesetName == tileset->getName())
                {
                    return tileset;
                }
            }
        }
    }
    // tileset not found
    return NULL;
}

ISOObjectGroup * ISOTileMap::objectGroupNamed(const std::string& objectGroupName)
{
    CCAssert(objectGroupName != "", "Invalid object group name!");
    
    if (_objectGroups && _objectGroups->count()>0)
    {
        ISOObjectGroup* objectGroup = NULL;
        Ref* pObj = NULL;
        
        CCARRAY_FOREACH(_objectGroups, pObj)
        {
            objectGroup = dynamic_cast<ISOObjectGroup*>(pObj);
            if(objectGroup)
            {
                if(objectGroupName == objectGroup->getName())
                {
                    return objectGroup;
                }
            }
        }
    }
    
    // objectGroup not found
    return NULL;
}

void ISOTileMap::scrollLayer(const Vec2& pos)
{
	Vec2 localPos=ccpMult(pos, 1/this->getScale());

	if (_useDynamicGroup){
		//如果使用动态组，则只更新动态组	
		_pDynamicGroup->scroll(localPos);

	}else{

		Ref* pObj=NULL;
		ISOLayer* layer;

		CCARRAY_FOREACH(_layers, pObj){
			layer=(ISOLayer*) pObj;
			layer->scroll(localPos);
		}
	}
}

/**
 * 显示地图的坐标线
 */
void ISOTileMap::showCoordLine()
{
	ISOCoordinateLayer* coordLayer=ISOCoordinateLayer::create();
	coordLayer->setMapWidth((int)_mapSize.width);
	coordLayer->setMapHeight((int)_mapSize.height);
	this->addChild(coordLayer,kCoordLineZOrder);
}

/**
 *检查某个单元是否可以通过
 */
bool ISOTileMap::isWorkable(float x,float y)
{
    //根据具体地图类型来实现。比如用某个层来标识路径情况。
    //如果地图上可移动物体是不能穿透，则也要算在路径里。
    return true;
}

//==============dynamic group===============//
	
/**
* 添加动态组件
* 如果动态组件不一样，可能会有多个组。目前只支持一个组
*/
void ISOTileMap::addDynamicComponent(ISODynamicComponent* dynamicComponent)
{
	_dynamicComponents->addObject(dynamicComponent);
}

/**
 * 设置动态组
 */
void ISOTileMap::setupDynamicGroup()
{
    if (_useDynamicGroup) {
        ISODynamicGroup* dynamicGroup=new ISODynamicGroup();
        dynamicGroup->init();
        
        //设置需呀的行列值
        Size visibleSize=this->getVisibleSize();
        
        int componentTileColumn=0;
        int componentTileRow=0;
        
        ISOTileUtils::calcDynamicComponetSize(visibleSize,_tileSize,&componentTileColumn,&componentTileRow);
        
        dynamicGroup->setComponentTileColumn(componentTileColumn);
        dynamicGroup->setComponentTileRow(componentTileRow);
        
        setupDynamicGroup(dynamicGroup,CCPointZero);
        
        dynamicGroup->release();
    }
}

/**
 * 设置动态组
 */
void ISOTileMap::setupDynamicGroup(ISODynamicGroup* dynamicGroup,const Vec2& offset)
{
    if (_useDynamicGroup) {
        //TODO 检查每个组件是不是一样的设置，主要是它们的组件的行列值
        setDynamicGroup(dynamicGroup);

        dynamicGroup->initOffset(offset);
        
        dynamicGroup->calcComponentsCount();
        
        Ref* pObj=NULL;
        ISODynamicComponent* dynamicComponent=NULL;

        CCARRAY_FOREACH(_dynamicComponents,pObj){
            dynamicComponent=static_cast<ISODynamicComponent*>(pObj);
            dynamicGroup->addDynamicComponent(dynamicComponent);
        }
    }
}

/**
 * 设置一些动态组
 */
void ISOTileMap::setupDynamicGroups()
{
    if (_useDynamicGroup) {
        //TODO
    }
}

void ISOTileMap::setUseDynamicGroup(bool useDynamicGroup)
{
    _useDynamicGroup = useDynamicGroup;

	//if (_useDynamicGroup!=useDynamicGroup)
	//{
	//	_useDynamicGroup = useDynamicGroup;

	//	if (_useDynamicGroup)
	//	{
	//		if (_pDynamicGroup==NULL)
	//		{
	//			_pDynamicGroup=new ISODynamicGroup();
	//			_pDynamicGroup->init();
	//		}
	//	}else{
	//		setDynamicGroup(NULL);
	//	}
	//}
}

NS_CC_YHGE_ISOMETRIC_END
