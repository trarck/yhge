#include "AttackComponent.h"
#include <yhge/Message/MessageManager.h>


USING_NS_CC;

NS_CC_YHGE_BEGIN

AttackComponent::AttackComponent()
:m_target(NULL)
{
    CCLOG("AttackComponent create");
    m_sName="AttackComponent";
}

AttackComponent::~AttackComponent()
{
    CCLOG("AttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool AttackComponent::init()
{
    CCLOG("AttackComponent init");
    return true;
}

void AttackComponent::attack()
{
    //if(m_target){
    //    CCLOG("AttackComponent::startAttack");
    //    int targetHp=m_target->getHealth();
    //    CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
    //    m_target->setHealth(targetHp-1);
    //}else {
    //    CCLOG("AttackComponent::startAttack no target");
    //}
}

void AttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

void AttackComponent::didTargetDie()
{
    CCLOG("target is die");
    
    ////remove message
    //MessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(AttackComponent::handleMessage));
    //CC_SAFE_RELEASE(m_target);
    //m_target=NULL;
}

CCObject* AttackComponent::getTarget()
{
    return m_target;
}

void AttackComponent::setTarget(CCObject* target)
{
    if(target!=m_target){
        //MessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(AttackComponent::handleMessage));
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target=target;

        //MessageManager::defaultManager()->registerReceiver(this, message_selector(AttackComponent::handleMessage), DIE, m_target);
    }
}

NS_CC_YHGE_END

