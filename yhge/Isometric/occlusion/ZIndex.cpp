//
//  ZIndex.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "ZIndex.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ZIndex::ZIndex()
:_statics(NULL)
,_dynamics(NULL)
,_sortLayer(NULL)
,_isWorking(true)
,_staticDirty(true)
{
    
}

ZIndex::~ZIndex()
{
    CC_SAFE_RELEASE(_statics);
    CC_SAFE_RELEASE(_dynamics);
    CC_SAFE_RELEASE(_sortLayer);
}

static ZIndex *s_zIndex=NULL;
ZIndex* ZIndex::sharedZIndex()
{
	if(!s_zIndex){
		s_zIndex=new ZIndex();
        s_zIndex->init();
	}
	return s_zIndex;
}

ZIndex* ZIndex::create(CCLayer* sortLayer)
{
    ZIndex* zIndex=new ZIndex();
    zIndex->init(sortLayer);
    zIndex->autorelease();
	return zIndex;
}

bool ZIndex::init()
{
    _statics=new CCArray(20);
    _dynamics=new CCArray(20);
    _isWorking=false;

    _pfnUpdate=schedule_selector(ZIndex::update);
	return true;
}

bool ZIndex::init(CCLayer* sortLayer)
{
    init();
    _sortLayer=sortLayer;

	return true;
}


void ZIndex::insertStatic(ZIndexNode* node)
{
	//注意insertSort反回的数组已经是加1的，如果使用self.statics=[self insertSort:node data:_statics]，
	//则会使statics_的引用数为2，下一次再执行该函数时，则已以前的statics_无法释放。
	CCArray * results=insertSort(node ,_statics);

    CC_SAFE_RELEASE(_statics);
	_statics=results;
	_staticDirty=true;
}

void ZIndex::insertDynamic(ZIndexNode*  node)
{
	_dynamics->addObject(node);
}

void ZIndex::removeStatic(ZIndexNode* node)
{
	_statics->removeObject(node);
}

void ZIndex::removeDynamic(ZIndexNode* node)
{
	_dynamics->removeObject(node);
}

CCArray* ZIndex::insertSort(ZIndexNode* node ,CCArray* rects)
{
	CCRect src;
    CCRect rect=node->getRect();
	int side,l=rects->count();
	bool maxAppear=false;
	CCArray* results=NULL;

    if(l>0){
		ZIndexNode* fromNode=(ZIndexNode*)rects->objectAtIndex(l-1);
		CCRect from=fromNode->getRect();
		side=caculateSideFrom(&from,&rect);
		
		if(side<0){
			results=new CCArray(l+1);
			results->addObjectsFromArray(rects);
			results->addObject(node);
		}else{
			CCArray *maxs=new CCArray(l/2);
			CCArray *mins=new CCArray(l/2);
            
            Ref* pObject = NULL;
	        CCARRAY_FOREACH(rects,pObject){
			    ZIndexNode*it=(ZIndexNode*)pObject;
				src=it->getRect();
				side=caculateSideFrom(&src,&rect);
				//NSLog(@"side:%d,from:%f,%f to:%f,%f",side,src.origin.x,src.origin.y,rect.origin.x,rect.origin.y);
				switch (side) {
					case -1:
					case -2:
						mins->addObject(it);
						break;
					case 1:
					case 2:
						maxs->addObject(it);
						maxAppear=true;
						break;
					case 0:
						if (maxAppear) {
							maxs->addObject(it);
						}else {
							mins->addObject(it);
						}
						break;

					default:
						break;
				}
			}
			mins->addObject(node);
			mins->addObjectsFromArray(maxs);
			results=mins;
			maxs->release();
		}
	}
	return results;
}

CCArray* ZIndex::sort()
{
	CCArray* temps=new CCArray();
	temps->initWithArray(_statics);
	CCArray* items=NULL;
	
	//sort dynamics
    Ref* pObject=NULL;
    CCARRAY_FOREACH(_dynamics,pObject){
	    ZIndexNode* it=(ZIndexNode*) pObject;
		items=insertSort(it ,temps);
		temps->release();
		temps=items;
	}
	return items;
}

void ZIndex::update(float delta)
{
	//update z-index

	if (_dynamics->count()>0) {
	    CCArray* items=sort();
		//NSLog(@"%@",_sortLayer);
		int i=1;
        Ref* pObject=NULL;
        CCARRAY_FOREACH(items,pObject){
		    ZIndexNode* it=(ZIndexNode*)pObject;
            CCNode* node=(CCNode*)it->getEntity();
			_sortLayer->reorderChild(node,i++);
		}
		items->release();
	}else if (_staticDirty) {
		int i=1;
        Ref* pObject=NULL;
        CCARRAY_FOREACH(_statics,pObject){
            ZIndexNode* it=(ZIndexNode*)pObject;
            CCNode* node=(CCNode*)it->getEntity();
		    _sortLayer->reorderChild(node,i++);
        }
		_staticDirty=false;
	}
}

void ZIndex::start()
{
	if(_isWorking) return;
	_isWorking=true;
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(_pfnUpdate,this,1,false);
}

void ZIndex::stop()
{
	if (_isWorking) {
		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(_pfnUpdate,this);
		_isWorking=false;
	}
}

int ZIndex::caculateSideFrom(CCRect* pFrom ,CCRect* pTo)
{
	int lr, tb;//如果要确切的知道8个方位。上下左右分别用1,4,2,8表示，中还是用0。这样二二之各就可以确定方位。

	if (pTo->origin.x > pFrom->origin.x+pFrom->size.width|| fabs(pTo->origin.x- (pFrom->origin.x+pFrom->size.width))<0.0001 ) {
		//右
		lr = 1;
	}else if(pTo->origin.x+pTo->size.width<pFrom->origin.x||fabs(pTo->origin.x+pTo->size.width-pFrom->origin.x)<0.0001){
		//左
		lr = -1;
	} else  {//desc.right<=src.right && desc.left>=src.left(内中),desc.right>=src.right && desc.left<=src.left(外中) 都算中
		//中
		lr = 0;
	}
	
	if (pTo->origin.y > pFrom->origin.y+pFrom->size.height||fabs(pTo->origin.y-( pFrom->origin.y+pFrom->size.height))<0.0001) {
		//下
		tb = 1;
	} else if (pTo->origin.y+pTo->size.height < pFrom->origin.y ||fabs(pTo->origin.y+pTo->size.height -pFrom->origin.y)<0.0001) {
		//上
		tb = -1;
	} else {
		//中
		tb = 0;
	}

	return lr + tb;
}

void ZIndex::setUpdate(SEL_SCHEDULE pfnUpdate)
{
    _pfnUpdate=pfnUpdate;
}

NS_CC_YHGE_ISOMETRIC_END