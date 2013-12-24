#ifndef YHGE_COMPONENTS_CCMANUALATTACKCOMPONENT_H_
#define YHGE_COMPONENTS_CCMANUALATTACKCOMPONENT_H_

#include "cocos2d.h"
#include "AttackComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN


class ManualAttackComponent : public AttackComponent 
{
public:
    ManualAttackComponent();
    ~ManualAttackComponent();
    virtual bool init();
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_CCMANUALATTACKCOMPONENT_H_
