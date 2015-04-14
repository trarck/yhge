
#include "Character.h"

NS_CC_YHGE_BEGIN

Character::Character()
:_id(0)
,_resource(NULL)
,_anchor(CCPointZero)
{

}
    
Character::~Character()
{
    CC_SAFE_RELEASE_NULL(_resource);
}

bool Character::init()
{
    return true;
}


NS_CC_YHGE_END