/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "GridMoveComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCGeometryValue.h>
#include <yhge/isometric.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

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
:m_moveState(MoveIdle)
,m_moveType(kMoveNone)
,m_speed(0.0f)
,m_speedX(0.0f)
,m_speedY(0.0f)
,m_fViewSpeedX(0.0f)
,m_fViewSpeedY(0.0f)
,m_directionX(0)
,m_directionY(0)
,m_lastDirectionX(0)
,m_lastDirectionY(0)
,m_nextDirectionX(0)
,m_nextDirectionY(0)
,m_bKeepMoveDirection(false)
,m_movingDuration(0.0f)
,m_movingDeltaTime(0.0f)
,m_to(ccp(0.0f, 0.0f))
,m_moving(false)
,m_fromIndex(0)
,m_pCurrentPaths(NULL)
,m_pNextPaths(NULL)
,m_pathIndex(0)
,m_update(NULL)
,m_isoPositionComponent(NULL)
,m_rendererComponent(NULL)
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

void GridMoveComponent::setup()
{
    Component::setup();
    m_isoPositionComponent=static_cast<ISOPositionComponent*>(m_owner->getComponent("ISOPositionComponent"));
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void GridMoveComponent::cleanup()
{
    m_isoPositionComponent=NULL;
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool GridMoveComponent::registerMessages()
{
    CCLOG("GridMoveComponent::registerMessages");
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION, NULL, message_selector(GridMoveComponent::onMoveWithDirection),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_PATH, NULL, message_selector(GridMoveComponent::onMoveWithPath),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_PATH_FROM, NULL, message_selector(GridMoveComponent::onMoveWithPathFrom),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_STOP, NULL, message_selector(GridMoveComponent::onMoveStop),this);
        
        return true;
    }
    
    return false;
}

void GridMoveComponent::cleanupMessages()
{
	CCLOG("GridMoveComponent::cleanupMessages");
    
    MessageManager* messageManager=MessageManager::defaultManager();
    
    messageManager->removeReceiver(m_owner, MSG_MOVE_DIRECTION);
    messageManager->removeReceiver(m_owner, MSG_MOVE_PATH);
    messageManager->removeReceiver(m_owner, MSG_MOVE_PATH_FROM);
    messageManager->removeReceiver(m_owner, MSG_MOVE_STOP);
    
    Component::cleanupMessages();
}

/**
 * 停止移动
 * 立即停止移动
 */
void GridMoveComponent::stop()
{
	m_moveState=MoveWillStop;
    stopMove();
}

/**
 * 移动之前进行检查
 */

bool GridMoveComponent::checkMoveable()
{
	return true;
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void GridMoveComponent::moveWithDirection(int directionX ,int directionY)
{
    //m_update=this->getUpdateDirectionHandle();

	if (m_moveState==MoveStop) {
        
        m_moveType=kMoveDirection;
        
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
    CCAssert(m_moveType==kMoveDirection, "GridMoveComponent::continueMoveWithDirection before move type is not the same");
	setNextDirection(directionX,directionY);
	m_moveState=MoveContinue;
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
 * 计算屏幕速度
 * direction -1,0,1
 */
void GridMoveComponent::calcSpeedVector(int directionX,int directionY)
{
	int i=directionX;
	int j=directionY;

    //注意m_speed是地图坐标系的速度，即做iso投影前的速度
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

	CCPoint viewSpeed=isoGameToView2F(m_speedX,m_speedY);
	m_fViewSpeedX=viewSpeed.x;
	m_fViewSpeedY=viewSpeed.y;
	CCLOG("m_speedX:%f,m_speedY:%f,viewSpeed:%f,%f",m_speedX,m_speedY,m_fViewSpeedX,m_fViewSpeedY);
}

/**
 * 计算移动到的位置
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcTo()
{
    if (m_isoPositionComponent) {
        m_to.x=m_isoPositionComponent->getX()+m_directionX;
        m_to.y=m_isoPositionComponent->getY()+m_directionY;
    }
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcDirection()
{
    CCAssert(m_isoPositionComponent!=NULL, "GridMoveComponent::calcDirection m_isoPositionComponent can't be null");
    
	float mx=m_isoPositionComponent->getX();
	float my=m_isoPositionComponent->getY();
	setDirection(m_to.x>mx?1:m_to.x<mx?-1:0,m_to.y>my?1:m_to.y<my?-1:0);
}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void GridMoveComponent::updateDirection( float delta)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
	CCPoint pos=renderer->getPosition();

	m_movingDeltaTime+=delta;
	if(m_movingDeltaTime<m_movingDuration){
		pos.x+=delta*m_fViewSpeedX;
		pos.y+=delta*m_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOG("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		renderer->setPosition(pos);
	}else{
		//一个路径结点移动完成
		renderer->setPosition(isoGameToView2F(m_to.x,m_to.y));
		if (m_moveState==MoveContinue) {
			prepareDirection(m_nextDirectionX, m_nextDirectionY);
    		this->continueUpdate();
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
	//m_update=this->getUpdatePathHandle();//schedule_selector(GridMoveComponent::updatePath);

	if(m_moveState==MoveStop){
        
        m_moveType=kMovePath;
        
		resetState();
		m_fromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (checkMoveable()) {
			prepareMove();
			startMove();
			doDirectionChange();
		}
	}else{
		m_fromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}
}
/**
 * 继续指定路径移动
 */
void GridMoveComponent::continueMoveWithPaths(CCArray* paths)
{
    CCAssert(m_moveType==kMovePath, "GridMoveComponent::continueMoveWithDirection before move type is not the same");
    
	this->setNextPaths(paths);	
	m_moveState=MoveContinue;
}

void GridMoveComponent::restartMoveWithPaths()
{
	m_moveState=MoveStart;
	preparePath();
}


/**
 * 准备移动路径
 */
void GridMoveComponent::preparePath()
{
	m_pathIndex=getCurrentPathIndex();
	preparePath(m_pathIndex);
}

/**
 * 准备移动路径
 */
void  GridMoveComponent::preparePath(int pathIndex)
{
	CCAssert(pathIndex>=0,"paths length less 2");
	CCLOG("preparePath.iPathIndex:%d",pathIndex);
    m_to=  static_cast<CCPointValue*>(m_pCurrentPaths->objectAtIndex(pathIndex))->getPoint();
	calcDirection();
}

/**
 * 取得当前路径结点索引
 */
int GridMoveComponent::getCurrentPathIndex(){
	return m_pCurrentPaths->count()-1 -m_fromIndex;
}


/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void GridMoveComponent::updatePath(float delta)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    
	CCPoint pos=renderer->getPosition();
	
	m_movingDeltaTime+=delta;
	
	//CCLOG("upate:%f,%f,%f",delta,m_movingDeltaTime,m_movingDuration);
	if(m_movingDeltaTime<m_movingDuration){
		//CCLOG("posx1:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		pos.x+=delta*m_fViewSpeedX;
		pos.y+=delta*m_fViewSpeedY;
		//owner->setCoordinate(mx,my);
		//CCLOG("posx2:%f,posy:%f:%f,%f:%f",pos.x,pos.y,m_fViewSpeedX,m_fViewSpeedY,delta);
		renderer->setPosition(pos);
	}else{
		//一个路径结点移动完成
		renderer->setPosition(isoGameToView2F(m_to.x,m_to.y));
        //设置地图坐标
		if (m_moveState==MoveContinue) {
			if (m_pNextPaths!=NULL) {
				m_moveState=MoveStart;
				this->setCurrentPaths(m_pNextPaths);
				preparePath();
				this->continueUpdate();
			}
		}else if (--m_pathIndex>=0 && m_moveState==MoveStart) {
			CCLOG("next cell %d",m_pathIndex);
			//进行下一个格子
			preparePath(m_pathIndex);
			this->continueUpdate();
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
void GridMoveComponent::doDirectionChange()
{
	if (m_moveState!=MoveStop && m_lastDirectionX==m_directionX && m_lastDirectionY==m_directionY) {
		return;
	}
	int i=floor(m_directionX)+1;
	int j=floor(m_directionY)+1;
	int index=directionMapping[i][j];
	//CCLOG("index:%d,%d,%d,%f,%f",index,i,j,m_directionX,m_directionY);
	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), "name");
		data->setObject(CCInteger::create(index), "direction");
    
		MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
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
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);

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
    
    CCArray* paths=(CCArray*)data->objectForKey("paths");
    CCInteger* fromIndex=static_cast<CCInteger*>(data->objectForKey("fromIndex"));
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
	m_lastDirectionX=m_directionX;
	m_lastDirectionY=m_directionY;
	m_directionX=directionX;
	m_directionY=directionY;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void GridMoveComponent::startMove()
{
	m_movingDeltaTime=0;
    CCLOG("startMove");
	m_moveState=MoveStart;

    startMoveUpdateSchedule();
    //CCDirector* director = CCDirector::sharedDirector();
    //CCScheduler* pScheduler = director->getScheduler();
    //pScheduler->scheduleSelector(m_update,this, 0, false);

    doMoveStart();
}

/**
 * 停止移动
 * 等待一个格子移动结束
 */
void GridMoveComponent::stopMove()
{
	if(m_moveState==MoveStart){
		m_moveState=MoveWillStop;
	}else {
        //CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
        //pScheduler->unscheduleSelector(m_update, this);
        stopMoveUpdateSchedule();
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		doMoveStop();
	}
}
void GridMoveComponent::prepareMove()
{
	calcMoveDuration(m_directionX,m_directionY);
	calcSpeedVector(m_directionX,m_directionY);
    m_isoPositionComponent->setCoordinate(m_to);
}

void GridMoveComponent::continueUpdate()
{
	if(checkMoveable()){
		m_moveState=MoveStart;
		m_movingDeltaTime=0;
		this->prepareMove();
		doDirectionChange();
	}else{
		stop();
	}
}

void GridMoveComponent::resetState()
{
	m_directionX=0;
	m_directionY=0;
	m_lastDirectionX=0;
	m_lastDirectionY=0;
	m_nextDirectionX=0;
    m_nextDirectionY=0;
}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void GridMoveComponent::startMoveUpdateSchedule()
{
    switch (m_moveType)
    {
    case kMoveDirection:
        m_update=schedule_selector(GridMoveComponent::updateDirection);
        break;
    case kMovePath:
        m_update=schedule_selector(GridMoveComponent::updatePath);
        break;
    default:
        break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(m_update,this, 0, false);
}

void GridMoveComponent::stopMoveUpdateSchedule()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(m_update,this);
    m_update=NULL;
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
