#include "SimpleMoveComponent.h"
#include <yhge/Message/MessageManager.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

SimpleMoveComponent::SimpleMoveComponent()
:m_speed(0.0f)
,m_direction(0.0f)
,m_directionX(0)
,m_directionY(0)
,m_moving(false)
,m_to(ccp(0.0f, 0.0f))
,m_hasEndPosition(false)
,m_isDirectionDirty(true)
{
    CCLOG("SimpleMoveComponent create");
}

SimpleMoveComponent::~SimpleMoveComponent()
{
    CCLOG("SimpleMoveComponent destroy");
}

bool SimpleMoveComponent::init()
{
	if(Component::init()){
		m_moveState=MoveStop;      
	}
    return true;
	
}

bool SimpleMoveComponent::init(float speed)
{
	if (init()) {
		m_speed=speed;
	}
	return true;
}

float SimpleMoveComponent::getSpeed()
{
    return m_speed;
}

void SimpleMoveComponent::setSpeed(float speed)
{
    m_speed=speed;
}

void SimpleMoveComponent::setDirection(float direction)
{
    m_direction=direction;
    m_isDirectionDirty=false;
}

float SimpleMoveComponent::getDirection()
{
    return m_direction;
}

CCPoint SimpleMoveComponent::getTo()
{
    return m_to;
}

void SimpleMoveComponent::setTo(CCPoint to)
{
    m_to=to;
}

bool SimpleMoveComponent::isMoving()
{
    return m_moving;
}

MoveState SimpleMoveComponent::getMoveState()
{
    return m_moveState;
}

CCPoint SimpleMoveComponent::movingCoordinate()
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

bool SimpleMoveComponent::beforeMove()
{
	return true;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void SimpleMoveComponent::startMove()
{
    CCLOG("startMove");
	m_moveState=MoveStart;
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->scheduleSelector(m_update,this, 0, false);
    didMoveStart();
}

/**
 * 停止移动
 * 取消移动动画的定时器
 */
void SimpleMoveComponent::stopMove()
{
//	if(m_moveState==MoveStart){
//		m_moveState=MoveWillStop;
//	}else {
		CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->unscheduleSelector(m_update, this);
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		didMoveStop();
//	}
}

void SimpleMoveComponent::moveWithDirection(float direction)
{
    moveWithDirection(direction,false);
}

void SimpleMoveComponent::moveWithDirection(float direction,bool hasTo)
{
    CCLOG("moveWithDirection:%f",direction);
    
    m_update=schedule_selector(SimpleMoveComponent::updateDirection);
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
void SimpleMoveComponent::moveWithDirection(float directionX ,float directionY)
{
    moveWithDirection(directionX, directionY, false);
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void SimpleMoveComponent::moveWithDirection(float directionX ,float directionY,bool hasTo)
{
    m_update=schedule_selector(SimpleMoveComponent::updateDirection);
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
void SimpleMoveComponent::continueMoveWithDirection(float direction)
{
	setDirection(direction);
    calcSpeedVector(cosf(direction), sinf(direction));
	m_moveState=MoveContinue;
}


/**
 * 断续指定方向移动
 */
void SimpleMoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
	calcSpeedVector(directionX, directionY);
    m_moveState=MoveContinue;
}

void SimpleMoveComponent::moveTo(CCPoint to)
{
    
    CCPoint pos=((CCNode*)m_pOwner)->getPosition();
    
    float dx=to.x-pos.x;
    float dy=to.y-pos.y;
    
    CCLOG("moveTo:%f,%f, diff:%f,%f",to.x,to.y,dx,dy);
    
    if(dx>0 || dy>0){
        float s=sqrtf(dx*dx+dy*dy);
        
        float directionX=dx/s;
        float directionY=dy/s;
        
        m_directionFlagX=dx>0?1:dx<0?-1:0;
        m_directionFlagY=dy>0?1:dy<0?-1:0;
        
        setTo(to);
        moveWithDirection(directionX, directionY,true);
    }
    
}

///**
// * 按指定路径移动
// */
//void moveWithPaths:(NSArray *) paths
//{
//	[self moveWithPaths:paths fromIndex:0];
//}
//
//void moveWithPaths:(NSArray *)paths fromIndex:(int) fromIndex
//{
//	updateStep_=@selector(updatePath:);
//	if (m_moveState==MoveStart) {
//		fromIndex_=fromIndex;
//		[self continueMoveWithPaths:paths];
//	}else if(m_moveState==MoveStop){
//		fromIndex_=fromIndex;
//		self.currentPaths=paths;
//		[self preparePath];
//		if ([self beforeMovePath]) {
//			[self startMove];
//		}
//	}
//}
///**
// * 继续指定路径移动
// */
//void continueMoveWithPaths:(NSArray *) paths
//{
//	self.nextPaths=paths;	
//	m_moveState=MoveContinue;
//}
//
//
//
//
//
///**
// * 路径移动之前进行检查
// */
//bool beforeMovePath
//{
//	if([self beforeMove]){
//		[self calcDirection];
//		//update move action
//		[self updateMoveAnimation];
//		return YES;
//	}
//	return NO;
//}





//void restartMove
//{
//	m_moveState=MoveStart;
//	[self preparePath];
//	[self beforeMovePath];
//}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void SimpleMoveComponent::updateDirection( float delta)
{
    CCNode* owner=(CCNode*)m_pOwner;
    
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
//		
//		if (m_moveState==MoveContinue) {
//
//            m_moveState=MoveStart;
//            m_direction=m_nextDirection;
//            m_speedX=m_speed*cosf(m_direction);
//            m_speedY=m_speed*sinf(m_direction);
//            if(beforeMove()){
//                
//            }
//
//		}else {
//			//stop move
//			m_moveState=MoveWillStop;//标记将要结束
			stopMove();
//		}
	}
	owner->setPosition(pos);
}
///**
// * 移动动画步骤
// * 通过路径移动的动画步骤
// */
//void SimpleMoveComponent::updatePath(float delta)
//{
//    GameEntity* owner=(GameEntity*)m_owner;
//    
//    CCPoint pos=owner->getPosition();
//	//根据速度计算移动距离
//    float s=delta*10;
//	pos.x+=s*m_speedX;
//	pos.y+=s*m_speedY;
//
//	
//	//判断是否结束	
//	if (fabs(pos.x-m_to.x)<0.00001 &&  fabs(pos.y-m_to.y)<0.00001) {
//		pos.x=m_to.x;
//		pos.y=m_to.y;
//
//		if (m_moveState==MoveContinue) {
//			if (m_nextPaths!=NULL) {
//				m_moveState=MoveStart;
//				self.currentPaths=m_nextPaths;
//				[self preparePath];
//				[self beforeMovePath];
//			}
//		}else if (--m_spathIndex>=0 && m_moveState==MoveStart) {
//			//进行下一个格子
//			m_to=[[m_currentPaths objectAtIndex:m_spathIndex] CGPointValue];
//			[self beforeMovePath];
//		}else {
//			//stop move
//			self.currentPaths=NULL;
//			m_moveState=MoveWillStop;//标记将要结束
//			[self stopMove];
//		}
//	}
//	[owner_ setCoordinate:mx y:my];
//}

///**
// * 准备移动路径
// */
//void  preparePath
//{
//	m_spathIndex=[m_currentPaths	count]-2-fromIndex_;
//	if (m_spathIndex<0) {
//		NSAssert(m_spathIndex<0,@"paths length less 2");
//	}
//	
//	m_to=[[m_currentPaths objectAtIndex:m_spathIndex] CGPointValue];
//}
//
///**
// * 计算方向
// * 主要用于按路径移动时
// */
//void calcDirection
//{
//	lastDirection_=m_direction;
//	float mx=owner_.mx,my=owner_.my;
//	m_direction.x=m_to.x>mx?1:m_to.x<mx?-1:0;
//	m_direction.y=m_to.y>my?1:m_to.y<my?-1:0;
//}
//
///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(float) dirX dirY:(float)dirY
//{
//	lastDirection_=m_direction;
//	
//	m_direction.x=dirX;
//	m_direction.y=dirY;
//	
//	m_to.x=owner_.mx+dirX;
//	m_to.y=owner_.my+dirY;
//}
//
///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(CGPoint) dir
//{
//	lastDirection_=m_direction;
//	
//	m_direction=dir;
//	
//	m_to.x=owner_.mx+dir.x;
//	m_to.y=owner_.my+dir.y;
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
///**
// * 方向改变
// * 人物在移动时要面向不同的方向
// */
//void updateMoveAnimation
//{
//	
//}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void SimpleMoveComponent::didMoveStart()
{
    //todo parse direction
    
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("move"), "name");
    data->setObject(CCInteger::create(3), "direction");
    
    //MessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_owner,data);
    
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void SimpleMoveComponent::didMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    //MessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_owner,data);

}
//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。、
void SimpleMoveComponent::didHit(CCPoint location)
{
	
}

NS_CC_YHGE_END
