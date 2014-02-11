#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ATTACKCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ATTACKCOMPONENT_H_

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
    virtual void onAttack(Message *message);
    
    /**
     * 处理设置目标消息
     */
    virtual void onSetAttackTarget(Message *message);
    
    /**
     * 处理目标死亡消息
     */
    virtual void onTargetDie(Message *message);
    
    virtual void setTarget(Entity* target);
    
public:
    
    inline Entity* getTarget()
    {
        return m_target;
    }
    
protected:
    
    Entity* m_target;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ATTACKCOMPONENT_H_
