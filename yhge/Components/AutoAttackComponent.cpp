#include "AutoAttackComponent.h"
#include <yhge/Message/MessageManager.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

AutoAttackComponent::AutoAttackComponent()
:m_attackSpeed(2)
{
    CCLOG("AutoAttackComponent create");
}

AutoAttackComponent::~AutoAttackComponent()
{
    CCLOG("AutoAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool AutoAttackComponent::init()
{
    CCLOG("AutoAttackComponent init");
	m_sName="AutoAttackComponent";
    return true;
}

void AutoAttackComponent::attack()
{
    CCLOG("AutoAttackComponent::startAttack");
	if (m_target) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this, m_attackSpeed, false);
	}
}

void AutoAttackComponent::stopAttack()
{
    CCLOG("AutoAttackComponent::stopAttack");
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
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
	//int targetHp=m_target->getHealth();
 //   CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
 //   m_target->setHealth(targetHp-1);
}

void AutoAttackComponent::didTargetDie()
{
    stopAttack();
}

float AutoAttackComponent::getAttackSpeed()
{
	return m_attackSpeed;
}

void AutoAttackComponent::setAttackSpeed(float attackSpeed)
{
	m_attackSpeed=attackSpeed;
}

NS_CC_YHGE_END

