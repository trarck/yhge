#include "ISOBatchDynamicTileLayer.h"
#include "ISOBatchDynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN



ISOBatchDynamicTileLayer::ISOBatchDynamicTileLayer()
:_pTileset(NULL)
{

}

ISOBatchDynamicTileLayer::~ISOBatchDynamicTileLayer()
{
	CC_SAFE_RELEASE(_pTileset);
}

bool ISOBatchDynamicTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        _pDynamicComponent=new ISOBatchDynamicComponent();
        _pDynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool ISOBatchDynamicTileLayer::init(Size& mapTileSize,Vec2& offset)
{
    if(ISOTileLayer::init(mapTileSize, offset)){
        init();       
        return true;
    }
    return false;
}

NS_CC_YHGE_ISOMETRIC_END
