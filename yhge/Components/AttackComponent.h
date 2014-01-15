#ifndef YHGE_COMPONENTS_ATTACK_COMPONENT_H_
#define YHGE_COMPONENTS_ATTACK_COMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN


class AttackComponent : public Component 
{
public:
    
    AttackComponent();
    ~AttackComponent();
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(Message* message);
    virtual void cleanupMessages();
    
    /**
     * 攻击
     */
    virtual void attack();
    
    /**
     * 使用技能攻击
     */
    virtual void attackWithSkillId(int skillId);

    /**
     * 处理攻击消息
     */
    void onAttack(Message *message);
    
    /**
     * 处理设置目标消息
     */
    void onSetAttackTarget(Message *message);
    
    /**
     * 处理目标死亡消息
     */
    void onTargetDie(Message *message);
public:
    
    inline void setTarget(CCObject* target)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target = target;
    }
    
    inline CCObject* getTarget()
    {
        return m_target;
    }
    
protected:
    
    CCObject* m_target;
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_ATTACK_COMPONENT_H_
