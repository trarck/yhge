#include "AttackComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

AttackComponent::AttackComponent()
:m_target(NULL)
{
    CCLOG("AttackComponent create");
    m_name="AttackComponent";
}

AttackComponent::~AttackComponent()
{
    CCLOG("AttackComponent destroy");
    CC_SAFE_RELEASE_NULL(m_target);
}

bool AttackComponent::init()
{
    CCLOG("AttackComponent init");
    return true;
}

bool AttackComponent::registerMessages()
{
    CCLOG("AttackComponent::registerMessages");
    
    Component::registerMessages();
    
    yhge::MessageManager::defaultManager()->registerReceiver(m_owner, MSG_SET_ATTACK_TARGET, NULL, message_selector(AttackComponent::onSetAttackTarget));
    
    yhge::MessageManager::defaultManager()->registerReceiver(m_owner, MSG_ATTACK, NULL, message_selector(AttackComponent::onAttack));
    
    return true;
}

void AttackComponent::cleanupMessages()
{
	CCLOG("AttackComponent::cleanupMessages");
    yhge::MessageManager::defaultManager()->removeReceiver(m_owner, MSG_SET_ATTACK_TARGET);
    yhge::MessageManager::defaultManager()->removeReceiver(m_owner, MSG_ATTACK);
    yhge::MessageManager::defaultManager()->removeReceiver(m_owner, MSG_TARGET_DIE);
    
    Component::cleanupMessages();
}


void AttackComponent::attack()
{
    if(m_target){
        CCLOG("AttackComponent::startAttack");
        int targetHp=10;//m_target->getHealth();
        CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
//        m_target->setHealth(targetHp-1);
    }else {
        CCLOG("AttackComponent::startAttack no target");
    }
}



void AttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

/**
 * 处理攻击消息
 */
void AttackComponent::onAttack(Message *message)
{
    CCObject* target=message->getData();
    if(target){
        setTarget(target);
    }
    attack();
}

/**
 * 处理设置目标消息
 */
void AttackComponent::onSetAttackTarget(Message *message)
{
    CCObject* target=message->getData();
    
    MessageManager::defaultManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    setTarget(message->getData());
    MessageManager::defaultManager()->registerReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
}

/**
 * 处理目标死亡消息
 */
void AttackComponent::onTargetDie(Message *message)
{
    CCLOG("target is die");
    MessageManager::defaultManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    CC_SAFE_RELEASE(m_target);
    m_target=NULL;
}

NS_CC_YHGE_END

