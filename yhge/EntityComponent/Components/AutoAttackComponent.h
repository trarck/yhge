#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_AUTOATTACKCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_AUTOATTACKCOMPONENT_H_

#include "cocos2d.h"
#include "AttackComponent.h"

NS_CC_YHGE_BEGIN


class AutoAttackComponent : public AttackComponent 
{
public:
    AutoAttackComponent();
    ~AutoAttackComponent();
    
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void cleanupMessages();
    
    void startAttack();
    
    virtual void didTargetDie();
    
    void stopAttack();
    
    void updateAttack(float delta);

    /**
     * 开始自动攻击
     */
    virtual void onAutoAttack(Message* message);
    
    /**
     * 处理目标死亡消息
     */
    virtual void onTargetDie(Message *message);
    
public:
    
    float getAttackSpeed()
    {
        return _attackSpeed;
    }
    
    void setAttackSpeed(float attackSpeed)
    {
        _attackSpeed=attackSpeed;
    }
protected:
    float _attackSpeed;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_AUTOATTACKCOMPONENT_H_
