#include "IsometricProperty.h"

NS_CC_YHGE_BEGIN

IsometricProperty::IsometricProperty()
{
    CCLOG("Entity create");
}

IsometricProperty::~IsometricProperty()
{
    CCLOG("Entity destroy");

}

bool IsometricProperty::init(void)
{
    CCLOG("Entity init");
    return true;
}

NS_CC_YHGE_END
