#ifndef YHGE_COMPONENTS_ATTACKCOMPONENT_H_
#define YHGE_COMPONENTS_ATTACKCOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class AttackComponent : public Component 
{
public:
    AttackComponent();
    ~AttackComponent();
    virtual bool init();

	virtual void attack();
    virtual void attackWithSkillId(int skillId);
    
    virtual void didTargetDie();
    
    virtual void setTarget(CCObject* target);
    CCObject* getTarget();
    
protected:
    CCObject* m_target;
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_ATTACKCOMPONENT_H_
