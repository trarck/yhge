#include "ISODynamicTileLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../ISOTileMap.h"

NS_CC_YHGE_BEGIN



ISODynamicTileLayer::ISODynamicTileLayer()
:m_pDynamicComponent(NULL)
,m_iLastStartX(0)
,m_iLastStartY(0)
{

}

ISODynamicTileLayer::~ISODynamicTileLayer()
{
	CC_SAFE_RELEASE(m_pDynamicComponent);
}

bool ISODynamicTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        m_pDynamicComponent=new ISODynamicComponent();
        m_pDynamicComponent->init();
        m_pDynamicComponent->setCreateDelegator(this);
        m_pDynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool ISODynamicTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(ISOTileLayer::init(mapTileSize, offset)){
        init();
        //setComponentColumnAndRow();
        //m_pDynamicComponent->setupComponents(offset);
        
        return true;
    }
    return false;
}

void ISODynamicTileLayer::setupTiles()
{
    setComponentColumnAndRow();
    m_pDynamicComponent->setupComponents(m_tOffset);
}

void ISODynamicTileLayer::setComponentColumnAndRow()
{

    if(m_pDynamicComponent && m_tMapTileSize.height!=0 && m_tMapTileSize.width!=0){
        
        CCSize visibleSize=m_pMap->getVisibleSize();
        
        int componentTileColumn=floor(visibleSize.width/m_tMapTileSize.width)+2;
        int componentTileRow=floor(visibleSize.height/m_tMapTileSize.height)+2;
        
        m_pDynamicComponent->setComponentTileColumn(componentTileColumn);
        m_pDynamicComponent->setComponentTileRow(componentTileRow);
    }

}

void ISODynamicTileLayer::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    
    CCSize visibleSize=m_pMap->getVisibleSize();
    
    ccDrawRect(m_tOffset,ccp(m_tOffset.x+visibleSize.width,m_tOffset.y+visibleSize.height));
}


void ISODynamicTileLayer::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	m_pDynamicComponent->scroll(tOffset);
}

void ISODynamicTileLayer::setDynamicComponent(ISODynamicComponent* pDynamicComponent)
{
    CC_SAFE_RETAIN(pDynamicComponent);
    CC_SAFE_RELEASE(m_pDynamicComponent);
    m_pDynamicComponent = pDynamicComponent;
}

ISODynamicComponent* ISODynamicTileLayer::getDynamicComponent()
{
    return m_pDynamicComponent;
}

CCSprite* ISODynamicTileLayer::createTile()
{
    CCSprite* cellTile=CCSprite::create("grid_ground.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    //    cellTile->setOpacity(60);
    this->addChild(cellTile);
    return cellTile;
}
NS_CC_YHGE_END
