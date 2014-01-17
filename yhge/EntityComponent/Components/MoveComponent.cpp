/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "MoveComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCGeometryValue.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

static int directionMapping[3][3]={
	{4,1,5},
	{0,-1,2},
	{7,3,6}
};

MoveComponent::MoveComponent()
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
{
    CCLOG("MoveComponent create");
	m_name="MoveComponent";
}

MoveComponent::~MoveComponent()
{
    CCLOG("MoveComponent destroy");
	CC_SAFE_RELEASE(m_pCurrentPaths);
	CC_SAFE_RELEASE(m_pNextPaths);
}

bool MoveComponent::init()
{
	if(Component::init()){
		m_moveState=MoveStop;      
	}
    return true;
	
}

bool MoveComponent::init(float speed)
{
	if (init()) {
		m_speed=speed;
	}
	return true;
}

bool MoveComponent::registerMessages()
{
    CCLOG("MoveComponent::registerMessages");
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION, NULL, message_selector(MoveComponent::onMoveDirection),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION_STOP, NULL, message_selector(MoveComponent::onMoveDirectionStop),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_TO, NULL, message_selector(MoveComponent::onMoveTo),this);
        
        return true;
    }
    
    return false;

}

void MoveComponent::cleanupMessages()
{
	CCLOG("MoveComponent::cleanupMessages");
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_DIRECTION);
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_DIRECTION_STOP);
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_TO);
    
    Component::cleanupMessages();
}

bool MoveComponent::isMoving()
{
    return m_moving;
}

MoveState MoveComponent::getMoveState()
{
    return m_moveState;
}

CCPoint MoveComponent::movingCoordinate()
{
	CCPoint coord;
//	if (m_moveState==MoveStart) {
//		coord=m_to;
//	}else {
//		coord.x=m_owner.mx;
//		coord.y=m_owner.my;
//	}
	return coord;
}



/**
 * 移动之前进行检查
 */

bool MoveComponent::beforeMove()
{
	return true;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void MoveComponent::startMove()
{
    CCLOG("startMove");
	m_moveState=MoveStart;
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->scheduleSelector(m_update,this, 0, false);
    doMoveStart();
}

/**
 * 停止移动
 * 取消移动动画的定时器
 */
void MoveComponent::stopMove()
{
//	if(m_moveState==MoveStart){
//		m_moveState=MoveWillStop;
//	}else {
		CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->unscheduleSelector(m_update, this);
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		doMoveStop();
//	}
}

void MoveComponent::moveTo(CCPoint to)
{
    
    CCPoint pos=((CCNode*)m_owner)->getPosition();
    
    float dx=to.x-pos.x;
    float dy=to.y-pos.y;
    
    CCLOG("moveTo:%f,%f, diff:%f,%f",to.x,to.y,dx,dy);
    
    if(dx!=0 || dy!=0){
        float s=sqrtf(dx*dx+dy*dy);
        
        float directionX=dx/s;
        float directionY=dy/s;
        
        m_directionFlagX=dx>0?1:dx<0?-1:0;
        m_directionFlagY=dy>0?1:dy<0?-1:0;
        
        setTo(to);
        moveWithDirection(directionX, directionY,true);
    }
    
}

#pragma mark -
#pragma mark 按方向移动

void MoveComponent::moveWithDirection(float direction)
{
    moveWithDirection(direction,false);
}

void MoveComponent::moveWithDirection(float direction,bool hasTo)
{
    CCLOG("moveWithDirection:%f",direction);
    
    m_update=schedule_selector(MoveComponent::updateDirection);
    m_hasEndPosition=hasTo;
    
    if (m_moveState==MoveStart) {
		continueMoveWithDirection(direction);
	}else {
        setDirection(direction);
        calcSpeedVector(cosf(direction), sinf(direction));
        
        if(beforeMove()){
            startMove();
        }
	}
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void MoveComponent::moveWithDirection(float directionX ,float directionY)
{
    moveWithDirection(directionX, directionY, false);
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void MoveComponent::moveWithDirection(float directionX ,float directionY,bool hasTo)
{
    m_update=schedule_selector(MoveComponent::updateDirection);
    m_hasEndPosition=hasTo;
    
    m_isDirectionDirty=true;
    
    m_directionX=directionX;
    m_directionY=directionY;
    
	calcSpeedVector(directionX, directionY);
    
    if(beforeMove()){
        startMove();
    }
}
/**
 * 断续指定方向移动
 */
void MoveComponent::continueMoveWithDirection(float direction)
{
	setDirection(direction);
    calcSpeedVector(cosf(direction), sinf(direction));
	m_moveState=MoveContinue;
}


/**
 * 断续指定方向移动
 */
void MoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
	calcSpeedVector(directionX, directionY);
    m_moveState=MoveContinue;
}



/**
 * 按指定路径移动
 */
void MoveComponent::moveWithPaths(CCArray* paths)
{
	moveWithPaths(paths ,0);
}

void MoveComponent::moveWithPaths(CCArray* paths,int fromIndex)
{
	m_update=schedule_selector(MoveComponent::updatePath);

	if (m_moveState==MoveStart) {
		m_fromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}else if(m_moveState==MoveStop){
		m_fromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (beforeMovePath()) {
			startMove();
		}
	}
}
/**
 * 继续指定路径移动
 */
void MoveComponent::continueMoveWithPaths(CCArray* paths)
{
	this->setNextPaths(paths);	
	m_moveState=MoveContinue;
}

/**
 * 路径移动之前进行检查
 */
bool MoveComponent::beforeMovePath()
{
	if(beforeMove()){
		calcDirection();
		return true;
	}
	return false;
}

void MoveComponent::restartMove()
{
	m_moveState=MoveStart;
	preparePath();
	beforeMovePath();
}

/**
 * 准备移动路径
 */
void  MoveComponent::preparePath()
{
	m_pathIndex=m_pCurrentPaths->count()-2-m_fromIndex;
	if (m_pathIndex<0) {
		CCAssert(m_pathIndex<0,"paths length less 2");
	}
	
	m_to=*(CCPoint*)m_pCurrentPaths->objectAtIndex(m_pathIndex);

}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void MoveComponent::calcDirection()
{
	CCNode* owner=(CCNode*)m_owner;
	CCPoint pos=owner->getPosition();
	m_directionX=m_to.x>pos.x?1:m_to.x<pos.y?-1:0;
	m_directionY=m_to.y>pos.y?1:m_to.y<pos.y?-1:0;
}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void MoveComponent::updateDirection( float delta)
{
    CCNode* owner=(CCNode*)m_owner;
    
    CCPoint pos=owner->getPosition();
	//根据速度计算移动距离
    float s=delta*10;
	pos.x+=s*m_speedX;
	pos.y+=s*m_speedY;
    
//    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束	
	if (m_hasEndPosition && (m_directionFlagX * pos.x>m_directionFlagX*m_to.x  || fabs(pos.x-m_to.x)<0.00001) &&  (m_directionFlagY*pos.y> m_directionFlagY* m_to.y|| fabs(pos.y-m_to.y)<0.00001)) {
		pos.x=m_to.x;
		pos.y=m_to.y;
		stopMove();

	}
	owner->setPosition(pos);
}

/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void MoveComponent::updatePath(float delta)
{
    CCNode* owner=(CCNode*)m_owner;
    
    CCPoint pos=owner->getPosition();
	//根据速度计算移动距离
    float s=delta*10;
	pos.x+=s*m_speedX;
	pos.y+=s*m_speedY;
    
//    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束	
	if (m_hasEndPosition && (m_directionFlagX * pos.x>m_directionFlagX*m_to.x  || fabs(pos.x-m_to.x)<0.00001) &&  (m_directionFlagY*pos.y> m_directionFlagY* m_to.y|| fabs(pos.y-m_to.y)<0.00001)) {
		pos.x=m_to.x;
		pos.y=m_to.y;

		if (m_moveState==MoveContinue) {
			if (m_pNextPaths!=NULL) {
				m_moveState=MoveStart;
				this->setCurrentPaths(m_pNextPaths);
				preparePath();
				beforeMovePath();
			}
		}else if (--m_pathIndex>=0 && m_moveState==MoveStart) {
			//进行下一个格子
			m_to=*(CCPoint*)m_pCurrentPaths->objectAtIndex(m_pathIndex);
			beforeMovePath();
		}else {
			//stop move
			this->setCurrentPaths(NULL);
			m_moveState=MoveWillStop;//标记将要结束
			stopMove();
		}
	}
	owner->setPosition(pos);
}



///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(float) dirX dirY:(float)dirY
//{
//	m_lastDirection=m_direction;
//	
//	m_direction.x=dirX;
//	m_direction.y=dirY;
//	
//	m_to.x=m_owner.mx+dirX;
//	m_to.y=m_owner.my+dirY;
//}
//
///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(CGPoint) dir
//{
//	m_lastDirection=m_direction;
//	
//	m_direction=dir;
//	
//	m_to.x=m_owner.mx+dir.x;
//	m_to.y=m_owner.my+dir.y;
//}
//
//void clearMapData
//{
//	MapData *mapData=[MapData sharedMapData];
//	int x,y;
//	if (m_moveState!=MoveStop) {
//		x=(int)m_to.x;
//		y=(int)m_to.y;
//	}else {
//		x=(int)mx;
//		y=(int)my;
//	}
//	
//	for ( int i=0; i<l_; i++) {
//		for (int j=0; j<b_; j++) {
//			[mapData removeMapInfoWithX:x+j y:y+i entity:self];
//		}
//	}
//}
/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void MoveComponent::updateMoveAnimation()
{
	//+0.5四舍五入
	int i=floor(m_directionX+0.5)+1;
	int j=floor(m_directionY+0.5)+1;
	int index=directionMapping[i][j];
	CCLOG("index:%d,%d,%d,%f,%f",index,i,j,m_directionX,m_directionY);
	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), "name");
		data->setObject(CCInteger::create(index), "direction");
    
		this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, m_owner,data);
	}
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void MoveComponent::doMoveStart()
{
    //todo parse direction
    updateMoveAnimation();
   
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void MoveComponent::doMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);

}
//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。、
void MoveComponent::doHit(CCPoint location)
{
	
}

void MoveComponent::onMoveDirection(Message *message)
{
    CCInteger* integer=(CCInteger*)message->getData();
    moveWithDirection(kmDegreesToRadians(integer->getValue()));
}

void MoveComponent::onMoveDirectionStop(Message *message)
{
    stopMove();
}

void MoveComponent::onMoveTo(Message *message)
{
    CCPoint to=static_cast<CCPointValue*>(message->getData())->getPoint();
    moveTo(to);
}

NS_CC_YHGE_END
