#include "ManualAttackComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ManualAttackComponent::ManualAttackComponent()
{
    _name="ManualAttackComponent";
}

ManualAttackComponent::~ManualAttackComponent()
{
    CC_SAFE_RELEASE(_target);
}

bool ManualAttackComponent::init()
{
    return true;
}

NS_CC_YHGE_END

