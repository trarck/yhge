#include "ISOBatchDynamicTileLayer.h"
#include "ISOBatchDynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN



ISOBatchDynamicTileLayer::ISOBatchDynamicTileLayer()
:m_pTileset(NULL)
{

}

ISOBatchDynamicTileLayer::~ISOBatchDynamicTileLayer()
{
	CC_SAFE_RELEASE(m_pTileset);
}

bool ISOBatchDynamicTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        m_pDynamicComponent=new ISOBatchDynamicComponent();
        m_pDynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool ISOBatchDynamicTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(ISOTileLayer::init(mapTileSize, offset)){
        init();       
        return true;
    }
    return false;
}

NS_CC_YHGE_ISOMETRIC_END
