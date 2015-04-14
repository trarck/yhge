#include "AutoAttackComponent.h"
#include <yhge/Base/Log.h>
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

AutoAttackComponent::AutoAttackComponent()
:_attackSpeed(2)
{
    _name="AutoAttackComponent";
}

AutoAttackComponent::~AutoAttackComponent()
{
    CC_SAFE_RELEASE(_target);
}

bool AutoAttackComponent::init()
{
    return true;
}

bool AutoAttackComponent::registerMessages()
{

    if(AttackComponent::registerMessages()){
        this->getMessageManager()->registerReceiver(_owner, MSG_AUTO_ATTACK, NULL, message_selector(AutoAttackComponent::onAutoAttack));
        return true;
    }
    
    return false;
}

void AutoAttackComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(_owner, MSG_AUTO_ATTACK);
    
    AttackComponent::cleanupMessages();
}


void AutoAttackComponent::startAttack()
{
    YHINFO("AutoAttackComponent::startAttack");
	if (_target) {
        CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this, _attackSpeed, false);
	}
}

void AutoAttackComponent::stopAttack()
{
    YHINFO("AutoAttackComponent::stopAttack");
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this);
}

void AutoAttackComponent::updateAttack(float delta)
{
    YHINFO("AutoAttackComponent::updateAttack");
	//check attack stop
	/*
	 1.target die
	 2.if use skill, mp less then the skill requirement
	 */
    //TODO get target hp
//	int targetHp=10;//_target->getHealth();
//    YHINFO("current target hp %d after attack %d",targetHp,targetHp-1);
    
    //TODO set target hp
//    _target->setHealth(targetHp-1);
}

void AutoAttackComponent::didTargetDie()
{
    stopAttack();
}

/**
 * 开始自动攻击
 */
void AutoAttackComponent::onAutoAttack(Message* message)
{
    Entity* target= static_cast<Entity*>(message->getData());
    if(target){
        setTarget(target);
    }
    startAttack();
}

/**
 * 处理目标死亡消息
 */
void AutoAttackComponent::onTargetDie(Message *message)
{
    stopAttack();
    AttackComponent::onTargetDie(message);
}

NS_CC_YHGE_END

