#include "ISODynamicGroup.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../base/ISOTile.h"
#include "ISOTileLayer.h"
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

//const CCSize testSize=CCSizeMake(256,160);
static const int kComponentExtendCount=2;

ISODynamicGroup::ISODynamicGroup()
:m_pDynamiceComponentList(NULL)
,m_iStartX(0)
,m_iStartY(0)
,m_iLastStartX(-999999)
,m_iLastStartY(-999999)
,m_iComponentIndexX(0)
,m_iComponentIndexY(0)
,m_pUpdateDelegator(NULL)
,m_pCreateDelegator(NULL)
,m_iComponentNodeExtendCount(kComponentExtendCount)
,m_iComponentTileColumn(0)
,m_iComponentTileRow(0)
,m_iComponentTileTotalColumn(0)
,m_iComponentTileTotalRow(0)
,m_tileMap(NULL)
,m_tOffset(CCPointZero)
{
	
}

ISODynamicGroup::~ISODynamicGroup()
{
	CC_SAFE_RELEASE_NULL(m_pDynamiceComponentList);
}

bool ISODynamicGroup::init()
{
	m_pDynamiceComponentList=new CCArray();
	m_pDynamiceComponentList->init();
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
	CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(m_tOffset));
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
    //CCLOG("start:%d,%d %f,%f",m_iStartX,m_iStartY,m_tPosition.x,m_tPosition.y);
	return m_iStartX!=m_iLastStartX || m_iStartY!=m_iLastStartY;
}

void ISODynamicGroup::doUpdateComponents()
{
    //用到的组件的总列数和总行数
    int totalRow=2*m_iComponentTileRow;
    int totalColumn=2*m_iComponentTileColumn;
    
	//移动的行列数
    int dx=m_iStartX-m_iLastStartX;
    int dy=m_iStartY-m_iLastStartY;
    
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
                moveComponentIndexX=m_iComponentIndexX;
                m_iComponentIndexX=(m_iComponentIndexX+dirX)%totalColumn;
            }else if(dirX<0){
                m_iComponentIndexX=(m_iComponentIndexX+dirX+totalColumn)%totalColumn;
                moveComponentIndexX=m_iComponentIndexX;
            }
            
            for(int j=0;j<m_iComponentTileRow;j++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                row=(j*2+m_iComponentIndexY+((m_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*m_iComponentTileColumn+moveComponentIndexX/2;
                //CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
				//更新组件坐标
                this->updateMapCoordinate(index, dirX*m_iComponentTileColumn, -dirX*m_iComponentTileColumn);
            }
                    
            //纵向移动 移动行。上面移动到下边或下边移动到上边。
            if(dirX>0){
                moveComponentIndexY=m_iComponentIndexY;
                m_iComponentIndexY=(m_iComponentIndexY+dirX)%totalRow;
                
            }else if(dirX<0){
                m_iComponentIndexY=(m_iComponentIndexY+dirX+totalRow)%totalRow;
                moveComponentIndexY=m_iComponentIndexY;
            }
            
            for(int i=0;i<m_iComponentTileColumn;i++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                col=(i*2+m_iComponentIndexX+((m_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*m_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index, dirX*m_iComponentTileRow, dirX*m_iComponentTileRow);
            }
        }
    }
    
	if(dy!=0){
        for(int k=0;k<loopY;k++){
            //横向移动
            if(dirY>0){
                m_iComponentIndexX=(m_iComponentIndexX-1+totalColumn)%totalColumn;
                moveComponentIndexX=m_iComponentIndexX;
            }else if(dirY<0){
                moveComponentIndexX=m_iComponentIndexX;
                m_iComponentIndexX=(m_iComponentIndexX+1)%totalColumn;
            }

            
            for(int j=0;j<m_iComponentTileRow;j++){
                row=(j*2+m_iComponentIndexY+((m_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*m_iComponentTileColumn+moveComponentIndexX/2;
//                CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, -dirY*m_iComponentTileColumn, dirY*m_iComponentTileColumn);
            }
            
            //纵向移动
            if(dirY>0){
                moveComponentIndexY=m_iComponentIndexY;
                m_iComponentIndexY=(m_iComponentIndexY+1)%totalRow;
            }else if(dirY<0){
                m_iComponentIndexY=(m_iComponentIndexY-1+totalRow)%totalRow;
                moveComponentIndexY=m_iComponentIndexY;
            }
            
            for(int i=0;i<m_iComponentTileColumn;i++){
                col=(i*2+m_iComponentIndexX+((m_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*m_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index,dirY*m_iComponentTileRow, dirY*m_iComponentTileRow);
//                node=(ISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirY*m_iComponentTileRow, my+dirY*m_iComponentTileRow);
            }
        }
    }
}

void ISODynamicGroup::updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
    if(m_pUpdateDelegator) m_pUpdateDelegator->onUpdateComponentMapCoordinate(nodeIndex, deltaMapX, deltaMapY);
    
	//更新组内的元素
	Ref* pObj=NULL;
	ISODynamicComponent* dynamicComponent=NULL;
	CCARRAY_FOREACH(m_pDynamiceComponentList,pObj){
		dynamicComponent=static_cast<ISODynamicComponent*>(pObj);
		dynamicComponent->updateNodeBy(nodeIndex,deltaMapX,deltaMapY);
	}
   
//    CCLOG("ISODynamicGroup::updateMapCoordinate from:%f,%f to:%f,%f",mx,my,newMx,newMy);

}

void ISODynamicGroup::calcComponentsCount()
{    
    m_iComponentTileColumn+=m_iComponentNodeExtendCount;
    m_iComponentTileRow+=m_iComponentNodeExtendCount;
    m_iComponentTileTotalColumn=2*m_iComponentTileColumn;
    m_iComponentTileTotalRow=2*m_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",m_iComponentTileColumn,m_iComponentTileRow);
}

void ISODynamicGroup::initOffset(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(tOffset));
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
	m_iLastStartX=m_iStartX;
	m_iLastStartY=m_iStartY;
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
        m_iLastStartX=m_iStartX;
		m_iLastStartY=m_iStartY;

	}
}

void ISODynamicGroup::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}

void ISODynamicGroup::setUpdateDelegator(ISODynamicComponentUpdateDelegator* pUpdateDelegator)
{
    m_pUpdateDelegator=pUpdateDelegator;
}

void ISODynamicGroup::setCreateDelegator(ISODynamicComponentCreateDelegator* pCreateDelegator)
{
    m_pCreateDelegator=pCreateDelegator;
}

void ISODynamicGroup::addDynamicComponent(ISODynamicComponent* dynamicComponent)
{
	m_pDynamiceComponentList->addObject(dynamicComponent);
}

void ISODynamicGroup::removeDynamicComponent(ISODynamicComponent* dynamicComponent)
{
	m_pDynamiceComponentList->removeObject(dynamicComponent);
}

NS_CC_YHGE_ISOMETRIC_END
