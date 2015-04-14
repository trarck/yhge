#include "AttackComponent.h"
#include <yhge/Base/Log.h>
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>
#include "ComponentConsts.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

AttackComponent::AttackComponent()
:Component("AttackComponent")
,_target(NULL)
{

}

AttackComponent::~AttackComponent()
{
    CC_SAFE_RELEASE_NULL(_target);
}

bool AttackComponent::init()
{
    return true;
}

bool AttackComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(_owner, MSG_SET_ATTACK_TARGET, NULL, message_selector(AttackComponent::onSetAttackTarget),this);
        
        messageManager->registerReceiver(_owner, MSG_ATTACK, NULL, message_selector(AttackComponent::onAttack),this);
        
        messageManager->registerReceiver(_owner, MSG_SKILL_ATTACK, NULL, message_selector(AttackComponent::onSkillAttack),this);
        
        return true;
    }
    return false;
}

void AttackComponent::cleanupMessages()
{    
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(_owner, MSG_SET_ATTACK_TARGET);
    messageManager->removeReceiver(_owner, MSG_ATTACK);
    messageManager->removeReceiver(_owner, MSG_SKILL_ATTACK);
    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE);
    
    Component::cleanupMessages();
}


void AttackComponent::attack()
{
    
    CCAssert(false, "don't call AttackComponent::attack function");
//    if(_target){
//        CCLOG("AttackComponent::startAttack");
//        int targetHp=10;//_target->getHealth();
//        CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
////        _target->setHealth(targetHp-1);
//    }else {
//        CCLOG("AttackComponent::startAttack no target");
//    }
    //攻击完成，消除目标。如果需要保存目标，则别行处理
//    setTarget(NULL);
}

void AttackComponent::attackWithSkillId(int skillId)
{
	//if (_target!=nil) {
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
 * 处理技能攻击消息
 */
void AttackComponent::onSkillAttack(Message *message)
{
    CCDictionary* data=message->getDictionary();
    
    Entity* target= static_cast<Entity*>(data->objectForKey(COMPONENT_ATTARCK_TARGET));
    if(target){
        setTarget(target);
    }
    
    CCInteger* skillIdValue=static_cast<CCInteger*>(data->objectForKey(COMPONENT_ATTARCK_SKILL_ID));
    if (skillIdValue) {
         attackWithSkillId(skillIdValue->getValue());
    }
}

/**
 * 处理设置目标消息
 */
void AttackComponent::onSetAttackTarget(Message *message)
{
    Entity* target= static_cast<Entity*>(message->getData());
    
    this->getMessageManager()->removeReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, _target, message_selector(AttackComponent::onTargetDie));
    setTarget(target);
    this->getMessageManager()->registerReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, _target, message_selector(AttackComponent::onTargetDie),this);
}

/**
 * 处理目标死亡消息
 */
void AttackComponent::onTargetDie(Message *message)
{
    YHINFO("target is die");
    this->getMessageManager()->removeReceiver(this->getMessageManager()->getGlobalObject(), MSG_ENTITY_DIE, _target, message_selector(AttackComponent::onTargetDie));
    CC_SAFE_RELEASE(_target);
    _target=NULL;
}

void AttackComponent::setTarget(Entity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(_target);
    _target = target;
}

NS_CC_YHGE_END

