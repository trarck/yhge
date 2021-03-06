#include "AstarFlexible.h"
#include <yhge/CocosExt/CCGeometryValue.h>

NS_CC_YHGE_BEGIN

static const int DEFAULT_NEARS_LENGTH=8;
static const int ASTAR_G_LINE=10;
static const int ASTAR_G_CROSS=14;

static int defaultNears[][2]={
	{-1 ,-1},{0 ,-1},{1,-1},
	{-1 , 0},        {1, 0},
	{-1 , 1},{0 , 1},{1, 1}
};

AstarFlexible::AstarFlexible(void)
:m_minX(0)
,m_minY(0)
,m_maxX(0)
,m_maxY(0)
,m_start(NULL)
,m_end(NULL)
,m_current(NULL)
,m_delegate(NULL)
{
	
}

AstarFlexible::~AstarFlexible(void)
{
	CC_SAFE_RELEASE(m_opens);
	CC_SAFE_RELEASE(m_closes);
	CC_SAFE_RELEASE(m_openSeq);
	CC_SAFE_RELEASE(m_start);
	CC_SAFE_RELEASE(m_end);
	
}

bool AstarFlexible::init()
{

	m_openSeq=new CCArray(10);
	m_opens=new CCDictionary();
	m_closes=new CCDictionary();
	
	return true;
}



void AstarFlexible::setMinX(int minX)
{
    m_minX = minX;
}

int AstarFlexible::getMinX()
{
    return m_minX;
}

void AstarFlexible::setMinY(int minY)
{
    m_minY = minY;
}

int AstarFlexible::getMinY()
{
    return m_minY;
}

void AstarFlexible::setMaxX(int maxX)
{
    m_maxX = maxX;
}

int AstarFlexible::getMaxX()
{
    return m_maxX;
}

void AstarFlexible::setMaxY(int maxY)
{
    m_maxY = maxY;
}

int AstarFlexible::getMaxY()
{
    return m_maxY;
}


static AstarFlexible * astarInstance=NULL;

AstarFlexible* AstarFlexible::sharedAstar()
{
	if(astarInstance==NULL){
		astarInstance=new AstarFlexible();
		astarInstance->init();
	}
	return astarInstance;
}


void AstarFlexible::reset()
{
    CC_SAFE_RELEASE(m_opens);
	CC_SAFE_RELEASE(m_closes);
	CC_SAFE_RELEASE(m_openSeq);


	m_openSeq=new CCArray(10);
	m_opens=new CCDictionary();
	m_closes=new CCDictionary();
}
/*
 * 搜索范围
 */
void AstarFlexible::setBounding(int minX ,int minY,int maxX,int maxY)
{
	m_minX=minX;
	m_minY=minY;
	m_maxX=maxX;
	m_maxY=maxY;
}

/**
 * 开始点
 */
void AstarFlexible::setStart(int x ,int y)
{
	CC_SAFE_RELEASE(m_start);
	m_start=new AstarNode();
	m_start->init(x,y);
	addToOpen(m_start);
}

/**
 * 结束点
 */
void AstarFlexible::setEnd(int x ,int y)
{
	CC_SAFE_RELEASE(m_end);
	m_end=new AstarNode();
	m_end->init(x,y);	
}

bool AstarFlexible::search()
{
	
	//如果开始和结束点是同一点、终点超出范围,不必寻路。
	if (isEnd(m_start->getX(),m_start->getY())|| isOut(m_end->getX(),m_end->getY())){
		return false;
	}
	
	while (m_openSeq->count()) {
		//取得下一个搜索点 
		getNext();
		removeFromOpen(m_current);
		//添加到closes
		addToClose(m_current->getX(),m_current->getY());
		
		//处理相邻结点
		if(checkNearby()){
			return true;
		}
	}
	return false;
}

bool AstarFlexible::checkNearby()
{
	int i=0,j=0,x=0,y=0,k=0,g=0,h=0;
	
	AstarNode* searchedNode;
	
	for(;k<DEFAULT_NEARS_LENGTH;k++){
		//near=defaultNears[k];
		i=defaultNears[k][0];
		j=defaultNears[k][1];
		
		x=m_current->getX()+i;
		y=m_current->getY()+j;
		
		//结束提前，可对目标是障碍物进行寻路。(例:人物要对某个建筑进行操作，比如攻击，要走到建筑旁边才可以)
		if (isEnd(x,y ,i ,j)) {//如果是斜着寻路，则要对旁边是否有障碍物进行判断。
			return true;//查找成功
		}
		
		if(!isOut(x,y) && isWorkableWithCrossSide(x ,y ,i ,j)){
			if(!isInClose(x ,y)){
				g=m_current->getG()+(i==0||j==0?ASTAR_G_LINE:ASTAR_G_CROSS);
				searchedNode=getFromOpen(x ,y);
				if(searchedNode!=NULL){
					//在开起列表中，比较G值
					if (g < searchedNode->getG()) {
						//有最小F值，重新排序
						setOpenSeqNode(searchedNode,g);
					}
				}else {
					//没有搜索过，直接添加到开起列表中
					h=getH(x ,y);
					AstarNode* astarNode=new AstarNode();
					astarNode->init(x ,y,g,h);
					astarNode->setParent(m_current);
					addToOpen(astarNode);
					astarNode->release();
				}
			}
		}
	}
	return false;
}

void AstarFlexible::getNext()
{
	CC_SAFE_RELEASE(m_current);
	m_current=(AstarNode*)m_openSeq->objectAtIndex(0);
	m_current->retain();
}

void AstarFlexible::setOpenSeqNode(AstarNode* node ,int g)
{
	node->retain();
	m_openSeq->removeObject(node);
	node->setG(g);
	node->setF(node->getG()+node->getH());

	int i=0;
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(m_openSeq,pObject){
		AstarNode* it=(AstarNode*)pObject;
		if(node->getF()<it->getF()) break;
		i++;
	}

	m_openSeq->insertObject(node,i);
	CC_SAFE_RELEASE(node);
}

void AstarFlexible::addToOpen(AstarNode* node)
{
	//CCLOG("addToOpen %d,%d",node->getX(),node->getY());
	int i=0;
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(m_openSeq,pObject){
		AstarNode* it=(AstarNode*)pObject;
		if(node->getF()<it->getF()) break;
		i++;
	}
	m_openSeq->insertObject(node,i);
	
	CCDictionary* ymd=(CCDictionary*)m_opens->objectForKey(node->getY());
	if (ymd==NULL) {
		ymd=new CCDictionary();
		m_opens->setObject(ymd,node->getY());
		CC_SAFE_RELEASE(ymd);
	}
	
	ymd->setObject(node,node->getX());
}

void AstarFlexible::removeFromOpen(AstarNode* node)
{
	m_openSeq->removeObject(node);

	CCDictionary* ymd=(CCDictionary*)m_opens->objectForKey(node->getY());
	if (ymd!=NULL) {
		ymd->removeObjectForKey(node->getX());
	}
}

bool AstarFlexible::isInOpen(int x ,int y)
{
	CCDictionary* ymd=(CCDictionary*)m_opens->objectForKey(y);

	if(ymd==NULL) return false;

	AstarNode* node=(AstarNode*)ymd->objectForKey(x);

	return node!=NULL;
}

AstarNode* AstarFlexible::getFromOpen(int x ,int y)
{
	//CCLOG("addToOpen %d,%d",x,y);
	CCDictionary* ymd=(CCDictionary*)m_opens->objectForKey(y);
	if(ymd==NULL) return NULL;
	
	AstarNode* node=(AstarNode*)ymd->objectForKey(x);

	return node;
}

void AstarFlexible::addToClose(int x,int y)
{

	CCDictionary* ymd=(CCDictionary*)m_closes->objectForKey(y);
	if (ymd==NULL) {
		ymd=new CCDictionary();
		m_closes->setObject(ymd,y);
		ymd->release();
	}
	
	CCInteger* data=CCInteger::create(1);
	ymd->setObject(data,x);
}

bool AstarFlexible::isInClose(int x ,int y)
{
	CCDictionary* ymd=(CCDictionary*)m_closes->objectForKey(y);
	if(ymd==NULL) return false;
	CCInteger* data=(CCInteger*)ymd->objectForKey(x);

	return data!=NULL;
}

int AstarFlexible::getH(int x ,int y)
{
	return abs(m_end->getX()-x)*ASTAR_G_LINE+abs(m_end->getY()-y)*ASTAR_G_LINE;
}

bool AstarFlexible::isOut(int x ,int y)
{
	//return y<m_minX||y>=m_maxY ||x<m_minX || x>=m_maxX;
	return y<m_minY||y>m_maxY ||x<m_minX || x>m_maxX;
}

//本身和到达时斜对角是否可以通过
bool AstarFlexible::isWorkableWithCrossSide(int x ,int y ,int stepX ,int stepY)
{
	bool ret=isWorkable(x,y);
	if (stepX!=0 && stepY !=0) {
		ret&=isWorkable(x,y-stepY) && isWorkable(x-stepX ,y);
	}
	return ret;
}
//到达x,y时，斜对角是否可以通过
//x,y搜索点，当前点为x-stepX,y-stepY
bool AstarFlexible::isCrossSideWorkable(int x ,int y ,int stepX ,int stepY)
{
	return stepX==0 || stepY ==0 || (isWorkable(x,y-stepY) && isWorkable(x-stepX,y));
}

bool AstarFlexible::isEnd(int x ,int y)
{
	return m_end->getX()==x && m_end->getY()==y;
}

bool AstarFlexible::isEnd(int x ,int y ,int stepX ,int stepY)
{
	return m_end->getX()==x && m_end->getY()==y && isCrossSideWorkable(x,y ,stepX ,stepY);
}

//本身是否可以通过
bool AstarFlexible::isWorkable(int x,int y) 
{
	return m_delegate->isWorkable(x,y);
}

//void  AstarFlexible::setCheckBarrierHandle(SEL_CheckBarrierHandler checkBarrierHandle,CCObject* target)
//{
//	m_checkBarrierHandle=checkBarrierHandle;
//	m_target=target;
//}

// void setCheckBarrierHandle(FUN_CheckBarrierHandler isWorkable)
// {
// 	
// }
	
//取得路径  路径是反向的，从终点指向起点，不包含终点和起点。
CCArray* AstarFlexible::getPath()
{
	CCArray* paths=CCArray::create();
	AstarNode* node=m_current;
	
	while (node && node->getParent()!=NULL) {
		CCPointValue* p=new CCPointValue(node->getX(),node->getY());
		paths->addObject(p);
		p->release();
		node=node->getParent();
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含起点，不包含终点。
CCArray* AstarFlexible::getPathWithStart()
{
	CCArray* paths=CCArray::create();
	AstarNode* node=m_current;
	
	while (node) {
		CCPointValue* p=new CCPointValue(node->getX(),node->getY());
		paths->addObject(p);
		p->release();
		node=node->getParent();
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点，不包含起点。
CCArray* AstarFlexible::getPathWithEnd()
{
	CCArray* paths=getPath();
	CCPointValue* p=new CCPointValue(m_end->getX(),m_end->getY());
	paths->insertObject(p,0);
	p->release();
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点和起点。
CCArray* AstarFlexible::getPathWithStartEnd()
{
	CCArray* paths=getPathWithStart();
	CCPointValue* p=new CCPointValue(m_end->getX(),m_end->getY());
	paths->insertObject(p,0);
	p->release();
	paths->insertObject(p,0);
	return paths;
}

NS_CC_YHGE_END
