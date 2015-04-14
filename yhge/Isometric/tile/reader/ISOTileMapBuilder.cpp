#include "ISOTileMapBuilder.h"
#include "../ISOBases.h"
#include "../ISOLayers.h"
#include "../ISOTileMap.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileMapBuilder::ISOTileMapBuilder()
:_pMap(NULL)
,_uMapLayerType(NormalLayerType)
,_activeLayerName("ActiveLayer")
,_activeLayerDefaultZOrder(99999)
,_buildActiveLayer(false)
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
    _pMap=pMap;
    return true;
}

void ISOTileMapBuilder::buildWithMapInfo(ISOMapInfo* mapInfo)
{
    CCAssert(_pMap!=NULL, "buildWithMapInfo _pMap can't be null");
    _pMap->setMapSize(mapInfo->getMapSize());
    _pMap->setTileSize(mapInfo->getTileSize());
    _pMap->setProperties(mapInfo->getProperties());
    
    this->buildMapTilesets(mapInfo);
    this->buildMapLayers(mapInfo);
    this->buildMapObjectGroups(mapInfo);
    
    if (_buildActiveLayer) {
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
        Ref* pObj = NULL;
        CCARRAY_FOREACH(tilesets, pObj)
        {
            tilesetInfo = (ISOTilesetInfo*)pObj;
            if (tilesetInfo)
            {
                buildMapTileset(tilesetInfo, tilesetGroup);
            }
        }
        
        _pMap->setTilesetGroup(tilesetGroup);
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
    Ref* pObj;

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
    Ref* pObj;
    
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
        Ref* pObj = NULL;
        CCARRAY_FOREACH(layerInfos, pObj)
        {
            layerInfo = (ISOLayerInfo*)pObj;
            if (layerInfo && layerInfo->getVisible() && layerInfo->getName()!=_activeLayerName)
            {
                buildMapLayer(layerInfo,mapInfo);
                idx++;
            }
        }
    }
}

void ISOTileMapBuilder::buildMapLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    CCLOG("ISOTileMapBuilder::buildMapLayer:%s",layerInfo->getName().c_str());
    ISOTileLayer *layer = NULL;
    
    switch (_uMapLayerType) {
        case NormalLayerType:
            layer=new ISOGroundTileLayer();
            layer->init();
            break;
        case DynamicLayerType:{
            ISODynamicTileLayer* dynamicLayer=new ISODynamicTileLayer();
            dynamicLayer->init();

			//设置是否使用统一动态组件
			if (_pMap->isUseDynamicGroup())
			{
				_pMap->addDynamicComponent(dynamicLayer->getDynamicComponent());
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
			if (_pMap->isUseDynamicGroup())
			{
				_pMap->addDynamicComponent(batchLayer->getDynamicComponent());
			}

            layer=batchLayer;
            break;
        }
        default:
            break;
    }
    
    if(layer){
        
        setLayerAttribute(layer, layerInfo, mapInfo);

        _pMap->addChild(layer,layerInfo->getRenderIndex());
        _pMap->getLayers()->addObject(layer);
        layer->release();
    }
    
    // update content size with the max size
    //                const CCSize& childSize = layer->getContentSize();
    //                CCSize currentSize = _pMap->getContentSize();
    //                currentSize.width = MAX( currentSize.width, childSize.width );
    //                currentSize.height = MAX( currentSize.height, childSize.height );
    //                _pMap->setContentSize(currentSize);
}

void ISOTileMapBuilder::setLayerAttribute(ISOTileLayer* tileLayer,ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    
    tileLayer->setMap(_pMap);
    tileLayer->setMapTileSize(_pMap->getTileSize());
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
    CCArray* tilesets = _pMap->getTilesetGroup()->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        ISOTileset* tileset = NULL;
        Ref* pObj = NULL;
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
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->getName().c_str());
    return NULL;
}



ISOTilesetInfo * ISOTileMapBuilder::tilesetInfoForLayer(ISOLayerInfo *layerInfo, ISOMapInfo *mapInfo)
{
    CCSize size = layerInfo->getLayerSize();
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        ISOTilesetInfo* tileset = NULL;
        Ref* pObj = NULL;
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
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->getName().c_str());
    return NULL;
}



void ISOTileMapBuilder::buildMapObjectGroups(ISOMapInfo* mapInfo)
{
    
    CCArray* objectGroups = mapInfo->getObjectGroups();
    if (objectGroups && objectGroups->count()>0)
    {
        ISOObjectGroupInfo* objectGroupInfo = NULL;
        Ref* pObj = NULL;
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
                
                _pMap->getObjectGroups()->addObject(objGroup);
                objGroup->release();

                if (objectGroupInfo->getName()!=_activeLayerName) {
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
    Ref* pObj = NULL;
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

	objectLayer->setMap(_pMap);
	objectLayer->setLayerName(objectGroup->getName());
	objectLayer->setLayerOrientation(_pMap->getMapOrientation());
	objectLayer->setProperties(objectGroup->getProperties());
	objectLayer->setObjectGroup(objectGroup);
	objectLayer->setupLayer();
    
    //fix object layer position
    //x方向向左移动半个地图大小
//    objectLayer->setPosition(ccp(-_pMap->getMapSize().width*_pMap->getTileSize().width*0.5f,0));
    
	_pMap->addChild(objectLayer);

	objectLayer->release();
}

/**
 * 设置地图中的活动层
 */
void ISOTileMapBuilder::setupMapActiveLayer(ISOMapInfo* mapInfo)
{
    ISOActiveLayerInfo* activeLayerInfo=this->getActiveLayerInfo(mapInfo);
    buildMapActiveLayerWithActiveLayerInfo(activeLayerInfo);
}

/**
 * 构建map active layer
 * 对于格子地图，object的坐标最好是基于格子的。
 */
void ISOTileMapBuilder::buildMapActiveLayer(const std::string& name,CCArray* objects,CCDictionary* properties,int zOrder)
{
    ISOActiveLayer* activeLayer=new ISOActiveLayer();
	activeLayer->init();
    
	activeLayer->setMap(_pMap);
	activeLayer->setLayerName(name);
	activeLayer->setLayerOrientation(_pMap->getMapOrientation());
    if (properties) {
        activeLayer->setProperties(properties);
    }
	activeLayer->setObjects(objects);
	activeLayer->setupLayer();
    
	_pMap->addChild(activeLayer,zOrder);
    
    _pMap->setActiveLayer(activeLayer);
    
	activeLayer->release();
}


/**
 * 构建map active layer
 * 对于格子地图，object的坐标最好是基于格子的。
 */
void ISOTileMapBuilder::buildMapActiveLayerWithActiveLayerInfo(ISOActiveLayerInfo* activeLayerInfo)
{
    buildMapActiveLayer(activeLayerInfo->getName(), activeLayerInfo->getObjects(), activeLayerInfo->getProperties(), activeLayerInfo->getRenderIndex());
}

/**
 * 把layer里的元素转成对象
 */
CCArray* ISOTileMapBuilder::createObjectsFromLayerInfo(ISOLayerInfo* layerInfo)
{
    CCSize layerSize=layerInfo->getLayerSize();
    
    CCArray* objects=CCArray::createWithCapacity((unsigned int)(layerSize.width*layerSize.height*0.25));
    
    unsigned int * tiles=layerInfo->getTiles();
    ISOObjectInfo* obj=NULL;
    
    for (unsigned int y=0; y < layerSize.height; y++)
    {
        for (unsigned int x=0; x < layerSize.width; x++)
        {
            unsigned int pos = (unsigned int)(x + layerSize.width * y);
            unsigned int gid = tiles[ pos ];
            if (gid) {
                obj=new ISOObjectInfo();
//                obj->init();
                obj->setGid(gid);
                obj->setPosition(ccp(x,y));
                objects->addObject(obj);
                
                obj->release();
            }            
        }
    }
    
    return objects;
}

/**
 * 取得活动层的信息
 */
ISOActiveLayerInfo* ISOTileMapBuilder::getActiveLayerInfo(ISOMapInfo* mapInfo)
{
    ISOActiveLayerInfo* activeLayerInfo=new ISOActiveLayerInfo();
    
    bool haveActiveLayer=false;
    
    //首先从object groups里检找是否叫_activeLayerName设置的layer
    CCArray* objectGroups = mapInfo->getObjectGroups();
    if (objectGroups && objectGroups->count()>0)
    {
        ISOObjectGroupInfo* objectGroupInfo = NULL;
        Ref* pObj = NULL;
        CCARRAY_FOREACH(objectGroups, pObj)
        {
            objectGroupInfo = (ISOObjectGroupInfo*)pObj;
            if (objectGroupInfo && strcmp(objectGroupInfo->getName(), _activeLayerName.c_str())==0)
            {
                activeLayerInfo->setName(objectGroupInfo->getName());
                activeLayerInfo->setObjects(objectGroupInfo->getObjects());
                activeLayerInfo->setProperties(objectGroupInfo->getProperties());
                activeLayerInfo->setRenderIndex(objectGroupInfo->getRenderIndex());
                
                haveActiveLayer=true;
                break;
            }
        }
    }
    
    //从tile layer里查找
    CCArray* layerInfos = mapInfo->getLayers();
    if (layerInfos && layerInfos->count()>0)
    {
        ISOLayerInfo* layerInfo = NULL;
        Ref* pObj = NULL;
        CCARRAY_FOREACH(layerInfos, pObj)
        {
            layerInfo = (ISOLayerInfo*)pObj;
            if (layerInfo && layerInfo->getName()==_activeLayerName)
            {
                activeLayerInfo->setName(layerInfo->getName());
                activeLayerInfo->setProperties(layerInfo->getProperties());
                activeLayerInfo->setRenderIndex(layerInfo->getRenderIndex());
                
                CCArray* objects=createObjectsFromLayerInfo(layerInfo);
                activeLayerInfo->setObjects(objects);
                
                haveActiveLayer=true;
                break;

            }
        }
    }
    
    if (!haveActiveLayer) {
        //没有找到创建一个空的layer，默认放在最上层
        activeLayerInfo->setName(_activeLayerName.c_str());
        activeLayerInfo->setObjects(NULL);
        activeLayerInfo->setRenderIndex(_activeLayerDefaultZOrder);
    }

    activeLayerInfo->autorelease();
    
    return activeLayerInfo;
}

NS_CC_YHGE_ISOMETRIC_END
