#include "ISODynamicTileLayer.h"
#include "../ISOTileMap.h"
#include "../IsoTileUtils.h"

NS_CC_YHGE_ISOMETRIC_BEGIN



ISODynamicTileLayer::ISODynamicTileLayer()
:_dynamicComponent(NULL)
,_iLastStartX(0)
,_iLastStartY(0)
{

}

ISODynamicTileLayer::~ISODynamicTileLayer()
{
	CC_SAFE_RELEASE(_dynamicComponent);
}

bool ISODynamicTileLayer::init()
{
    if(ISOTileLayer::init()){
        
        _dynamicComponent=new ISODynamicComponent();
        _dynamicComponent->init();
        _dynamicComponent->setCreateDelegator(this);
        _dynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool ISODynamicTileLayer::init(Size& mapTileSize,Vec2& offset)
{
    if(ISOTileLayer::init(mapTileSize, offset)){
        init();
        //setComponentColumnAndRow();
        //_dynamicComponent->setupComponents(offset);
        
        return true;
    }
    return false;
}

void ISODynamicTileLayer::setupTiles()
{
    setComponentColumnAndRow();
    _dynamicComponent->setupComponents(_offset);
}

void ISODynamicTileLayer::setComponentColumnAndRow()
{

    if(_dynamicComponent && _mapTileSize.height!=0 && _mapTileSize.width!=0){
        
        Size visibleSize=_tileMap->getVisibleSize();
        int componentTileColumn=0;
        int componentTileRow=0;

        ISOTileUtils::calcDynamicComponetSize(visibleSize,_mapTileSize,&componentTileColumn,&componentTileRow);
        ////参考Isometric.Game.Programming.with.DirectX.7的第421页。
        ////如果要显示全visibleSize的大小内的元素，则在除以块大小后，四个角要向外移动一格。所以最后大小要加2.
        //int componentTileColumn=floor(visibleSize.width/_mapTileSize.width)+2;
        //int componentTileRow=floor(visibleSize.height/_mapTileSize.height)+2;
        
        _dynamicComponent->setComponentTileColumn(componentTileColumn);
        _dynamicComponent->setComponentTileRow(componentTileRow);
    }

}

void ISODynamicTileLayer::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    
    Size visibleSize=_tileMap->getVisibleSize();
    
    ccDrawRect(_offset,ccp(_offset.x+visibleSize.width,_offset.y+visibleSize.height));
}


void ISODynamicTileLayer::scroll(const Vec2& offset)
{
    this->setOffset(offset);
	_dynamicComponent->scroll(offset);
}

void ISODynamicTileLayer::setDynamicComponent(ISODynamicComponent* dynamicComponent)
{
    CC_SAFE_RETAIN(dynamicComponent);
    CC_SAFE_RELEASE(_dynamicComponent);
    _dynamicComponent = dynamicComponent;
}

ISODynamicComponent* ISODynamicTileLayer::getDynamicComponent()
{
    return _dynamicComponent;
}

CCSprite* ISODynamicTileLayer::createTile()
{
    CCSprite* cellTile=CCSprite::create("grid_ground.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    //    cellTile->setOpacity(60);
    this->addChild(cellTile);
    return cellTile;
}
NS_CC_YHGE_ISOMETRIC_END
