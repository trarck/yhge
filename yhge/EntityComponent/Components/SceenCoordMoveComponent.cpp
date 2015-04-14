/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "SceenCoordMoveComponent.h"
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

SceenCoordMoveComponent::SceenCoordMoveComponent()
:Component("SceenCoordMoveComponent")
,_moveState(MoveIdle)
,_moveType(kMoveNone)
,_speed(0.0f)
,_speedX(0.0f)
,_speedY(0.0f)
,_direction(0.0f)
,_directionX(0)
,_directionY(0)
,_directionFlagX(0)
,_directionFlagY(0)
,_to(CCPointZero)
,_moving(false)
,_fromIndex(0)
,_hasEndPosition(false)
,_pCurrentPaths(NULL)
,_pNextPaths(NULL)
,_pathIndex(0)
,_update(NULL)
{

}

SceenCoordMoveComponent::~SceenCoordMoveComponent()
{
	CC_SAFE_RELEASE(_pCurrentPaths);
	CC_SAFE_RELEASE(_pNextPaths);
}

bool SceenCoordMoveComponent::init()
{
	if(Component::init()){
		_moveState=MoveStop;      
	}
    return true;
}

bool SceenCoordMoveComponent::init(float speed)
{
	if (init()) {
		_speed=speed;
	}
	return true;
}

void SceenCoordMoveComponent::setup()
{
    Component::setup();
    _isoPositionComponent=static_cast<ISOPositionComponent*>(_owner->getComponent("ISOPositionComponent"));
    _rendererComponent=static_cast<RendererComponent*>(_owner->getComponent("RendererComponent"));
}

void SceenCoordMoveComponent::cleanup()
{
    _isoPositionComponent=NULL;
    _rendererComponent=NULL;
    Component::cleanup();
}

bool SceenCoordMoveComponent::registerMessages()
{
    if(Component::registerMessages()){
        MessageManager* messageManager=MessageManager::defaultManager();
        
        messageManager->registerReceiver(_owner, MSG_MOVE_DIRECTION, NULL, message_selector(SceenCoordMoveComponent::onMoveDirection),this);
        messageManager->registerReceiver(_owner, MSG_MOVE_STOP, NULL, message_selector(SceenCoordMoveComponent::onMoveStop),this);
        messageManager->registerReceiver(_owner, MSG_MOVE_TO, NULL, message_selector(SceenCoordMoveComponent::onMoveTo),this);
        
        return true;
    }
    
    return false;

}

void SceenCoordMoveComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(_owner, MSG_MOVE_DIRECTION);
    this->getMessageManager()->removeReceiver(_owner, MSG_MOVE_DIRECTION_STOP);
    this->getMessageManager()->removeReceiver(_owner, MSG_MOVE_TO);
    
    Component::cleanupMessages();
}

/**
 * 移动之前进行检查
 */

bool SceenCoordMoveComponent::checkMoveable()
{
	return true;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void SceenCoordMoveComponent::startMove()
{
    CCLOG("startMove");
	_moveState=MoveStart;
    startMoveUpdateSchedule();
    doMoveStart();
}

/**
 * 停止移动
 * 由于不是按格子移动，可以立即停止移动
 */
void SceenCoordMoveComponent::stopMove()
{
    stopMoveUpdateSchedule();
    _moveState=MoveStop;
    doMoveStop();
}

void SceenCoordMoveComponent::moveTo(const CCPoint& to)
{
    if (_moveState==MoveStop) {
        
        _moveType=kMoveTo;
        
        CCPoint from=_rendererComponent->getRenderer()->getPosition();
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

void SceenCoordMoveComponent::continueMoveTo(const CCPoint& to)
{
    CCAssert(_moveType==kMoveTo, "SceenCoordMoveComponent::continueMoveTo before move type is not the same");
    
    CCPoint from=_rendererComponent->getRenderer()->getPosition();
    
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

void SceenCoordMoveComponent::moveWithDirection(float direction)
{
    moveWithDirection(direction,false);
}

void SceenCoordMoveComponent::moveWithDirection(float direction,bool hasTo)
{
    CCLOG("moveWithDirection:%f",direction);
    
    if (_moveState==MoveStop) {
        
        _moveType=kMoveDirection;
        
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
void SceenCoordMoveComponent::moveWithDirection(float directionX ,float directionY)
{
    moveWithDirection(directionX, directionY, false);
}

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void SceenCoordMoveComponent::moveWithDirection(float directionX ,float directionY,bool hasTo)
{
    if (_moveState==MoveStop) {
        
        _moveType=kMoveDirection;
        
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
void SceenCoordMoveComponent::continueMoveWithDirection(float direction)
{
    CCAssert(_moveType==kMoveDirection, "SceenCoordMoveComponent::continueMoveWithDirection before move type is not the same");
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
void SceenCoordMoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
    CCAssert(_moveType==kMoveDirection, "SceenCoordMoveComponent::continueMoveWithDirection before move type is not the same");
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
void SceenCoordMoveComponent::moveWithPaths(CCArray* paths)
{
	moveWithPaths(paths ,0);
}

void SceenCoordMoveComponent::moveWithPaths(CCArray* paths,int fromIndex)
{
	if (_moveState==MoveStop) {
        
        _moveType=kMovePath;
        
		_fromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (checkMoveable()) {
            prepareMove();
			startMove();
		}
	}else{
		_fromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}
}
/**
 * 继续指定路径移动
 */
void SceenCoordMoveComponent::continueMoveWithPaths(CCArray* paths)
{
    CCAssert(_moveType==kMovePath, "SceenCoordMoveComponent::continueMoveWithPaths before move type is not the same");
	this->setNextPaths(paths);
    preparePath();
    if (checkMoveable()) {
        prepareMove();
    }else{
        stopMove();
    }
//	_moveState=MoveContinue;
}

/**
 * 路径移动之前进行检查
 */
bool SceenCoordMoveComponent::beforeMovePath()
{
	if(checkMoveable()){
		calcDirection();
		return true;
	}
	return false;
}

void SceenCoordMoveComponent::restartMoveWithPaths()
{
	_moveState=MoveStart;
	preparePath();
	beforeMovePath();
}

/**
 * 取得当前路径结点索引
 */
int SceenCoordMoveComponent::getCurrentPathIndex(){
	return _pCurrentPaths->count()-2-_fromIndex;
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void SceenCoordMoveComponent::calcDirection()
{
	CCPoint pos=_rendererComponent->getRenderer()->getPosition();
	_directionX=_to.x>pos.x?1:_to.x<pos.y?-1:0;
	_directionY=_to.y>pos.y?1:_to.y<pos.y?-1:0;
}

/**
 * 计算速度分量
 */
void SceenCoordMoveComponent::calcSpeedVector(){
    _speedX=_speed*_directionX;
    _speedY=_speed*_directionY;
}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void SceenCoordMoveComponent::updateTo( float delta)
{
    CCNode* renderer=_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
	//根据速度计算移动距离
	pos.x+=delta*_speedX;
	pos.y+=delta*_speedY;
    
    //    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束
	if ((_directionFlagX * pos.x>_directionFlagX*_to.x  || fabs(pos.x-_to.x)<0.00001) &&  (_directionFlagY*pos.y> _directionFlagY* _to.y|| fabs(pos.y-_to.y)<0.00001)) {
		pos.x=_to.x;
		pos.y=_to.y;
		stopMove();
	}
    
	renderer->setPosition(pos);
}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void SceenCoordMoveComponent::updateDirection( float delta)
{
    CCNode* renderer=_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
    
	//根据速度计算移动距离
	pos.x+=delta*_speedX;
	pos.y+=delta*_speedY;
    
    renderer->setPosition(pos);
    
    //由于没有目标点，必须手动停止。或遇障碍物会停止。

}

/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void SceenCoordMoveComponent::updatePath(float delta)
{
    CCNode* renderer=_rendererComponent->getRenderer();
    
    CCPoint pos=renderer->getPosition();
	//根据速度计算移动距离
	pos.x+=delta*_speedX;
	pos.y+=delta*_speedY;
    
//    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束	
	if ((_directionFlagX * pos.x>_directionFlagX*_to.x  || fabs(pos.x-_to.x)<0.00001) &&  (_directionFlagY*pos.y> _directionFlagY* _to.y|| fabs(pos.y-_to.y)<0.00001)) {
		pos.x=_to.x;
		pos.y=_to.y;

        if (--_pathIndex>=0 && _moveState==MoveStart) {
			//进行下一个格子
            preparePath(_pathIndex);
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
void SceenCoordMoveComponent::doDirectionChange()
{
	//根据方向来确定8方向。
    //一种方法是根据角度值来确定8方向
    //一种是直接根据公式来映射
	int index=kDirectionMapping[this->hadap(_direction)];

	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), "name");
		data->setObject(CCInteger::create(index), "direction");
    
		this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, _owner,data);
	}
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void SceenCoordMoveComponent::doMoveStart()
{
    doDirectionChange();
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void SceenCoordMoveComponent::doMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, _owner,data);

}

//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。
void SceenCoordMoveComponent::doHit(CCPoint location)
{
	
}

void SceenCoordMoveComponent::onMoveDirection(Message *message)
{
    CCInteger* integer=(CCInteger*)message->getData();
    moveWithDirection(kmDegreesToRadians(integer->getValue()));
}

void SceenCoordMoveComponent::onMoveWithPath(Message *message)
{
    CCDictionary* data=message->getDictionary();
    
    CCArray* paths=(CCArray*)data->objectForKey("paths");
    CCInteger* fromIndex=static_cast<CCInteger*>(data->objectForKey("fromIndex"));
    moveWithPaths(paths,fromIndex->getValue());
}

void SceenCoordMoveComponent::onMoveTo(Message *message)
{
    CCPoint to=static_cast<CCPointValue*>(message->getData())->getPoint();
    moveTo(to);
}

void SceenCoordMoveComponent::onMoveStop(Message *message)
{
    stopMove();
}

/**
 * 准备移动到的数据
 */
bool SceenCoordMoveComponent::prepareTo(const CCPoint& to,const CCPoint& from)
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
void SceenCoordMoveComponent::prepareDirection(float direction)
{
    _directionX=cosf(direction);
    _directionY=sinf(direction);
    _direction=direction;
    _directionFlagX=_directionX>0?1:_directionX<0?-1:0;
    _directionFlagY=_directionX>0?1:_directionX<0?-1:0;
}

/**
 * 准备方向移动的数据
 */
void SceenCoordMoveComponent::prepareDirection(float directionX,float directionY)
{
    _directionX=directionX;
    _directionY=directionY;
    _direction=atan2f(directionY, directionX);
    _directionFlagX=_directionX>0?1:_directionX<0?-1:0;
    _directionFlagY=_directionX>0?1:_directionX<0?-1:0;
}

/**
 * 准备移动路径
 */
void SceenCoordMoveComponent::preparePath()
{
	_pathIndex=getCurrentPathIndex();
	preparePath(_pathIndex);
}

void SceenCoordMoveComponent::preparePath(int pathIndex)
{
    CCAssert(pathIndex>=0,"paths length less 2");
	CCLOG("preparePath.PathIndex:%d",pathIndex);
    CCPoint to= static_cast<CCPointValue*>(_pCurrentPaths->objectAtIndex(pathIndex))->getPoint();
    CCPoint from=_rendererComponent->getRenderer()->getPosition();
    prepareTo(to, from);
}

/**
 * 移动之前的准备
 */
void SceenCoordMoveComponent::prepareMove()
{
    calcSpeedVector();
}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void SceenCoordMoveComponent::startMoveUpdateSchedule()
{
    switch (_moveType)
    {
        case kMoveDirection:
            _update=schedule_selector(SceenCoordMoveComponent::updateDirection);
            break;
        case kMovePath:
            _update=schedule_selector(SceenCoordMoveComponent::updatePath);
            break;
        default:
            break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(_update,this, 0, false);
}

void SceenCoordMoveComponent::stopMoveUpdateSchedule()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(_update,this);
    _update=NULL;
}

NS_CC_YHGE_END
