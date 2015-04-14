#include "ISOTileMap.h"
#include "base/ISOTileset.h"
#include "layers/ISOCoordinateLayer.h"
#include "IsoTileUtils.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static const int kCoordLineZOrder=10000;

ISOTileMap::ISOTileMap()
:m_pObjectGroups(NULL)
,m_pDynamicGroup(NULL)
,m_pTilesetGroup(NULL)
,m_useDynamicGroup(false)
,m_dynamicComponents(NULL)
{
	
}

ISOTileMap::~ISOTileMap()
{
    CC_SAFE_RELEASE_NULL(m_pTilesetGroup);
    CC_SAFE_RELEASE_NULL(m_pObjectGroups);
    CC_SAFE_RELEASE_NULL(m_pDynamicGroup);
	CC_SAFE_RELEASE_NULL(m_dynamicComponents);
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
        m_pObjectGroups=new CCArray();
        
        m_dynamicComponents=new CCArray();
        
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
//    //layerInfo->m_bOwnTiles = false;
//    //layer->setupTiles();
//    //
//    //return layer;
//	return NULL;
//}
//
//ISOTilesetInfo * ISOTileMap::tilesetForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
//{
//    CCSize size = layerInfo->m_tLayerSize;
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
//                        unsigned int gid = layerInfo->m_pTiles[ pos ];
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
//                            if( (gid & kCCFlippedMask) >= tileset->m_uFirstGid )
//                                return tileset;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    
//    // If all the tiles are 0, return empty tileset
//    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->m_sName.c_str());
//    return NULL;
//}
//
//void ISOTileMap::buildWithMapInfo(ISOMapInfo* mapInfo)
//{
//    m_tMapSize = mapInfo->getMapSize();
//    m_tTileSize = mapInfo->getTileSize();
//    m_nMapOrientation = mapInfo->getOrientation();
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
//            if (layerInfo && layerInfo->m_bVisible)
//            {
//                ISOTileLayer *child = parseLayer(layerInfo, mapInfo);
//                addChild((CCNode*)child, idx, idx);
//                
//                // update content size with the max size
//                const CCSize& childSize = child->getContentSize();
//                CCSize currentSize = this->getContentSize();
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
    
    if (m_pTilesetGroup && m_pTilesetGroup->tilesetCount()>0){
        CCArray* pTilesets=m_pTilesetGroup->getTilesets();
        Ref* pObj = NULL;
        ISOTileset* tileset =NULL;
        
        CCARRAY_FOREACH(pTilesets, pObj)
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
    
    if (m_pObjectGroups && m_pObjectGroups->count()>0)
    {
        ISOObjectGroup* objectGroup = NULL;
        Ref* pObj = NULL;
        
        CCARRAY_FOREACH(m_pObjectGroups, pObj)
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

void ISOTileMap::scrollLayer(const CCPoint& pos)
{
	CCPoint localPos=ccpMult(pos, 1/this->getScale());

	if (m_useDynamicGroup){
		//如果使用动态组，则只更新动态组	
		m_pDynamicGroup->scroll(localPos);

	}else{

		Ref* pObj=NULL;
		ISOLayer* layer;

		CCARRAY_FOREACH(m_layers, pObj){
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
	coordLayer->setMapWidth((int)m_tMapSize.width);
	coordLayer->setMapHeight((int)m_tMapSize.height);
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
	m_dynamicComponents->addObject(dynamicComponent);
}

/**
 * 设置动态组
 */
void ISOTileMap::setupDynamicGroup()
{
    if (m_useDynamicGroup) {
        ISODynamicGroup* dynamicGroup=new ISODynamicGroup();
        dynamicGroup->init();
        
        //设置需呀的行列值
        CCSize visibleSize=this->getVisibleSize();
        
        int componentTileColumn=0;
        int componentTileRow=0;
        
        ISOTileUtils::calcDynamicComponetSize(visibleSize,m_tTileSize,&componentTileColumn,&componentTileRow);
        
        dynamicGroup->setComponentTileColumn(componentTileColumn);
        dynamicGroup->setComponentTileRow(componentTileRow);
        
        setupDynamicGroup(dynamicGroup,CCPointZero);
        
        dynamicGroup->release();
    }
}

/**
 * 设置动态组
 */
void ISOTileMap::setupDynamicGroup(ISODynamicGroup* dynamicGroup,const CCPoint& offset)
{
    if (m_useDynamicGroup) {
        //TODO 检查每个组件是不是一样的设置，主要是它们的组件的行列值
        setDynamicGroup(dynamicGroup);

        dynamicGroup->initOffset(offset);
        
        dynamicGroup->calcComponentsCount();
        
        Ref* pObj=NULL;
        ISODynamicComponent* dynamicComponent=NULL;

        CCARRAY_FOREACH(m_dynamicComponents,pObj){
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
    if (m_useDynamicGroup) {
        //TODO
    }
}

void ISOTileMap::setUseDynamicGroup(bool useDynamicGroup)
{
    m_useDynamicGroup = useDynamicGroup;

	//if (m_useDynamicGroup!=useDynamicGroup)
	//{
	//	m_useDynamicGroup = useDynamicGroup;

	//	if (m_useDynamicGroup)
	//	{
	//		if (m_pDynamicGroup==NULL)
	//		{
	//			m_pDynamicGroup=new ISODynamicGroup();
	//			m_pDynamicGroup->init();
	//		}
	//	}else{
	//		setDynamicGroup(NULL);
	//	}
	//}
}

NS_CC_YHGE_ISOMETRIC_END
