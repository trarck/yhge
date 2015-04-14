/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "GridMoveComponent.h"
#include <yhge/Base/Log.h>
#include <yhge/message.h>
#include <yhge/CocosExt/CCGeometryValue.h>
#include <yhge/isometric.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"


#define AXIS_VECTOR 1
//sqrt(2)
#define BEVEL_VECTOR 1.41421356f
#define BEVEL_VECTOR_HALF 0.70710678f
#define MOVIE_TIME_UNIT 1
#define FLOAT_ZERO_FLAG 0.00001

USING_NS_CC;

NS_CC_YHGE_BEGIN

static int directionMapping[3][3]={
	{4,1,5},
	{0,-1,2},
	{7,3,6}
};

static float MoveDurationMap[3][3]={
	{BEVEL_VECTOR*MOVIE_TIME_UNIT,AXIS_VECTOR*MOVIE_TIME_UNIT,BEVEL_VECTOR*MOVIE_TIME_UNIT},
	{AXIS_VECTOR*MOVIE_TIME_UNIT,0,AXIS_VECTOR*MOVIE_TIME_UNIT},
	{BEVEL_VECTOR*MOVIE_TIME_UNIT,AXIS_VECTOR*MOVIE_TIME_UNIT,BEVEL_VECTOR*MOVIE_TIME_UNIT}
};

/**
 * 按地图的格子移动
 * 每次移动一个格子的距离
 * 原始数据使用地图坐标，移动过程(动画)使用屏幕坐标
 */
GridMoveComponent::GridMoveComponent()
:Component("GridMoveComponent")
,_moveState(MoveIdle)
,_moveType(kMoveNone)
,_speed(0.0f)
,_speedX(0.0f)
,_speedY(0.0f)
,_fViewSpeedX(0.0f)
,_fViewSpeedY(0.0f)
,_directionX(0)
,_directionY(0)
,_lastDirectionX(0)
,_lastDirectionY(0)
,_nextDirectionX(0)
,_nextDirectionY(0)
,_bKeepMoveDirection(false)
,_movingDuration(0.0f)
,_movingDeltaTime(0.0f)
,_to(ccp(0.0f, 0.0f))
,_moving(false)
,_fromIndex(0)
,_pCurrentPaths(NULL)
,_pNextPaths(NULL)
,_pathIndex(0)
,_update(NULL)
,_moveableDelegate(NULL)
,_isoPositionComponent(NULL)
//,_rendererComponent(NULL)
{

}

GridMoveComponent::~GridMoveComponent()
{
	CC_SAFE_RELEASE(_pCurrentPaths);
	CC_SAFE_RELEASE(_pNextPaths);
}

bool GridMoveComponent::init()
{
	if(Component::init()){
		_moveState=MoveStop;      
	}
    return true;
	
}

bool GridMoveComponent::init(float speed)
{
	if (init()) {
		_speed=speed;
	}
	return true;
}

void GridMoveComponent::setup()
{
    Component::setup();
    _isoPositionComponent=static_cast<ISOPositionComponent*>(_owner->getComponent("ISOPositionComponent"));
//    _rendererComponent=static_cast<RendererComponent*>(_owner->getComponent("RendererComponent"));
}

void GridMoveComponent::cleanup()
{
    _isoPositionComponent=NULL;
//    _rendererComponent=NULL;
    stopMoveUpdateSchedule();
    Component::cleanup();
}

bool GridMoveComponent::registerMessages()
{
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(_owner, MSG_MOVE_DIRECTION, NULL, MESSAGE_SELECTOR(GridMoveComponent::onMoveWithDirection),this);
        messageManager->registerReceiver(_owner, MSG_MOVE_PATH, NULL, MESSAGE_SELECTOR(GridMoveComponent::onMoveWithPath),this);
        messageManager->registerReceiver(_owner, MSG_MOVE_PATH_FROM, NULL, MESSAGE_SELECTOR(GridMoveComponent::onMoveWithPathFrom),this);
        messageManager->registerReceiver(_owner, MSG_MOVE_STOP, NULL, MESSAGE_SELECTOR(GridMoveComponent::onMoveStop),this);
        
        return true;
    }
    
    return false;
}

void GridMoveComponent::cleanupMessages()
{    
    MessageManager* messageManager=MessageManager::defaultManager();
    
    messageManager->removeReceiver(_owner, MSG_MOVE_DIRECTION);
    messageManager->removeReceiver(_owner, MSG_MOVE_PATH);
    messageManager->removeReceiver(_owner, MSG_MOVE_PATH_FROM);
    messageManager->removeReceiver(_owner, MSG_MOVE_STOP);
    
    Component::cleanupMessages();
}

/**
 * 停止移动
 * 立即停止移动
 */
void GridMoveComponent::stop()
{
	_moveState=MoveWillStop;
    stopMove();
}

/**
 * 移动之前进行检查
 */

bool GridMoveComponent::checkMoveable()
{
    if (_moveableDelegate) {
        return _moveableDelegate->isWorkable(_to.x,_to.y);
    }
	return true;
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void GridMoveComponent::moveWithDirection(int directionX ,int directionY)
{
    //_update=this->getUpdateDirectionHandle();

	if (_moveState==MoveStop) {
        
        _moveType=kMoveDirection;
        
		resetState();
		prepareDirection(directionX, directionY);
		if(checkMoveable()){
			prepareMove();
			startMove();
			doDirectionChange();
		}
	}else {
		continueMoveWithDirection(directionX,directionY);
	}
}

/**
 * 断续指定方向移动
 */
void GridMoveComponent::continueMoveWithDirection(int directionX ,int directionY)
{
    CCAssert(_moveType==kMoveDirection, "GridMoveComponent::continueMoveWithDirection before move type is not the same");
	setNextDirection(directionX,directionY);
	_moveState=MoveContinue;
}

/**
 * 移动之前准备一下
 */
void GridMoveComponent::prepareDirection(int directionX,int directionY)
{
	setDirection(directionX,directionY);
	calcTo();
}

/**
 * 计算移动时间
 * direction取值为-1,0,1
 */
void GridMoveComponent::calcMoveDuration(int directionX,int directionY)
{
	//计算本次移动所需要的时间
	//+1.由于-1=<directionX<=1,偏移一个1，正好0<=directionX+1<=2。起点和数组下标吻合
	int i=directionX+1;
	int j=directionY+1;
	CCAssert(i>=0 && i<=2,"prepareDirection error the direction out of range");
	CCAssert(j>=0 && j<=2,"prepareDirection error the direction out of range");
	_movingDuration=MoveDurationMap[i][j]/_speed;

	YHDEBUG("_movingDuration:%f",_movingDuration);
	//float absDirX=abs(directionX);
	//float absDirY=abs(directionY);

	//if((absDirX<FLOAT_ZERO_FLAG&&absDirY>FLOAT_ZERO_FLAG)||(absDirX>FLOAT_ZERO_FLAG&&absDirY<FLOAT_ZERO_FLAG)){
	//	_movingDuration=AXIS_VECTOR*1000;//毫秒
	//}else{
	//	if(abs(directionX)>FLOAT_ZERO_FLAG&&abs(directionY)>FLOAT_ZERO_FLAG){
	//		_movingDuration=BEVEL_VECTOR *1000;
	//	}else{
	//		_movingDuration=0;
	//	}
	//}
	

}

/**
 * 计算屏幕速度
 * direction -1,0,1
 */
void GridMoveComponent::calcSpeedVector(int directionX,int directionY)
{
	int i=directionX;
	int j=directionY;

    //注意_speed是地图坐标系的速度，即做iso投影前的速度
	if(i==0||j==0){
		//_speedX,_speedY其中一个为0或都为0
		_speedX=i*_speed*AXIS_VECTOR;
		_speedY=j*_speed*AXIS_VECTOR;
	}else{
		//_speedX,_speedY都不为0，为speed的sqrt(2)/2
		//speed的大小不变，分量的是变化的。由于是45度地图，所以只有一种变化sqrt(2)/2
		_speedX=i*_speed*BEVEL_VECTOR_HALF;
		_speedY=j*_speed*BEVEL_VECTOR_HALF;
	}

	CCPoint viewSpeed=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_speedX,_speedY));
	_fViewSpeedX=viewSpeed.x;
	_fViewSpeedY=viewSpeed.y;
	YHDEBUG("_speedX:%f,_speedY:%f,viewSpeed:%f,%f",_speedX,_speedY,_fViewSpeedX,_fViewSpeedY);
}

/**
 * 计算移动到的位置
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcTo()
{
    if (_isoPositionComponent) {
        _to.x=_isoPositionComponent->getX()+_directionX;
        _to.y=_isoPositionComponent->getY()+_directionY;
    }
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcDirection()
{
    CCAssert(_isoPositionComponent!=NULL, "GridMoveComponent::calcDirection _isoPositionComponent can't be null");
    
	float mx=_isoPositionComponent->getX();
	float my=_isoPositionComponent->getY();
	setDirection(_to.x>mx?1:_to.x<mx?-1:0,_to.y>my?1:_to.y<my?-1:0);
}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void GridMoveComponent::updateDirection( float delta)
{
//    CCNode* renderer=_rendererComponent->getRenderer();
//	CCPoint pos=renderer->getPosition();
    CCPoint pos=_isoPositionComponent->getRendererPosition();

	_movingDeltaTime+=delta;
	if(_movingDeltaTime<_movingDuration){
		pos.x+=delta*_fViewSpeedX;
		pos.y+=delta*_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOGINFO("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,_fViewSpeedX,_fViewSpeedY,delta);
        
//		renderer->setPosition(pos);
//        renderer->setZOrder(-(int)pos.y);
        //这里使用了虚函数，如果担心会影响性能，可以直接替换_isoPositionComponent成一个没有虚函数的组件。
        //但是一般性能影响可以忽略。
        _isoPositionComponent->updateRendererPositionDirectly(pos);
	}else{
		//一个路径结点移动完成,设置成终点所在的位置。使用时间计算出来的终点位置可能不准。
//        pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_to.x,_to.y));
////		renderer->setPosition(pos);
////        renderer->setZOrder(-(int)pos.y);
//        _isoPositionComponent->updateRendererPositionDirectly(pos);
        _isoPositionComponent->updateRendererPosition();
		if (_moveState==MoveContinue) {
			prepareDirection(_nextDirectionX, _nextDirectionY);
    		this->continueUpdate();
		}else{
			if(_bKeepMoveDirection){
				if(checkMoveable()){
					_movingDeltaTime=0;
				}else{
					stop();
				}
			}else{
				stop();
			}
		}
	}
}

/**
 * 按指定路径移动
 */
void GridMoveComponent::moveWithPaths(CCArray* paths)
{
	moveWithPaths(paths ,0);
}

void GridMoveComponent::moveWithPaths(CCArray* paths,int fromIndex)
{
	//_update=this->getUpdatePathHandle();//schedule_selector(GridMoveComponent::updatePath);

	if(_moveState==MoveStop){
        
        _moveType=kMovePath;
        
		resetState();
		_fromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (checkMoveable()) {
			prepareMove();
			startMove();
			doDirectionChange();
		}
	}else{
		_fromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}
}
/**
 * 继续指定路径移动
 */
void GridMoveComponent::continueMoveWithPaths(CCArray* paths)
{
    CCAssert(_moveType==kMovePath, "GridMoveComponent::continueMoveWithDirection before move type is not the same");
    
	this->setNextPaths(paths);	
	_moveState=MoveContinue;
}

void GridMoveComponent::restartMoveWithPaths()
{
	_moveState=MoveStart;
	preparePath();
}


/**
 * 准备移动路径
 */
void GridMoveComponent::preparePath()
{
	_pathIndex=getCurrentPathIndex();
	preparePath(_pathIndex);
}

/**
 * 准备移动路径
 */
void  GridMoveComponent::preparePath(int pathIndex)
{
	CCAssert(pathIndex>=0,"paths length less 2");
	YHDEBUG("preparePath.iPathIndex:%d",pathIndex);
    _to=  static_cast<CCPointValue*>(_pCurrentPaths->objectAtIndex(pathIndex))->getPoint();
	calcDirection();
}

/**
 * 取得当前路径结点索引
 */
int GridMoveComponent::getCurrentPathIndex(){
	return _pCurrentPaths->count()-1 -_fromIndex;
}


/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void GridMoveComponent::updatePath(float delta)
{
//    CCNode* renderer=_rendererComponent->getRenderer();
//    
//	CCPoint pos=renderer->getPosition();
    
    CCPoint pos=_isoPositionComponent->getRendererPosition();
	
	_movingDeltaTime+=delta;
	
	//CCLOGINFO("upate:%f,%f,%f",delta,_movingDeltaTime,_movingDuration);
	if(_movingDeltaTime<_movingDuration){
		//CCLOGINFO("posx1:%f,posy:%f:%f,%f:%f",pos.x,pos.y,_fViewSpeedX,_fViewSpeedY,delta);
		pos.x+=delta*_fViewSpeedX;
		pos.y+=delta*_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOGINFO("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,_fViewSpeedX,_fViewSpeedY,delta);
//		renderer->setPosition(pos);
//        renderer->setZOrder(-(int)pos.y);
        //这里使用了虚函数，如果担心会影响性能，可以直接替换_isoPositionComponent成一个没有虚函数的组件。
        //但是一般性能影响可以忽略。
        _isoPositionComponent->updateRendererPositionDirectly(pos);
	}else{
		//一个路径结点移动完成,设置成终点所在的位置。使用时间计算出来的终点位置可能不准。
//        pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_to.x,_to.y));
////		renderer->setPosition(pos);
////        renderer->setZOrder(-(int)pos.y);
//        _isoPositionComponent->updateRendererPositionDirectly(pos);
        _isoPositionComponent->updateRendererPosition();
        //设置地图坐标
		if (_moveState==MoveContinue) {
			if (_pNextPaths!=NULL) {
				_moveState=MoveStart;
				this->setCurrentPaths(_pNextPaths);
				preparePath();
				this->continueUpdate();
			}
		}else if (--_pathIndex>=0 && _moveState==MoveStart) {
			YHDEBUG("next cell %d",_pathIndex);
			//进行下一个格子
			preparePath(_pathIndex);
			this->continueUpdate();
		}else {
			//stop move
			this->setCurrentPaths(NULL);
			completeMove();
		}
	}
}

/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void GridMoveComponent::doDirectionChange()
{
	if (_moveState!=MoveStop && _lastDirectionX==_directionX && _lastDirectionY==_directionY) {
		return;
	}
	int i=floor(_directionX)+1;
	int j=floor(_directionY)+1;
	int index=directionMapping[i][j];
	//CCLOGINFO("index:%d,%d,%d,%f,%f",index,i,j,_directionX,_directionY);
	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
		data->setObject(CCInteger::create(index), COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION);
    
		MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, _owner,data);
	}
}

/**
 * 开始移动的时候做一些事情。
 */
void GridMoveComponent::doMoveStart()
{
   
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void GridMoveComponent::doMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
    data->setObject(CCInteger::create(0), COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION);
    
    getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, _owner,data);

    getMessageManager()->dispatchMessage(MSG_MOVE_STOPED,this,_owner);
}

/**
 * 移动被打断做一些事情。
 * 比如，通知游戏世界，重新寻路。
 */
void GridMoveComponent::doHit(CCPoint location)
{
	
}

void GridMoveComponent::onMoveWithDirection(Message *message)
{
    CCPoint direction=static_cast<CCPointValue*>(message->getData())->getPoint();
    moveWithDirection((int)direction.x,(int)direction.y);
}

void GridMoveComponent::onMoveWithPath(Message *message)
{
    CCArray* paths=(CCArray*)message->getData();
    moveWithPaths(paths);
}

void GridMoveComponent::onMoveWithPathFrom(Message *message)
{   
    CCDictionary* data=message->getDictionary();
    
    CCArray* paths=(CCArray*)data->objectForKey(COMPONENT_GRID_MOVE_RARAM_PATHS);
    CCInteger* fromIndex=static_cast<CCInteger*>(data->objectForKey(COMPONENT_GRID_MOVE_RARAM_FROMINDEX));
    moveWithPaths(paths,fromIndex->getValue());
}

void GridMoveComponent::onMoveStop(Message *message)
{
    stopMove();
}

/**
 * 设置方向。
 */
void GridMoveComponent::setDirection(int directionX,int directionY)
{
	_lastDirectionX=_directionX;
	_lastDirectionY=_directionY;
	_directionX=directionX;
	_directionY=directionY;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void GridMoveComponent::startMove()
{
	_movingDeltaTime=0;

	_moveState=MoveStart;

    startMoveUpdateSchedule();
    //CCDirector* director = CCDirector::sharedDirector();
    //CCScheduler* pScheduler = director->getScheduler();
    //pScheduler->scheduleSelector(_update,this, 0, false);

    doMoveStart();
}

/**
 * 停止移动
 * 等待一个格子移动结束
 */
void GridMoveComponent::stopMove()
{
	if(_moveState==MoveStart){
		_moveState=MoveWillStop;
	}else {
        //CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
        //pScheduler->unscheduleSelector(_update, this);
        stopMoveUpdateSchedule();
		_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		doMoveStop();
	}
}
void GridMoveComponent::prepareMove()
{
	calcMoveDuration(_directionX,_directionY);
	calcSpeedVector(_directionX,_directionY);
    _isoPositionComponent->setCoordinate(_to);
}

void GridMoveComponent::continueUpdate()
{
	if(checkMoveable()){
		_moveState=MoveStart;
		_movingDeltaTime=0;
		this->prepareMove();
		doDirectionChange();
	}else{
		stop();
	}
}

void GridMoveComponent::resetState()
{
	_directionX=0;
	_directionY=0;
	_lastDirectionX=0;
	_lastDirectionY=0;
	_nextDirectionX=0;
    _nextDirectionY=0;
}

void GridMoveComponent::completeMove()
{
    stop();
    
    //send move complete message
    getMessageManager()->dispatchMessage(MSG_MOVE_COMPLETE,this,_owner,CCPointValue::create(_to));

}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void GridMoveComponent::startMoveUpdateSchedule()
{
    switch (_moveType)
    {
    case kMoveDirection:
        _update=schedule_selector(GridMoveComponent::updateDirection);
        break;
    case kMovePath:
        _update=schedule_selector(GridMoveComponent::updatePath);
        break;
    default:
        break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(_update,this, 0, false);
}

void GridMoveComponent::stopMoveUpdateSchedule()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(_update,this);
    _update=NULL;
}

SEL_SCHEDULE GridMoveComponent::getUpdateDirectionHandle()
{
    return schedule_selector(GridMoveComponent::updateDirection);
}

SEL_SCHEDULE GridMoveComponent::getUpdatePathHandle()
{
    return schedule_selector(GridMoveComponent::updatePath);
}

NS_CC_YHGE_END
