#include "ISOTileMap.h"
#include "base/ISOTileset.h"
#include "layers/ISOCoordinateLayer.h"

NS_CC_YHGE_BEGIN

static const int kCoordLineZOrder=10000;

ISOTileMap::ISOTileMap()
:m_tMapSize(CCSizeZero)
,m_pTileLayers(NULL)
,m_pObjectGroups(NULL)
,m_pProperties(NULL)
,m_pTileProperties(NULL)
,m_pDynamicGroup(NULL)
,m_pTilesetGroup(NULL)
,m_visibleSize(CCSizeZero)
,m_useDynamicGroup(false)
,m_pTileDynamicLayers(NULL)
{
	
}

ISOTileMap::~ISOTileMap()
{
    CC_SAFE_RELEASE_NULL(m_pTileLayers);
    CC_SAFE_RELEASE_NULL(m_pTilesetGroup);
    CC_SAFE_RELEASE_NULL(m_pProperties);
    CC_SAFE_RELEASE_NULL(m_pObjectGroups);
    CC_SAFE_RELEASE_NULL(m_pTileProperties);
    CC_SAFE_RELEASE_NULL(m_pDynamicGroup);
	CC_SAFE_RELEASE_NULL(m_pTileDynamicLayers);
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
    m_pTileLayers=new CCArray();
    m_pTileLayers->init();
    
    m_pObjectGroups=new CCArray();
    m_pObjectGroups->init();
    
    m_pProperties=new CCDictionary();
    
    m_visibleSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);

//    CCLayerColor* lc=CCLayerColor::create(ccc4(0,0,255,255), 600, 400);
//    addChild(lc);
	return true;
}

bool ISOTileMap::initWithXMLFile(const char *xmlFile)
{
    CCAssert(xmlFile != NULL && strlen(xmlFile)>0, "ISOTileMap: map file should not bi NULL");
    
    setContentSize(CCSizeZero);
    
//    ISOXMLParser *xmlParser = ISOXMLParser::formatWithXMLFile(xmlFile);
//    
//    ISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    if (! mapInfo)
//    {
//        return false;
//    }
//    CCAssert( mapInfo->getTilesets()->count() != 0, "ISOTileMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool ISOTileMap::initWithJSONFile(const char *jsonFile)
{
    CCAssert( false, "ISOTileMap::initWithJSONFile not support.");
    
    return true;
}

bool ISOTileMap::initWithXML(const char* xmlString, const char* resourcePath)
{
    setContentSize(CCSizeZero);
        
//    ISOXMLParser *xmlParser = ISOXMLParser::formatWithXML(xmlString, resourcePath);
//    ISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    CCAssert( mapInfo->getTilesets()->count() != 0, "ISOTileMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool ISOTileMap::initWithJSON(const char* jsonString, const char* resourcePath)
{
    CCAssert( false, "ISOTileMap::initWithJSON not support.");
    
    return true;
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
//        CCObject* pObj = NULL;
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
//        CCObject* pObj = NULL;
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

ISOTileset* ISOTileMap::tilesetNamed(const char* tilesetName)
{
    CCAssert(tilesetName != NULL && strlen(tilesetName) > 0, "Invalid tileset name!");
    
    if (m_pTilesetGroup && m_pTilesetGroup->tilesetCount()>0){
        CCArray* pTilesets=m_pTilesetGroup->getTilesets();
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pTilesets, pObj)
        {
            ISOTileset* tileset = dynamic_cast<ISOTileset*>(pObj);
            if(tileset)
            {
                if(0 == strcmp(tileset->getName(), tilesetName))
                {
                    return tileset;
                }
            }
        }
    }
    // layer not found
    return NULL;
}

ISOTileLayer * ISOTileMap::layerNamed(const char *layerName)
{
    CCAssert(layerName != NULL && strlen(layerName) > 0, "Invalid layer name!");
    
    if (m_pTileLayers && m_pTileLayers->count()>0){
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pTileLayers, pObj)
        {
            ISOTileLayer* layer = dynamic_cast<ISOTileLayer*>(pObj);
            if(layer)
            {
                if(0 == strcmp(layer->getLayerName(), layerName))
                {
                    return layer;
                }
            }
        }
    }
    // layer not found
    return NULL;
}

ISOObjectGroup * ISOTileMap::objectGroupNamed(const char *objectGroupName)
{
    CCAssert(objectGroupName != NULL && strlen(objectGroupName) > 0, "Invalid object group name!");
    
    if (m_pObjectGroups && m_pObjectGroups->count()>0)
    {
        ISOObjectGroup* objectGroup = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pObjectGroups, pObj)
        {
            objectGroup = dynamic_cast<ISOObjectGroup*>(pObj);
            if(objectGroup)
            {
                if(0 == strcmp(objectGroup->getName(), objectGroupName))
                {
                    return objectGroup;
                }
            }
        }
    }
    
    // objectGroup not found
    return NULL;
}

CCString* ISOTileMap::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void ISOTileMap::scrollLayer(const CCPoint& pos)
{
	CCPoint localPos=ccpMult(pos, 1/this->getScale());

	if (m_useDynamicGroup){
		//如果使用动态组，则只更新动态组	
		m_pDynamicGroup->scroll(localPos);

	}else{

		CCObject* pObj=NULL;
		ISOTileLayer* tileLayer;

		CCARRAY_FOREACH(m_pTileLayers, pObj){
			tileLayer=(ISOTileLayer*) pObj;
			tileLayer->scroll(localPos);
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


///**
// * for update component coordinate
// */
//void ISOTileMap::onUpdateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)
//{
//    CCLOG("ISOTileMap::updateComponentMapCoordinate");
//    
//    
//    //TODO other thing.
//    //1.标记地图哪些区域可以显示。
//    //2.通知子层更改组件的位置。
//
//}

CCSize ISOTileMap::getVisibleSize()
{
    if(m_fScaleX==0 || m_fScaleY==0) return m_visibleSize;
    
    return CCSizeMake(m_visibleSize.width/m_fScaleX, m_visibleSize.height/m_fScaleY);
}

void ISOTileMap::setUseDynamicGroup(bool useDynamicGroup)
{
	if (m_useDynamicGroup!=useDynamicGroup)
	{
		m_useDynamicGroup = useDynamicGroup;

		if (m_useDynamicGroup)
		{
			if (m_pDynamicGroup==NULL)
			{
				m_pDynamicGroup=new ISODynamicGroup();
				m_pDynamicGroup->init();
			}
		}else{
			setDynamicGroup(NULL);
		}
	}
}

NS_CC_YHGE_END
