#include "ManualAttackComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ManualAttackComponent::ManualAttackComponent()
{
    m_name="ManualAttackComponent";
}

ManualAttackComponent::~ManualAttackComponent()
{
    CC_SAFE_RELEASE(m_target);
}

bool ManualAttackComponent::init()
{
    return true;
}

NS_CC_YHGE_END

