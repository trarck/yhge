/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "GridMoveComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCGeometryValue.h>
#include <yhge/isometric.h>
#include "ComponentMessageDefine.h"

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

GridMoveComponent::GridMoveComponent()
:m_speed(0.0f)
,m_direction(0.0f)
,m_directionX(0)
,m_directionY(0)
,m_moving(false)
,m_to(ccp(0.0f, 0.0f))
,m_hasEndPosition(false)
,m_isDirectionDirty(true)
,m_pCurrentPaths(NULL)
,m_pNextPaths(NULL)
,m_lastDirectionX(0)
,m_lastDirectionY(0)
{
    CCLOG("GridMoveComponent create");
	m_name="GridMoveComponent";
}

GridMoveComponent::~GridMoveComponent()
{
    CCLOG("GridMoveComponent destroy");
	CC_SAFE_RELEASE(m_pCurrentPaths);
	CC_SAFE_RELEASE(m_pNextPaths);
}

bool GridMoveComponent::init()
{
	if(Component::init()){
		m_moveState=MoveStop;      
	}
    return true;
	
}

bool GridMoveComponent::init(float speed)
{
	if (init()) {
		m_speed=speed;
	}
	return true;
}

bool GridMoveComponent::registerMessages()
{
    CCLOG("GridMoveComponent::registerMessages");
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION, NULL, message_selector(GridMoveComponent::onMoveDirection),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION_STOP, NULL, message_selector(GridMoveComponent::onMoveDirectionStop),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_TO, NULL, message_selector(GridMoveComponent::onMoveTo),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_PATH, NULL, message_selector(GridMoveComponent::onMovePath),this);
        
        return true;
    }
    
    return false;
}

void GridMoveComponent::cleanupMessages()
{
	CCLOG("GridMoveComponent::cleanupMessages");
    
    MessageManager* messageManager=MessageManager::defaultManager();
    
    messageManager->removeReceiver(m_owner, MSG_MOVE_DIRECTION);
    messageManager->removeReceiver(m_owner, MSG_MOVE_DIRECTION_STOP);
    messageManager->removeReceiver(m_owner, MSG_MOVE_TO);
    messageManager->removeReceiver(m_owner, MSG_MOVE_PATH);
    
    Component::cleanupMessages();
}

bool GridMoveComponent::isMoving()
{
    return m_moving;
}

MoveState GridMoveComponent::getMoveState()
{
    return m_moveState;
}

/**
 * 移动之前进行检查
 */

bool GridMoveComponent::checkMoveable()
{
	return true;
}

/**
 * 移动结束
 */

void GridMoveComponent::stop()
{
	m_moveState=MoveWillStop;
    _stopMove();
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void GridMoveComponent::_startMove()
{
	m_movingDeltaTime=0;
    CCLOG("_startMove");
	m_moveState=MoveStart;
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->scheduleSelector(m_update,this, 0, false);
    doMoveStart();
}

/**
 * 停止移动
 * 取消移动动画的定时器
 */
void GridMoveComponent::_stopMove()
{
	if(m_moveState==MoveStart){
		m_moveState=MoveWillStop;
	}else {
		CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->unscheduleSelector(m_update, this);
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		doMoveStop();
	}
}
void GridMoveComponent::_prepareMove()
{
	calcMoveDuration(m_directionX,m_directionY);
	calcSpeedVector(m_directionX,m_directionY);
//	((WorldEntity*) m_owner)->setCoordinate(m_to);
}

void GridMoveComponent::_continueUpdate()
{
	if(checkMoveable()){
		m_moveState=MoveStart;
		m_movingDeltaTime=0;
		this->_prepareMove();
		updateMoveAnimation();
	}else{
		stop();
	}
}

void GridMoveComponent::_resetState()
{
	m_directionX=0;
	m_directionY=0;
	m_lastDirectionX=0;
	m_lastDirectionY=0;
	m_nextDirectionX=0;
    m_nextDirectionY=0;
}
#pragma mark -
#pragma mark 按方向移动

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void GridMoveComponent::moveWithDirection(float directionX ,float directionY)
{
    m_update=schedule_selector(GridMoveComponent::updateDirection);

	if (m_moveState==MoveStop) {
		_resetState();
		prepareDirection(directionX, directionY);
		if(checkMoveable()){
			_prepareMove();
			_startMove();
			updateMoveAnimation();
		}
	}else {
		continueMoveWithDirection(directionX,directionY);
	}
}

void GridMoveComponent::moveWithDirection(CCPoint direction)
{
    moveWithDirection(direction.x, direction.y);
}
/**
 * 断续指定方向移动
 */
void GridMoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
	setNextDirection(directionX,directionY);
	m_moveState=MoveContinue;
}

void GridMoveComponent::continueMoveWithDirection(CCPoint direction)
{
	continueMoveWithDirection(direction.x, direction.y);
}

void GridMoveComponent::prepareDirection(float directionX,float directionY)
{
	setDirection(directionX,directionY);
	calcTo();
}

void GridMoveComponent::calcMoveDuration(float directionX,float directionY)
{
	//计算本次移动所需要的时间
	//+0.5 四舍五入的修正
	//+1.由于-1=<directionX<=1,偏移一个1，正好0<=directionX+1<=2。起点和数组下标吻合
	int i=floor(directionX+0.5)+1;
	int j=floor(directionY+0.5)+1;
	CCAssert(i>=0 && i<=2,"prepareDirection error the direction out of range");
	CCAssert(j>=0 && j<=2,"prepareDirection error the direction out of range");
	m_movingDuration=MoveDurationMap[i][j]/m_speed;

	CCLOG("m_movingDuration:%f",m_movingDuration);
	//float absDirX=abs(directionX);
	//float absDirY=abs(directionY);

	//if((absDirX<FLOAT_ZERO_FLAG&&absDirY>FLOAT_ZERO_FLAG)||(absDirX>FLOAT_ZERO_FLAG&&absDirY<FLOAT_ZERO_FLAG)){
	//	m_movingDuration=AXIS_VECTOR*1000;//毫秒
	//}else{
	//	if(abs(directionX)>FLOAT_ZERO_FLAG&&abs(directionY)>FLOAT_ZERO_FLAG){
	//		m_movingDuration=BEVEL_VECTOR *1000;
	//	}else{
	//		m_movingDuration=0;
	//	}
	//}
	

}

/**
 * directionX -1,0,1
 */
void GridMoveComponent::calcSpeedVector(float directionX,float directionY)
{
	int i=floor(directionX+FLOAT_ZERO_FLAG);
	int j=floor(directionY+FLOAT_ZERO_FLAG);

	if(i==0||j==0){
		//m_speedX,m_speedY其中一个为0或都为0
		m_speedX=i*m_speed*AXIS_VECTOR;
		m_speedY=j*m_speed*AXIS_VECTOR;
	}else{
		//m_speedX,m_speedY都不为0，为speed的sqrt(2)/2
		//speed的大小不变，分量的是变化的。由于是45度地图，所以只有一种变化sqrt(2)/2
		m_speedX=i*m_speed*BEVEL_VECTOR_HALF;
		m_speedY=j*m_speed*BEVEL_VECTOR_HALF;
	}
    //TODO
	CCPoint viewSpeed=ccp(2,1);//isoGameToView2F(m_speedX,m_speedY);
	m_fViewSpeedX=viewSpeed.x;
	m_fViewSpeedY=viewSpeed.y;
	CCLOG("m_speedX:%f,m_speedY:%f,viewSpeed:%f,%f",m_speedX,m_speedY,m_fViewSpeedX,m_fViewSpeedY);
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcTo()
{
    //TODO
//	WorldEntity* owner=(WorldEntity*)m_owner;
//	float mx=owner->getX();
//	float my=owner->getY();
//	owner->setCoordinate(mx+m_directionX,my+m_directionY);
}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void GridMoveComponent::updateDirection( float delta)
{
	CCNode* owner=(CCNode*)m_owner;
	CCPoint pos=owner->getPosition();

	m_movingDeltaTime+=delta;
	if(m_movingDeltaTime<m_movingDuration){
		pos.x+=delta*m_fViewSpeedX;
		pos.y+=delta*m_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOG("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		owner->setPosition(pos);
	}else{
		//一个路径结点移动完成
		owner->setPosition(isoGameToView2F(m_to.x,m_to.y));
		if (m_moveState==MoveContinue) {
			prepareDirection(m_nextDirectionX, m_nextDirectionY);
    		this->_continueUpdate();
		}else{
			if(m_bKeepMoveDirection){
				if(checkMoveable()){
					m_movingDeltaTime=0;
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
	CCObject* pObj=NULL;
	CCARRAY_FOREACH(paths,pObj){
		CCPoint* pos=(CCPoint*)pObj;
		CCLOG("x=%f,y=%f",pos->x,pos->y);
	}

	m_update=schedule_selector(GridMoveComponent::updatePath);

	if(m_moveState==MoveStop){
		_resetState();
		m_iFromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (checkMoveable()) {
			_prepareMove();
			_startMove();
			updateMoveAnimation();
		}
	}else{
		m_iFromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}
}
/**
 * 继续指定路径移动
 */
void GridMoveComponent::continueMoveWithPaths(CCArray* paths)
{
	this->setNextPaths(paths);	
	m_moveState=MoveContinue;
}

void GridMoveComponent::restartMove()
{
	m_moveState=MoveStart;
	preparePath();
}

int GridMoveComponent::getFirstPathIndex(){
	int iPathIndex=m_pCurrentPaths->count()-1 -m_iFromIndex;
	return iPathIndex;
}

/**
 * 准备移动路径
 */
void  GridMoveComponent::preparePath()
{
	m_iPathIndex=getFirstPathIndex();
	preparePath(m_iPathIndex);
}

/**
 * 准备移动路径
 */
void  GridMoveComponent::preparePath(int iPathIndex)
{
	CCAssert(m_iPathIndex>=0,"paths length less 2");
	CCLOG("preparePath.iPathIndex:%d",iPathIndex);
	m_to=*(CCPoint*)m_pCurrentPaths->objectAtIndex(iPathIndex);
	calcDirection();
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcDirection()
{
    //TODO
//	WorldEntity* owner=(WorldEntity*)m_owner;
//	float mx=owner->getX();
//	float my=owner->getY();
//	setDirection(m_to.x>mx?1:m_to.x<mx?-1:0,m_to.y>my?1:m_to.y<my?-1:0);
}



/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void GridMoveComponent::updatePath(float delta)
{
    CCNode* owner=(CCNode*)m_owner;
    
	CCPoint pos=owner->getPosition();
	
	m_movingDeltaTime+=delta;
	
	//CCLOG("upate:%f,%f,%f",delta,m_movingDeltaTime,m_movingDuration);
	if(m_movingDeltaTime<m_movingDuration){
		//CCLOG("posx1:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		pos.x+=delta*m_fViewSpeedX;
		pos.y+=delta*m_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOG("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		owner->setPosition(pos);
	}else{
		//一个路径结点移动完成
		owner->setPosition(isoGameToView2F(m_to.x,m_to.y));
		if (m_moveState==MoveContinue) {
			if (m_pNextPaths!=NULL) {
				m_moveState=MoveStart;
				this->setCurrentPaths(m_pNextPaths);
				preparePath();
				this->_continueUpdate();
			}
		}else if (--m_iPathIndex>=0 && m_moveState==MoveStart) {
			CCLOG("next cell %d",m_iPathIndex);
			//进行下一个格子
			preparePath(m_iPathIndex);
			this->_continueUpdate();
		}else {
			//stop move
			this->setCurrentPaths(NULL);
			stop();
		}
	}
}


/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void GridMoveComponent::updateMoveAnimation()
{
	if (m_moveState!=MoveStop && m_lastDirectionX==m_directionX && m_lastDirectionY==m_directionY) {
		return;
	}
	//+0.5四舍五入
	int i=floor(m_directionX+0.5)+1;
	int j=floor(m_directionY+0.5)+1;
	int index=directionMapping[i][j];
	CCLOG("index:%d,%d,%d,%f,%f",index,i,j,m_directionX,m_directionY);
	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), "name");
		data->setObject(CCInteger::create(index), "direction");
    
		MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
	}
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void GridMoveComponent::doMoveStart()
{
    //todo parse direction
    //updateMoveAnimation();
   
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void GridMoveComponent::doMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);

}
//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。、
void GridMoveComponent::doHit(CCPoint location)
{
	
}

void GridMoveComponent::onMoveDirection(Message *message)
{
    CCPoint direction=static_cast<CCPointValue*>(message->getData())->getPoint();
    moveWithDirection(direction);
}

void GridMoveComponent::onMoveDirectionStop(Message *message)
{
    stop();
}

void GridMoveComponent::onMoveTo(Message *message)
{
    CCPoint to=static_cast<CCPointValue*>(message->getData())->getPoint();
//    moveTo(to);
}

void GridMoveComponent::onMovePath(Message *message)
{
    CCArray* paths=(CCArray*)message->getData();
    moveWithPaths(paths);
}

float GridMoveComponent::getSpeed()
{
    return m_speed;
}

void GridMoveComponent::setSpeed(float speed)
{
    m_speed=speed;
}

void GridMoveComponent::setDirection(float directionX,float directionY)
{
	m_lastDirectionX=m_directionX;
	m_lastDirectionY=m_directionY;
	m_directionX=directionX;
	m_directionY=directionY;

}

void GridMoveComponent::setDirection(CCPoint direction)
{
	m_lastDirectionX=m_directionX;
	m_lastDirectionY=m_directionY;

	m_directionX=direction.x;
	m_directionY=direction.y;
}

CCPoint GridMoveComponent::getDirection()
{
    return ccp(m_directionX,m_directionY);
}

void GridMoveComponent::setDirectionX(float directionX)
{
	m_lastDirectionX=m_directionX;
    m_directionX = directionX;
}

float GridMoveComponent::getDirectionX()
{
    return m_directionX;
}

void GridMoveComponent::setDirectionY(float directionY)
{
	m_lastDirectionY=m_directionY;
    m_directionY = directionY;
}

float GridMoveComponent::getDirectionY()
{
    return m_directionY;
}

void GridMoveComponent::setNextDirection(float directionX,float directionY)
{
	m_nextDirectionX=directionX;
	m_nextDirectionY=directionY;
}
CCPoint GridMoveComponent::getNextDirection()
{
	return ccp(m_nextDirectionX,m_nextDirectionY);
}

void GridMoveComponent::setNextDirectionX(int nextDirectionX)
{
    m_nextDirectionX = nextDirectionX;
}

int GridMoveComponent::getNextDirectionX()
{
    return m_nextDirectionX;
}

void GridMoveComponent::setNextDirectionY(float nextDirectionY)
{
    m_nextDirectionY = nextDirectionY;
}

float GridMoveComponent::getNextDirectionY()
{
    return m_nextDirectionY;
}

void GridMoveComponent::setKeepMoveDirection(bool bKeepMoveDirection)
{
    m_bKeepMoveDirection = bKeepMoveDirection;
}

bool GridMoveComponent::isKeepMoveDirection()
{
    return m_bKeepMoveDirection;
}

CCPoint GridMoveComponent::getTo()
{
    return m_to;
}

void GridMoveComponent::setTo(CCPoint to)
{
    m_to=to;
}

void GridMoveComponent::setCurrentPaths(CCArray* pCurrentPaths)
{
    CC_SAFE_RETAIN(pCurrentPaths);
    CC_SAFE_RELEASE(m_pCurrentPaths);
    m_pCurrentPaths = pCurrentPaths;
}

CCArray* GridMoveComponent::getCurrentPaths()
{
    return m_pCurrentPaths;
}

void GridMoveComponent::setNextPaths(CCArray* pNextPaths)
{
    CC_SAFE_RETAIN(pNextPaths);
    CC_SAFE_RELEASE(m_pNextPaths);
    m_pNextPaths = pNextPaths;
}

CCArray* GridMoveComponent::getNextPaths()
{
    return m_pNextPaths;
}



NS_CC_YHGE_END
