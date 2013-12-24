#ifndef YHGE_COMPONENTS_AUTOATTACKCOMPONENT_H_
#define YHGE_COMPONENTS_AUTOATTACKCOMPONENT_H_

#include "cocos2d.h"

#include "AttackComponent.h"

NS_CC_YHGE_BEGIN


class AutoAttackComponent : public AttackComponent 
{
public:
    AutoAttackComponent();
    ~AutoAttackComponent();
    virtual bool init();
	
    virtual void attack();
    virtual void didTargetDie();
    
    void stopAttack();
    void updateAttack(float delta);
    
    float getAttackSpeed();
    void setAttackSpeed(float attackSpeed);
protected:
    float m_attackSpeed;
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_AUTOATTACKCOMPONENT_H_
