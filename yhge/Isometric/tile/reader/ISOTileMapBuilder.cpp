#include "ISOTileMapBuilder.h"
#include "../ISOBases.h"
#include "../ISOLayers.h"
#include "../ISOTileMap.h"

NS_CC_YHGE_BEGIN

ISOTileMapBuilder::ISOTileMapBuilder()
:m_pMap(NULL)
,m_uMapLayerType(NormalLayerType)
,m_activeLayerName("ActiveLayer")
,m_activeLayerDefaultZOrder(99999)
,m_buildActiveLayer(false)
{
	
}

ISOTileMapBuilder::~ISOTileMapBuilder()
{

}

bool ISOTileMapBuilder::init()
{
    return true;
}

bool ISOTileMapBuilder::init(ISOTileMap* pMap)
{
    m_pMap=pMap;
    return true;
}

void ISOTileMapBuilder::buildWithMapInfo(ISOMapInfo* mapInfo)
{
    CCAssert(m_pMap!=NULL, "buildWithMapInfo m_pMap can't be null");
    m_pMap->setMapSize(mapInfo->getMapSize());
    m_pMap->setTileSize(mapInfo->getTileSize());
    m_pMap->setProperties(mapInfo->getProperties());
    
    this->buildMapTilesets(mapInfo);
    this->buildMapLayers(mapInfo);
    this->buildMapObjectGroups(mapInfo);
    
    if (m_buildActiveLayer) {
        this->setupMapActiveLayer(mapInfo);
    }
}

void ISOTileMapBuilder::buildMapTilesets(ISOMapInfo* mapInfo)
{
    
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        
        ISOTilesetGroup* tilesetGroup=new ISOTilesetGroup();
        tilesetGroup->init();
        
        ISOTilesetInfo* tilesetInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(tilesets, pObj)
        {
            tilesetInfo = (ISOTilesetInfo*)pObj;
            if (tilesetInfo)
            {
                buildMapTileset(tilesetInfo, tilesetGroup);
            }
        }
        
        m_pMap->setTilesetGroup(tilesetGroup);
        tilesetGroup->release();
    }
}

void ISOTileMapBuilder::buildMapTileset(ISOTilesetInfo* tilesetInfo,ISOTilesetGroup* tilesetGroup)
{
    
    ISOTileset* tileset=new ISOTileset();
    tileset->init();
    
    tileset->setName(tilesetInfo->getName());
    tileset->setFirstGid(tilesetInfo->getFirstGid());
    tileset->setTileSize(tilesetInfo->getTileSize());
    tileset->setTileSpacing(tilesetInfo->getSpacing());
    tileset->setMargin(tilesetInfo->getMargin());
    tileset->setTileOffset(tilesetInfo->getTileOffset());
    tileset->setProperties(tilesetInfo->getProperties());

    const char* imageSource=tilesetInfo->getImageSource();
    
    if(imageSource){
        tileset->setImageSource(tilesetInfo->getImageSource());
        tileset->setImageSize(tilesetInfo->getImageSize());
        tileset->loadFromImageSource();
        //设置抗锯齿.否则图块会有缝隙。
        if(tileset->getTexture())
            tileset->getTexture()->setAliasTexParameters();
        
        CCArray* tileInfos=tilesetInfo->getTiles();
        if(tileInfos){
            setMapTilesProperties(tileInfos,tileset);
        }
    }else{
        CCArray* tileInfos=tilesetInfo->getTiles();
        if(tileInfos){
            buildMapTiles(tileInfos, tileset);
        }
    }
    
    tilesetGroup->addTileset(tileset);
    tileset->release();
}

void ISOTileMapBuilder::buildMapTiles(CCArray* tileInfos,ISOTileset* tileset)
{
    CCAssert(tileInfos, "buildMapTiles tiles must non't be null");
    CCObject* pObj;

    CCARRAY_FOREACH(tileInfos, pObj){
        ISOTileInfo* tileInfo=(ISOTileInfo*)pObj;
        
        if(tileInfo->getImageSource()){
            unsigned int tileId=tileInfo->getId();
            
            CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(tileInfo->getImageSource());
            
            ISOTile* tile=new ISOTile();
            tile->init(tileId, tileset, pTexture);
            tile->setProperties(tileInfo->getProperties());
            tileset->addTile(tile);
            
            tile->release();
        }
    }
}

void ISOTileMapBuilder::setMapTilesProperties(CCArray* tileInfos,ISOTileset* tileset)
{
    CCAssert(tileInfos, "setMapTilesProperties tiles must non't be null");
    CCObject* pObj;
    
    CCARRAY_FOREACH(tileInfos, pObj){
        ISOTileInfo* tileInfo=(ISOTileInfo*)pObj;
        ISOTile* tile=tileset->tileForId(tileInfo->getId());
        tile->setProperties(tileInfo->getProperties());
    }
}


void ISOTileMapBuilder::buildMapLayers(ISOMapInfo* mapInfo)
{
    int idx=0;
    
    CCArray* layerInfos = mapInfo->getLayers();
    if (layerInfos && layerInfos->count()>0)
    {
        ISOLayerInfo* layerInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(layerInfos, pObj)
        {
            layerInfo = (ISOLayerInfo*)pObj;
            if (layerInfo && layerInfo->getVisible() && layerInfo->getName()!=m_activeLayerName)
            {
                buildMapLayer(layerInfo,mapInfo);
                idx++;
            }
        }
    }
}

void ISOTileMapBuilder::buildMapLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    CCLOG("ISOTileMapBuilder::buildMapLayer:%s",layerInfo->getName());
    ISOTileLayer *layer = NULL;
    
    switch (m_uMapLayerType) {
        case NormalLayerType:
            layer=new ISOGroundTileLayer();
            layer->init();
            break;
        case DynamicLayerType:{
            ISODynamicTileLayer* dynamicLayer=new ISODynamicTileLayer();
            dynamicLayer->init();

			//设置是否使用统一动态组件
			if (m_pMap->isUseDynamicGroup())
			{
				m_pMap->addDynamicComponent(dynamicLayer->getDynamicComponent());
			}
			layer=dynamicLayer;
            //layer->setPosition(ccp(100,50));
            //layer->setOffset(ccp(100,50));
			break;
		}
        case BatchLayerType:
        {
            ISOBatchTileLayer* batchLayer=new ISOBatchTileLayer();
            batchLayer->init();
            
			//设置tileset
            ISOTileset* tileset=tilesetForLayer(layerInfo);
            if(tileset){
                batchLayer->setTileset(tileset);
            }

            layer=batchLayer;
            break;
        }
		case BatchDynamicLayerType:
        {
            ISOBatchDynamicTileLayer* batchLayer=new ISOBatchDynamicTileLayer();
            batchLayer->init();
            
			//设置tileset
            ISOTileset* tileset=tilesetForLayer(layerInfo);
            if(tileset){
                batchLayer->setTileset(tileset);
            }

			//设置是否使用统一动态组件
			if (m_pMap->isUseDynamicGroup())
			{
				m_pMap->addDynamicComponent(batchLayer->getDynamicComponent());
			}

            layer=batchLayer;
            break;
        }
        default:
            break;
    }
    
    if(layer){
        
        setLayerAttribute(layer, layerInfo, mapInfo);

        m_pMap->addChild(layer,layerInfo->getRenderIndex());
        m_pMap->getLayers()->addObject(layer);
        layer->release();
    }
    
    // update content size with the max size
    //                const CCSize& childSize = layer->getContentSize();
    //                CCSize currentSize = m_pMap->getContentSize();
    //                currentSize.width = MAX( currentSize.width, childSize.width );
    //                currentSize.height = MAX( currentSize.height, childSize.height );
    //                m_pMap->setContentSize(currentSize);
}

void ISOTileMapBuilder::setLayerAttribute(ISOTileLayer* tileLayer,ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    
    tileLayer->setMap(m_pMap);
    tileLayer->setMapTileSize(m_pMap->getTileSize());
    tileLayer->setLayerName(layerInfo->getName());
    tileLayer->setLayerSize(layerInfo->getLayerSize());
    tileLayer->setOffset(layerInfo->getOffset());
    tileLayer->setOpacity(layerInfo->getOpacity());
    tileLayer->setTiles(layerInfo->getTiles());
    tileLayer->setProperties(layerInfo->getProperties());
    layerInfo->setOwnTiles(false);
    tileLayer->setupLayer();
}

ISOTileset * ISOTileMapBuilder::tilesetForLayer(ISOLayerInfo *layerInfo)
{
    CCSize size = layerInfo->getLayerSize();
    CCArray* tilesets = m_pMap->getTilesetGroup()->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        ISOTileset* tileset = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
        {
            tileset = (ISOTileset*)pObj;
            if (tileset)
            {
                unsigned int* pTiles=layerInfo->getTiles();
                
                for( unsigned int y=0; y < size.height; y++ )
                {
                    for( unsigned int x=0; x < size.width; x++ )
                    {
                        unsigned int pos = (unsigned int)(x + size.width * y);
                        unsigned int gid = pTiles[ pos ];
                        
                        // gid are stored in little endian.
                        // if host is big endian, then swap
                        //if( o == CFByteOrderBigEndian )
                        //    gid = CFSwapInt32( gid );
                        /* We support little endian.*/
                        
                        // XXX: gid == 0 --> empty tile
                        if( gid != 0 )
                        {
                            // Optimization: quick return
                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
                            if( (gid & kCCFlippedMask) >= tileset->getFirstGid() )
                                return tileset;
                        }
                    }
                }
            }
        }
    }
    
    // If all the tiles are 0, return empty tileset
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->getName());
    return NULL;
}



ISOTilesetInfo * ISOTileMapBuilder::tilesetInfoForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    CCSize size = layerInfo->getLayerSize();
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        ISOTilesetInfo* tileset = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
        {
            tileset = (ISOTilesetInfo*)pObj;
            if (tileset)
            {
                unsigned int* pTiles=layerInfo->getTiles();
                
                for( unsigned int y=0; y < size.height; y++ )
                {
                    for( unsigned int x=0; x < size.width; x++ )
                    {
                        unsigned int pos = (unsigned int)(x + size.width * y);
                        unsigned int gid = pTiles[ pos ];
                        
                        // gid are stored in little endian.
                        // if host is big endian, then swap
                        //if( o == CFByteOrderBigEndian )
                        //    gid = CFSwapInt32( gid );
                        /* We support little endian.*/
                        
                        // XXX: gid == 0 --> empty tile
                        if( gid != 0 )
                        {
                            // Optimization: quick return
                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
                            if( (gid & kCCFlippedMask) >= tileset->getFirstGid() )
                                return tileset;
                        }
                    }
                }
            }
        }
    }
    
    // If all the tiles are 0, return empty tileset
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->getName());
    return NULL;
}



void ISOTileMapBuilder::buildMapObjectGroups(ISOMapInfo* mapInfo)
{
    
    CCArray* objectGroups = mapInfo->getObjectGroups();
    if (objectGroups && objectGroups->count()>0)
    {
        ISOObjectGroupInfo* objectGroupInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(objectGroups, pObj)
        {
            objectGroupInfo = (ISOObjectGroupInfo*)pObj;
            if (objectGroupInfo && objectGroupInfo->getVisible())
            {
                ISOObjectGroup* objGroup=new ISOObjectGroup();
                objGroup->init();
                objGroup->setName(objectGroupInfo->getName());
                objGroup->setOffset(objectGroupInfo->getPositionOffset());
                objGroup->setProperties(objectGroupInfo->getProperties());
                objGroup->setRenderIndex(objectGroupInfo->getRenderIndex());
                
                buildMapObjects(objectGroupInfo->getObjects(), objGroup);
                
                m_pMap->getObjectGroups()->addObject(objGroup);
                objGroup->release();

                if (objectGroupInfo->getName()!=m_activeLayerName) {
                    buildMapObjectLayer(objGroup);
                }
            }
        }
    }
}

void ISOTileMapBuilder::buildMapObjects(CCArray* objects,ISOObjectGroup* objectGroup)
{
    CCAssert(objects!=NULL, "buildMapObjects objects must non't be null");
    CCAssert(objectGroup!=NULL, "buildMapObjects objectGroup must non't be null");
    
    ISOObjectInfo* objectInfo = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        objectInfo = (ISOObjectInfo*)pObj;
        if (objectInfo && objectInfo->getVisible())
        {
            buildMapObject(objectInfo,objectGroup);
        }
    }
}

void ISOTileMapBuilder::buildMapObject(ISOObjectInfo* objectInfo,ISOObjectGroup* objectGroup)
{
    ISOMapObject* obj=new ISOMapObject();
    obj->init();
    obj->setName(objectInfo->getName());
    obj->setGid(objectInfo->getGid());
    obj->setPosition(objectInfo->getPosition());
    obj->setSize(objectInfo->getSize());
    obj->setType(objectInfo->getType());
    obj->setRotation(objectInfo->getRotation());
    obj->setVisible(objectInfo->getVisible());
    obj->setProperties(objectInfo->getProperties());
    objectGroup->getObjects()->addObject(obj);
    obj->release();
}

/**
 * 构建map object layer
 * 只显示图块的object group
 */
void ISOTileMapBuilder::buildMapObjectLayer(ISOObjectGroup* objectGroup)
{
	ISOObjectLayer* objectLayer=new ISOObjectLayer();
	objectLayer->init();

	objectLayer->setMap(m_pMap);
	objectLayer->setLayerName(objectGroup->getName());
	objectLayer->setLayerOrientation(m_pMap->getMapOrientation());
	objectLayer->setProperties(objectGroup->getProperties());
	objectLayer->setObjectGroup(objectGroup);
	objectLayer->setupLayer();
    
    //fix object layer position
    //x方向向左移动半个地图大小
//    objectLayer->setPosition(ccp(-m_pMap->getMapSize().width*m_pMap->getTileSize().width*0.5f,0));
    
	m_pMap->addChild(objectLayer);

	objectLayer->release();
}

/**
 * 设置地图中的活动层
 */
void ISOTileMapBuilder::setupMapActiveLayer(ISOMapInfo* mapInfo)
{
    //首先从object groups里检找是否叫m_activeLayerName设置的layer
    CCArray* objectGroups = mapInfo->getObjectGroups();
    if (objectGroups && objectGroups->count()>0)
    {
        ISOObjectGroupInfo* objectGroupInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(objectGroups, pObj)
        {
            objectGroupInfo = (ISOObjectGroupInfo*)pObj;
            if (objectGroupInfo && strcmp(objectGroupInfo->getName(), m_activeLayerName.c_str())==0)
            {
                buildMapActiveLayerWithObjectGroup(objectGroupInfo);
                return;
            }
        }
    }

    //从tile layer里查找
    CCArray* layerInfos = mapInfo->getLayers();
    if (layerInfos && layerInfos->count()>0)
    {
        ISOLayerInfo* layerInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(layerInfos, pObj)
        {
            layerInfo = (ISOLayerInfo*)pObj;
            if (layerInfo && strcmp(layerInfo->getName(), m_activeLayerName.c_str())==0)
            {
                buildMapActiveLayerWithLayerInfo(layerInfo);
                return;
            }
        }
    }
    
    //没有找到创建一个空的layer，默认放在最上层
    buildMapActiveLayer(m_activeLayerName, NULL, NULL, m_activeLayerDefaultZOrder);
}

/**
 * 构建map active layer
 * 对于格子地图，object的坐标最好是基于格子的。
 */
void ISOTileMapBuilder::buildMapActiveLayer(const std::string& name,CCArray* objects,CCDictionary* properties,int zOrder)
{
    ISOActiveLayer* activeLayer=new ISOActiveLayer();
	activeLayer->init();
    
	activeLayer->setMap(m_pMap);
	activeLayer->setLayerName(name);
	activeLayer->setLayerOrientation(m_pMap->getMapOrientation());
    if (properties) {
        activeLayer->setProperties(properties);
    }
	activeLayer->setObjects(objects);
	activeLayer->setupLayer();
    
	m_pMap->addChild(activeLayer,zOrder);
    
    m_pMap->setActiveLayer(activeLayer);
    
	activeLayer->release();
}

/**
 * 构建map active layer
 * 对于格子地图，object的坐标最好是基于格子的。
 */
void ISOTileMapBuilder::buildMapActiveLayerWithObjectGroup(ISOObjectGroupInfo* objectGroupInfo)
{
    buildMapActiveLayer(objectGroupInfo->getName(),objectGroupInfo->getObjects(),objectGroupInfo->getProperties(),objectGroupInfo->getRenderIndex());
}

/**
 * 构建map active layer
 * 对于格子地图，object的坐标最好是基于格子的。
 */
void ISOTileMapBuilder::buildMapActiveLayerWithLayerInfo(ISOLayerInfo* layerInfo)
{
    CCArray* objects=createObjectsFromLayerInfo(layerInfo);
    
    buildMapActiveLayer(layerInfo->getName(), objects, layerInfo->getProperties(), layerInfo->getRenderIndex());
}

/**
 * 把layer里的元素转成对象
 */
CCArray* ISOTileMapBuilder::createObjectsFromLayerInfo(ISOLayerInfo* layerInfo)
{
    CCSize layerSize=layerInfo->getLayerSize();
    
    CCArray* objects=CCArray::createWithCapacity((unsigned int)(layerSize.width*layerSize.height*0.25));
    
    unsigned int * tiles=layerInfo->getTiles();
    ISOMapObject* obj=NULL;
    
    for (unsigned int y=0; y < layerSize.height; y++)
    {
        for (unsigned int x=0; x < layerSize.width; x++)
        {
            unsigned int pos = (unsigned int)(x + layerSize.width * y);
            unsigned int gid = tiles[ pos ];
            if (gid) {
                obj=new ISOMapObject();
                obj->init();
                obj->setGid(gid);
                obj->setPosition(ccp(x,y));
                objects->addObject(obj);
                
                obj->release();
            }            
        }
    }
    
    return objects;
}

NS_CC_YHGE_END
