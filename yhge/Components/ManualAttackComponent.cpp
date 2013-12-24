#include "ManualAttackComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ManualAttackComponent::ManualAttackComponent()
{
    CCLOG("ManualAttackComponent create");
}

ManualAttackComponent::~ManualAttackComponent()
{
    CCLOG("ManualAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool ManualAttackComponent::init()
{
    CCLOG("ManualAttackComponent init");
	m_sName="ManualAttackComponent";
    return true;
}

NS_CC_YHGE_END

