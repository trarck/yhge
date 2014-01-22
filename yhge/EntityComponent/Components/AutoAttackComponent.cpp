#include "AutoAttackComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

AutoAttackComponent::AutoAttackComponent()
:m_attackSpeed(2)
{
    m_name="AutoAttackComponent";
}

AutoAttackComponent::~AutoAttackComponent()
{
    CC_SAFE_RELEASE(m_target);
}

bool AutoAttackComponent::init()
{
    return true;
}

bool AutoAttackComponent::registerMessages()
{

    if(AttackComponent::registerMessages()){
        this->getMessageManager()->registerReceiver(m_owner, MSG_AUTO_ATTACK, NULL, message_selector(AutoAttackComponent::onAutoAttack));
        return true;
    }
    
    return false;
}

void AutoAttackComponent::cleanupMessages()
{
    this->getMessageManager()->removeReceiver(m_owner, MSG_AUTO_ATTACK);
    
    AttackComponent::cleanupMessages();
}


void AutoAttackComponent::startAttack()
{
    CCLOG("AutoAttackComponent::startAttack");
	if (m_target) {
        CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this, m_attackSpeed, false);
	}
}

void AutoAttackComponent::stopAttack()
{
    CCLOG("AutoAttackComponent::stopAttack");
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this);
}

void AutoAttackComponent::updateAttack(float delta)
{
    CCLOG("AutoAttackComponent::updateAttack");
	//check attack stop
	/*
	 1.target die
	 2.if use skill, mp less then the skill requirement
	 */
    //TODO get target hp
	int targetHp=10;//m_target->getHealth();
    CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
    
    //TODO set target hp
//    m_target->setHealth(targetHp-1);
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
    CCObject* target=message->getData();
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

