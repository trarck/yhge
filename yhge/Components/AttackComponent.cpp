#include "AttackComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include "Entity.h"

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
    
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, MSG_SET_ATTACK_TARGET, NULL, message_selector(AttackComponent::onSetAttackTarget),this);
        
        messageManager->registerReceiver(m_owner, MSG_ATTACK, NULL, message_selector(AttackComponent::onAttack),this);
        
        return true;
    }
    return false;
}

void AttackComponent::cleanupMessages()
{
	CCLOG("AttackComponent::cleanupMessages");
    
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, MSG_SET_ATTACK_TARGET);
    messageManager->removeReceiver(m_owner, MSG_ATTACK);
    messageManager->removeReceiver(m_owner, MSG_TARGET_DIE);
    
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
    
    this->getMessageManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    setTarget(target);
    this->getMessageManager()->registerReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
}

/**
 * 处理目标死亡消息
 */
void AttackComponent::onTargetDie(Message *message)
{
    CCLOG("target is die");
    this->getMessageManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    CC_SAFE_RELEASE(m_target);
    m_target=NULL;
}

NS_CC_YHGE_END

