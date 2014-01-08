#include "ISOTileMapBuilder.h"
#include "../ISOBases.h"
#include "../ISOLayers.h"
#include "../ISOTileMap.h"

NS_CC_YHGE_BEGIN

ISOTileMapBuilder::ISOTileMapBuilder()
:m_pMap(NULL)
,m_uMapLayerType(NormalLayerType)
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
                buildMapObjects(objectGroupInfo->getObjects(), objGroup);
                
                m_pMap->getObjectGroups()->addObject(objGroup);
                objGroup->release();
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
    ISOTileMapObject* obj=new ISOTileMapObject();
    obj->init();
    obj->setName(objectInfo->getName());
    obj->setGid(objectInfo->getGid());
    obj->setPosition(objectInfo->getPosition());
    obj->setSize(objectInfo->getSize());
    obj->setType(objectInfo->getType());
    obj->setVisible(objectInfo->getVisible());
    obj->setProperties(objectInfo->getProperties());
    objectGroup->getObjects()->addObject(obj);
    obj->release();
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
            if (layerInfo && layerInfo->getVisible())
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
        case DynamicLayerType:
            layer=new ISODynamicTileLayer();
            layer->init();
            break;
        case BatchLayerType:
        {
            ISOBatchTileLayer* batchLayer=new ISOBatchTileLayer();
            batchLayer->init();

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

            ISOTileset* tileset=tilesetForLayer(layerInfo);
            
            if(tileset){
                batchLayer->setTileset(tileset);
            }
            layer=batchLayer;
            break;
        }
        default:
            break;
    }
    
    if(layer){
        
        setLayerAttribute(layer, layerInfo, mapInfo);
        
        
        
        m_pMap->addChild(layer);
        m_pMap->getTileLayers()->addObject(layer);
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

    tileLayer->setupTiles();
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




NS_CC_YHGE_END
