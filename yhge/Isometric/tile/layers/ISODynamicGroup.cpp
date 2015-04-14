#include "ISODynamicGroup.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../base/ISOTile.h"
#include "ISOTileLayer.h"
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

//const CCSize testSize=CCSizeMake(256,160);
static const int kComponentExtendCount=2;

ISODynamicGroup::ISODynamicGroup()
:_pDynamiceComponentList(NULL)
,_iStartX(0)
,_iStartY(0)
,_iLastStartX(-999999)
,_iLastStartY(-999999)
,_iComponentIndexX(0)
,_iComponentIndexY(0)
,_pUpdateDelegator(NULL)
,_pCreateDelegator(NULL)
,_iComponentNodeExtendCount(kComponentExtendCount)
,_iComponentTileColumn(0)
,_iComponentTileRow(0)
,_iComponentTileTotalColumn(0)
,_iComponentTileTotalRow(0)
,_tileMap(NULL)
,_tOffset(CCPointZero)
{
	
}

ISODynamicGroup::~ISODynamicGroup()
{
	CC_SAFE_RELEASE_NULL(_pDynamiceComponentList);
}

bool ISODynamicGroup::init()
{
	_pDynamiceComponentList=new CCArray();
	_pDynamiceComponentList->init();
	return true;
}

/*
 * 设置内容
 */
void ISODynamicGroup::setup()
{

}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool ISODynamicGroup::beforeUpdateContent()
{
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGame2F(0,0));
	//only for test
	CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(_tOffset));
	_iStartX=(int)startMapCoord.x;
	_iStartY=(int)startMapCoord.y;
    //CCLOG("start:%d,%d %f,%f",_iStartX,_iStartY,_tPosition.x,_tPosition.y);
	return _iStartX!=_iLastStartX || _iStartY!=_iLastStartY;
}

void ISODynamicGroup::doUpdateComponents()
{
    //用到的组件的总列数和总行数
    int totalRow=2*_iComponentTileRow;
    int totalColumn=2*_iComponentTileColumn;
    
	//移动的行列数
    int dx=_iStartX-_iLastStartX;
    int dy=_iStartY-_iLastStartY;
    
	//移动方向
    int dirX=dx>0?1:dx<0?-1:0;
    int dirY=dy>0?1:dy<0?-1:0;
    
	//移动多少行列
    int loopX=abs(dx);
    int loopY=abs(dy);
    
//	CCLOG("updateCompoents:%d,%d loops:%d,%d",dx,dy,loopX,loopY);
	//移动组件的索引
    int moveComponentIndexX=0,moveComponentIndexY=0;

    int index,row,col;
    
//    float mx=0,my=0;
//    ISOComponentNode* node=NULL;
    
    //注意正向，反向node移动的序列位置
    if(dx!=0){
        for(int k=0;k<loopX;k++){
            //横向移动 移动列。把左边的列移动到右边或把右边移动到左边
            if(dirX>0){
                moveComponentIndexX=_iComponentIndexX;
                _iComponentIndexX=(_iComponentIndexX+dirX)%totalColumn;
            }else if(dirX<0){
                _iComponentIndexX=(_iComponentIndexX+dirX+totalColumn)%totalColumn;
                moveComponentIndexX=_iComponentIndexX;
            }
            
            for(int j=0;j<_iComponentTileRow;j++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                row=(j*2+_iComponentIndexY+((_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*_iComponentTileColumn+moveComponentIndexX/2;
                //CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
				//更新组件坐标
                this->updateMapCoordinate(index, dirX*_iComponentTileColumn, -dirX*_iComponentTileColumn);
            }
                    
            //纵向移动 移动行。上面移动到下边或下边移动到上边。
            if(dirX>0){
                moveComponentIndexY=_iComponentIndexY;
                _iComponentIndexY=(_iComponentIndexY+dirX)%totalRow;
                
            }else if(dirX<0){
                _iComponentIndexY=(_iComponentIndexY+dirX+totalRow)%totalRow;
                moveComponentIndexY=_iComponentIndexY;
            }
            
            for(int i=0;i<_iComponentTileColumn;i++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                col=(i*2+_iComponentIndexX+((_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index, dirX*_iComponentTileRow, dirX*_iComponentTileRow);
            }
        }
    }
    
	if(dy!=0){
        for(int k=0;k<loopY;k++){
            //横向移动
            if(dirY>0){
                _iComponentIndexX=(_iComponentIndexX-1+totalColumn)%totalColumn;
                moveComponentIndexX=_iComponentIndexX;
            }else if(dirY<0){
                moveComponentIndexX=_iComponentIndexX;
                _iComponentIndexX=(_iComponentIndexX+1)%totalColumn;
            }

            
            for(int j=0;j<_iComponentTileRow;j++){
                row=(j*2+_iComponentIndexY+((_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*_iComponentTileColumn+moveComponentIndexX/2;
//                CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, -dirY*_iComponentTileColumn, dirY*_iComponentTileColumn);
            }
            
            //纵向移动
            if(dirY>0){
                moveComponentIndexY=_iComponentIndexY;
                _iComponentIndexY=(_iComponentIndexY+1)%totalRow;
            }else if(dirY<0){
                _iComponentIndexY=(_iComponentIndexY-1+totalRow)%totalRow;
                moveComponentIndexY=_iComponentIndexY;
            }
            
            for(int i=0;i<_iComponentTileColumn;i++){
                col=(i*2+_iComponentIndexX+((_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index,dirY*_iComponentTileRow, dirY*_iComponentTileRow);
//                node=(ISOComponentNode*) _pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirY*_iComponentTileRow, my+dirY*_iComponentTileRow);
            }
        }
    }
}

void ISODynamicGroup::updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
    if(_pUpdateDelegator) _pUpdateDelegator->onUpdateComponentMapCoordinate(nodeIndex, deltaMapX, deltaMapY);
    
	//更新组内的元素
	Ref* pObj=NULL;
	ISODynamicComponent* dynamicComponent=NULL;
	CCARRAY_FOREACH(_pDynamiceComponentList,pObj){
		dynamicComponent=static_cast<ISODynamicComponent*>(pObj);
		dynamicComponent->updateNodeBy(nodeIndex,deltaMapX,deltaMapY);
	}
   
//    CCLOG("ISODynamicGroup::updateMapCoordinate from:%f,%f to:%f,%f",mx,my,newMx,newMy);

}

void ISODynamicGroup::calcComponentsCount()
{    
    _iComponentTileColumn+=_iComponentNodeExtendCount;
    _iComponentTileRow+=_iComponentNodeExtendCount;
    _iComponentTileTotalColumn=2*_iComponentTileColumn;
    _iComponentTileTotalRow=2*_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",_iComponentTileColumn,_iComponentTileRow);
}

void ISODynamicGroup::initOffset(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(tOffset));
	_iStartX=(int)startMapCoord.x;
	_iStartY=(int)startMapCoord.y;
	_iLastStartX=_iStartX;
	_iLastStartY=_iStartY;
}

void ISODynamicGroup::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

void ISODynamicGroup::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	if(this->beforeUpdateContent()){
		//TODO 不删除所有tile,只修改改变的tile.
		//this->removeAllChildrenWithCleanup(true);
		//this->doUpdateContent();
		this->doUpdateComponents();
        _iLastStartX=_iStartX;
		_iLastStartY=_iStartY;

	}
}

void ISODynamicGroup::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}

void ISODynamicGroup::setUpdateDelegator(ISODynamicComponentUpdateDelegator* pUpdateDelegator)
{
    _pUpdateDelegator=pUpdateDelegator;
}

void ISODynamicGroup::setCreateDelegator(ISODynamicComponentCreateDelegator* pCreateDelegator)
{
    _pCreateDelegator=pCreateDelegator;
}

void ISODynamicGroup::addDynamicComponent(ISODynamicComponent* dynamicComponent)
{
	_pDynamiceComponentList->addObject(dynamicComponent);
}

void ISODynamicGroup::removeDynamicComponent(ISODynamicComponent* dynamicComponent)
{
	_pDynamiceComponentList->removeObject(dynamicComponent);
}

NS_CC_YHGE_ISOMETRIC_END
