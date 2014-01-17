#include "ManualAttackComponent.h"
#include "CCMessageManager.h"
#include "GameMessages.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

ManualAttackComponent::ManualAttackComponent()
{
    CCLOG("ManualAttackComponent create");
    m_name="ManualAttackComponent";
}

ManualAttackComponent::~ManualAttackComponent()
{
    CCLOG("ManualAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool ManualAttackComponent::init()
{
    CCLOG("ManualAttackComponent init");
    return true;
}

NS_CC_YHGE_END
