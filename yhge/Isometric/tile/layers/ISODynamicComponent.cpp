#include "ISODynamicComponent.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../base/ISOTile.h"
#include "ISOTileLayer.h"



NS_CC_YHGE_BEGIN

static const int kComponentExtendCount=2;

//const CCSize testSize=CCSizeMake(256,160);

ISODynamicComponent::ISODynamicComponent()
:m_pComponents(NULL)
,m_iStartX(0)
,m_iStartY(0)
,m_iLastStartX(-999999)
,m_iLastStartY(-999999)
,m_iComponentIndexX(0)
,m_iComponentIndexY(0)
,m_iComponentNodeExtendCount(kComponentExtendCount)
,m_pUpdateDelegator(NULL)
,m_pCreateDelegator(NULL)
{
	
}

ISODynamicComponent::~ISODynamicComponent()
{
	CC_SAFE_RELEASE_NULL(m_pComponents);
}

bool ISODynamicComponent::init()
{
	return true;
}

void ISODynamicComponent::createComponents()
{
	int totalColumn=2*m_iComponentTileColumn;
	int totalRow=2*m_iComponentTileRow;
	m_pComponents=new CCArray(totalColumn*totalRow);

    CCLOG("totoal:%d,%d",totalColumn,totalRow);
	ISOComponentNode* node=NULL;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
			node=new ISOComponentNode();
            node->init();
			node->setColumn(i*2+(j&1));
			node->setRow(j);
			node->setAnchorPoint(ccp(0.5f,0.0f));
			m_pComponents->addObject(node);
			//ttt.push_back(node);
            m_pTileLayer->addChild(node);
			node->release();
		}
		//if(j&1){
		//	//奇
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		node=new ISOComponentNode();
		//		node->setColumn(i*2+1);
		//		node->setRow(j);
		//		m_pComponents->addObject(node);
		//		node->release();
		//	}
		//}else{
		//	//偶
		//	for(int i=0;i<m_iComponentTileColumn;i++){
		//		node=new ISOComponentNode();
		//		node->setColumn(i*2);
		//		node->setRow(j);
		//		m_pComponents->addObject(node);
		//		node->release();
		//	}
		//}
    }
}

void ISODynamicComponent::initComponents()
{
    int totalRow=2*m_iComponentTileRow;
    
    
    int startX=m_iStartX-m_iComponentNodeExtendCount-1;
    int startY=m_iStartY;
    CCLOG("initComponents start:%d,%d",startX,startY);
	ISOComponentNode* node;
    int row=0,col=0,index=0;
    int mx=0,my=0;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
            col=(i*2+(j&1));
            row=j;
            index=j*m_iComponentTileColumn+col/2;
            
			node=(ISOComponentNode*)m_pComponents->objectAtIndex(j*m_iComponentTileColumn+col/2);
            mx=startX+i;
            my=startY-i;
            updateNode(node, mx, my);
//            CCLOG("index:%d,%d,%d:%d,%d",index,i,j,mx,my);
		}
        if(j&1){
			//下个循环为偶
			startY++;
		}else{
			//下个循环为奇
            startX++;
		}
    }
}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool ISODynamicComponent::beforeUpdateContent()
{
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
    //CCLOG("start:%d,%d %f,%f",m_iStartX,m_iStartY,m_tPosition.x,m_tPosition.y);
	return m_iStartX!=m_iLastStartX || m_iStartY!=m_iLastStartY;
}

void ISODynamicComponent::doUpdateComponents()
{
    
    int totalRow=2*m_iComponentTileRow;
    int totalColumn=2*m_iComponentTileColumn;
    
    int dx=m_iStartX-m_iLastStartX;
    int dy=m_iStartY-m_iLastStartY;
    
    int dirX=dx>0?1:dx<0?-1:0;
    int dirY=dy>0?1:dy<0?-1:0;
    
    int loopX=abs(dx);
    int loopY=abs(dy);
    
//	CCLOG("updateCompoents:%d,%d loops:%d,%d",dx,dy,loopX,loopY);
    int moveComponentIndexX=0,moveComponentIndexY=0;
    int index,row,col;
    
//    float mx=0,my=0;
//    ISOComponentNode* node=NULL;
    
    //注意正向，反向node移动的序列位置
    if(dx!=0){
        for(int k=0;k<loopX;k++){
            //横向移动 移动列
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
                this->updateMapCoordinate(index, dirX*m_iComponentTileColumn, -dirX*m_iComponentTileColumn);

//                node=(ISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*m_iComponentTileColumn, my-dirX*m_iComponentTileColumn);
            }
                    
            //纵向移动 移动行
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
//                node=(ISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*m_iComponentTileRow, my+dirX*m_iComponentTileRow);
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
//                node=(ISOComponentNode*) m_pComponents->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx-dirY*m_iComponentTileColumn, my+dirY*m_iComponentTileColumn);
            }
            
            if(dirY>0){
                moveComponentIndexY=m_iComponentIndexY;
                m_iComponentIndexY=(m_iComponentIndexY+1)%totalRow;
            }else if(dirY<0){
                m_iComponentIndexY=(m_iComponentIndexY-1+totalRow)%totalRow;
                moveComponentIndexY=m_iComponentIndexY;
            }
            //纵向移动
            
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

void ISODynamicComponent::updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
    //if(m_pUpdateDelegator) m_pUpdateDelegator->onUpdateComponentMapCoordinate(nodeIndex, deltaMapX, deltaMapY);
    
    updateNodeBy(nodeIndex,deltaMapX,deltaMapY);
}

void ISODynamicComponent::updateNodeBy(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
	ISOComponentNode* node=(ISOComponentNode*) m_pComponents->objectAtIndex(nodeIndex);
    float mx=node->getMapX();
    float my=node->getMapY();
    float newMx=mx+deltaMapX;
    float newMy=my+deltaMapY;
    
//    CCLOG("ISODynamicComponent::updateMapCoordinate from:%f,%f to:%f,%f",mx,my,newMx,newMy);
    
    updateNode(node,newMx,newMy);
}

void ISODynamicComponent::updateNode(ISOComponentNode* node,float mx,float my)
{
    CCPoint pos=ccp(mx,my);
    //更新位置属性
    node->updateMapCoordinate(mx, my);
       
    ISOTile* tile=m_pTileLayer->tileAt(pos);
    
    // if GID == 0, then no tile is present
    if (tile)
    {
        //更新位置
        node->setPosition(isoGameToView2F(mx, my));
        
        m_pTileLayer->reorderChild(node,m_pTileLayer->zOrderForPos(pos));
//        node->reorderChild(m_pTileLayer->zOrderForPos(pos));
        
        //更新显示内容
        node->setVisible(true);
        
        node->setTexture(tile->getTexture());
        node->setTextureRect(tile->getTextureRect());
    }else{
        node->setVisible(false);
    }
}

void ISODynamicComponent::calcComponentsCount()
{    
    m_iComponentTileColumn+=m_iComponentNodeExtendCount;
    m_iComponentTileRow+=m_iComponentNodeExtendCount;
    m_iComponentTileTotalColumn=2*m_iComponentTileColumn;
    m_iComponentTileTotalRow=2*m_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",m_iComponentTileColumn,m_iComponentTileRow);
}

void ISODynamicComponent::setupComponents()
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start,0);

    this->calcComponentsCount();

	gettimeofday(&end,NULL);

	CCLOG("setupComponents1:%d",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);

	gettimeofday(&start,0);

    this->createComponents();
	
	gettimeofday(&end,NULL);

	CCLOG("setupComponents2:%d",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);

	gettimeofday(&start,0);

    this->initComponents();

	gettimeofday(&end,NULL);

	CCLOG("setupComponents3:%d",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
}


void ISODynamicComponent::setupComponents(const CCPoint& position)
{
    this->initOffset(position);
    setupComponents();
}


CCArray* ISODynamicComponent::getComponents(){
    return m_pComponents;
}

void ISODynamicComponent::setComponentTileColumn(int iComponentTileColumn)
{
    m_iComponentTileColumn = iComponentTileColumn;
}

int ISODynamicComponent::getComponentTileColumn()
{
    return m_iComponentTileColumn;
}

void ISODynamicComponent::setComponentTileRow(int iComponentTileRow)
{
    m_iComponentTileRow = iComponentTileRow;
}

int ISODynamicComponent::getComponentTileRow()
{
    return m_iComponentTileRow;
}

void ISODynamicComponent::setComponentTileExtendCount(int iComponentNodeExtendCount)
{
    m_iComponentNodeExtendCount = iComponentNodeExtendCount;
}

int ISODynamicComponent::getComponentTileExtendCount()
{
    return m_iComponentNodeExtendCount;
}

void ISODynamicComponent::initOffset(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
	m_iLastStartX=m_iStartX;
	m_iLastStartY=m_iStartY;
}

void ISODynamicComponent::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

void ISODynamicComponent::scroll(const CCPoint& tOffset)
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

void ISODynamicComponent::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}



void ISODynamicComponent::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void ISODynamicComponent::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint ISODynamicComponent::getOffset()
{
    return m_tOffset;
}

void ISODynamicComponent::setUpdateDelegator(ISODynamicComponentUpdateDelegator* pUpdateDelegator)
{
    m_pUpdateDelegator=pUpdateDelegator;
}

void ISODynamicComponent::setCreateDelegator(ISODynamicComponentCreateDelegator* pCreateDelegator)
{
    m_pCreateDelegator=pCreateDelegator;
}

void ISODynamicComponent::setTileLayer(ISOTileLayer* pTileLayer)
{
    m_pTileLayer = pTileLayer;
}

ISOTileLayer* ISODynamicComponent::getTileLayer()
{
    return m_pTileLayer;
}

NS_CC_YHGE_END
