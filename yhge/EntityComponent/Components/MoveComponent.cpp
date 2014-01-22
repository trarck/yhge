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

static int kDirectionMapping[8]={
    4,1,5,
    0,  2,
    7,3,6
};

MoveComponent::MoveComponent()
:Component("MoveComponent")
,m_moveState(MoveIdle)
,m_moveType(kMoveNone)
,m_speed(0.0f)
,m_speedX(0.0f)
,m_speedY(0.0f)
,m_direction(0.0f)
,m_directionX(0)
,m_directionY(0)
,m_directionFlagX(0)
,m_directionFlagY(0)
,m_to(CCPointZero)
,m_moving(false)
,m_fromIndex(0)
,m_hasEndPosition(false)
,m_pCurrentPaths(NULL)
,m_pNextPaths(NULL)
,m_pathIndex(0)
,m_update(NULL)
{

}

MoveComponent::~MoveComponent()
{
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

void MoveComponent::setup()
{
    Component::setup();
    m_isoPositionComponent=static_cast<ISOPositionComponent*>(m_owner->getComponent("ISOPositionComponent"));
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void MoveComponent::cleanup()
{
    m_isoPositionComponent=NULL;
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool MoveComponent::registerMessages()
{
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(m_owner, MSG_MOVE_DIRECTION, NULL, message_selector(MoveComponent::onMoveDirection),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_STOP, NULL, message_selector(MoveComponent::onMoveStop),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_TO, NULL, message_selector(MoveComponent::onMoveTo),this);
        
        return true;
    }
    
    return false;

}

void MoveComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_DIRECTION);
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_DIRECTION_STOP);
    this->getMessageManager()->removeReceiver(m_owner, MSG_MOVE_TO);
    
    Component::cleanupMessages();
}

/**
 * 移动之前进行检查
 */

bool MoveComponent::checkMoveable()
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
    startMoveUpdateSchedule();
    doMoveStart();
}

/**
 * 停止移动
 * 由于不是按格子移动，可以立即停止移动
 */
void MoveComponent::stopMove()
{
    stopMoveUpdateSchedule();
    m_moveState=MoveStop;
    doMoveStop();
}

void MoveComponent::moveTo(const CCPoint& to)
{
    if (m_moveState==MoveStop) {
        
        m_moveType=kMoveTo;
        
        CCPoint from=m_rendererComponent->getRenderer()->getPosition();
        if(prepareTo(to, from)){
            if(checkMoveable()){
                prepareMove();
                startMove();
            }
        }
    }else{
        continueMoveTo(to);
    }
}

void MoveComponent::continueMoveTo(const CCPoint& to)
{
    CCAssert(m_moveType==kMoveTo, "MoveComponent::continueMoveTo before move type is not the same");
    
    CCPoint from=m_rendererComponent->getRenderer()->getPosition();
    
    if(prepareTo(to, from)){
        if (checkMoveable()) {
            prepareMove();
        }else{
            stopMove();
        }
    }else{
        stopMove();
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
    
    if (m_moveState==MoveStop) {
        
        m_moveType=kMoveDirection;
        
        prepareDirection(direction);

        if(checkMoveable()){
            prepareMove();
            startMove();
        }
	}else {
        continueMoveWithDirection(direction);
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
    if (m_moveState==MoveStop) {
        
        m_moveType=kMoveDirection;
        
        prepareDirection(directionX,directionY);
        
        if(checkMoveable()){
            prepareMove();
            startMove();
        }
	}else {
        continueMoveWithDirection(directionX,directionY);
	}
}
/**
 * 断续指定方向移动
 */
void MoveComponent::continueMoveWithDirection(float direction)
{
    CCAssert(m_moveType==kMoveDirection, "MoveComponent::continueMoveWithDirection before move type is not the same");
	prepareDirection(direction);
    if (checkMoveable()) {
        prepareMove();
    }else{
        stopMove();
    }
}

/**
 * 断续指定方向移动
 */
void MoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
    CCAssert(m_moveType==kMoveDirection, "MoveComponent::continueMoveWithDirection before move type is not the same");
	prepareDirection(directionX,directionY);
    if (checkMoveable()) {
        prepareMove();
    }else{
        stopMove();
    }
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
	if (m_moveState==MoveStop) {
        
        m_moveType=kMovePath;
        
		m_fromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (checkMoveable()) {
            prepareMove();
			startMove();
		}
	}else{
		m_fromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}
}
/**
 * 继续指定路径移动
 */
void MoveComponent::continueMoveWithPaths(CCArray* paths)
{
    CCAssert(m_moveType==kMovePath, "MoveComponent::continueMoveWithPaths before move type is not the same");
	this->setNextPaths(paths);
    preparePath();
    if (checkMoveable()) {
        prepareMove();
    }else{
        stopMove();
    }
//	m_moveState=MoveContinue;
}

/**
 * 路径移动之前进行检查
 */
bool MoveComponent::beforeMovePath()
{
	if(checkMoveable()){
		calcDirection();
		return true;
	}
	return false;
}

void MoveComponent::restartMoveWithPaths()
{
	m_moveState=MoveStart;
	preparePath();
	beforeMovePath();
}

/**
 * 取得当前路径结点索引
 */
int MoveComponent::getCurrentPathIndex(){
	return m_pCurrentPaths->count()-2-m_fromIndex;
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void MoveComponent::calcDirection()
{
	CCPoint pos=m_rendererComponent->getRenderer()->getPosition();
	m_directionX=m_to.x>pos.x?1:m_to.x<pos.y?-1:0;
	m_directionY=m_to.y>pos.y?1:m_to.y<pos.y?-1:0;
}

/**
 * 计算速度分量
 */
void MoveComponent::calcSpeedVector(){
    m_speedX=m_speed*m_directionX;
    m_speedY=m_speed*m_directionY;
}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void MoveComponent::updateTo( float delta)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
	//根据速度计算移动距离
	pos.x+=delta*m_speedX;
	pos.y+=delta*m_speedY;
    
    //    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束
	if ((m_directionFlagX * pos.x>m_directionFlagX*m_to.x  || fabs(pos.x-m_to.x)<0.00001) &&  (m_directionFlagY*pos.y> m_directionFlagY* m_to.y|| fabs(pos.y-m_to.y)<0.00001)) {
		pos.x=m_to.x;
		pos.y=m_to.y;
		stopMove();
	}
    
	renderer->setPosition(pos);
}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void MoveComponent::updateDirection( float delta)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
    
	//根据速度计算移动距离
	pos.x+=delta*m_speedX;
	pos.y+=delta*m_speedY;
    
    renderer->setPosition(pos);
    
    //由于没有目标点，必须手动停止。或遇障碍物会停止。

}

/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void MoveComponent::updatePath(float delta)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
	//根据速度计算移动距离
	pos.x+=delta*m_speedX;
	pos.y+=delta*m_speedY;
    
//    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束	
	if ((m_directionFlagX * pos.x>m_directionFlagX*m_to.x  || fabs(pos.x-m_to.x)<0.00001) &&  (m_directionFlagY*pos.y> m_directionFlagY* m_to.y|| fabs(pos.y-m_to.y)<0.00001)) {
		pos.x=m_to.x;
		pos.y=m_to.y;

        if (--m_pathIndex>=0 && m_moveState==MoveStart) {
			//进行下一个格子
            preparePath(m_pathIndex);
            if (checkMoveable()) {
                prepareMove();
            }else{
                stopMove();
            }
		}else {
			//stop move
			this->setCurrentPaths(NULL);
			stopMove();
		}
	}
    
	renderer->setPosition(pos);
}

/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void MoveComponent::doDirectionChange()
{
	//根据方向来确定8方向。
    //一种方法是根据角度值来确定8方向
    //一种是直接根据公式来映射
	int index=kDirectionMapping[this->hadap(m_direction)];

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
    doDirectionChange();
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
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。
void MoveComponent::doHit(CCPoint location)
{
	
}

void MoveComponent::onMoveDirection(Message *message)
{
    CCInteger* integer=(CCInteger*)message->getData();
    moveWithDirection(kmDegreesToRadians(integer->getValue()));
}

void MoveComponent::onMoveWithPath(Message *message)
{
    CCDictionary* data=message->getDictionary();
    
    CCArray* paths=(CCArray*)data->objectForKey("paths");
    CCInteger* fromIndex=static_cast<CCInteger*>(data->objectForKey("fromIndex"));
    moveWithPaths(paths,fromIndex->getValue());
}

void MoveComponent::onMoveTo(Message *message)
{
    CCPoint to=static_cast<CCPointValue*>(message->getData())->getPoint();
    moveTo(to);
}

void MoveComponent::onMoveStop(Message *message)
{
    stopMove();
}

/**
 * 准备移动到的数据
 */
bool MoveComponent::prepareTo(const CCPoint& to,const CCPoint& from)
{
    
    float dx=to.x-from.x;
    float dy=to.y-from.y;
    
    if(dx!=0 || dy!=0){
        setTo(to);
        float s=sqrtf(dx*dx+dy*dy);
        prepareDirection(dx/s, dy/s);
        return true;
    }
    
    return false;
}

/**
 * 准备方向移动的数据
 */
void MoveComponent::prepareDirection(float direction)
{
    m_directionX=cosf(direction);
    m_directionY=sinf(direction);
    m_direction=direction;
    m_directionFlagX=m_directionX>0?1:m_directionX<0?-1:0;
    m_directionFlagY=m_directionX>0?1:m_directionX<0?-1:0;
}

/**
 * 准备方向移动的数据
 */
void MoveComponent::prepareDirection(float directionX,float directionY)
{
    m_directionX=directionX;
    m_directionY=directionY;
    m_direction=atan2f(directionY, directionX);
    m_directionFlagX=m_directionX>0?1:m_directionX<0?-1:0;
    m_directionFlagY=m_directionX>0?1:m_directionX<0?-1:0;
}

/**
 * 准备移动路径
 */
void MoveComponent::preparePath()
{
	m_pathIndex=getCurrentPathIndex();
	preparePath(m_pathIndex);
}

void MoveComponent::preparePath(int pathIndex)
{
    CCAssert(pathIndex>=0,"paths length less 2");
	CCLOG("preparePath.PathIndex:%d",pathIndex);
    CCPoint to= static_cast<CCPointValue*>(m_pCurrentPaths->objectAtIndex(pathIndex))->getPoint();
    CCPoint from=m_rendererComponent->getRenderer()->getPosition();
    prepareTo(to, from);
}

/**
 * 移动之前的准备
 */
void MoveComponent::prepareMove()
{
    calcSpeedVector();
}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void MoveComponent::startMoveUpdateSchedule()
{
    switch (m_moveType)
    {
        case kMoveDirection:
            m_update=schedule_selector(MoveComponent::updateDirection);
            break;
        case kMovePath:
            m_update=schedule_selector(MoveComponent::updatePath);
            break;
        default:
            break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(m_update,this, 0, false);
}

void MoveComponent::stopMoveUpdateSchedule()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(m_update,this);
    m_update=NULL;
}

NS_CC_YHGE_END
