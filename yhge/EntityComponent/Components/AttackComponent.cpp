#include "AttackComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

AttackComponent::AttackComponent()
:Component("AttackComponent")
,m_target(NULL)
{

}

AttackComponent::~AttackComponent()
{
    CC_SAFE_RELEASE_NULL(m_target);
}

bool AttackComponent::init()
{
    return true;
}

bool AttackComponent::registerMessages()
{
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
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, MSG_SET_ATTACK_TARGET);
    messageManager->removeReceiver(m_owner, MSG_ATTACK);
    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE);
    
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
    Entity* target= static_cast<Entity*>(message->getData());
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
    Entity* target= static_cast<Entity*>(message->getData());
    
    this->getMessageManager()->removeReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    setTarget(target);
    this->getMessageManager()->registerReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, m_target, message_selector(AttackComponent::onTargetDie),this);
}

/**
 * 处理目标死亡消息
 */
void AttackComponent::onTargetDie(Message *message)
{
    CCLOG("target is die");
    this->getMessageManager()->removeReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, m_target, message_selector(AttackComponent::onTargetDie));
    CC_SAFE_RELEASE(m_target);
    m_target=NULL;
}

void AttackComponent::setTarget(Entity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

NS_CC_YHGE_END

