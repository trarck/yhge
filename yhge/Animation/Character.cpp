
#include "Character.h"

NS_CC_YHGE_BEGIN

Character::Character()
:m_id(0)
,m_resource(NULL)
,m_anchor(CCPointZero)
{

}
    
Character::~Character()
{
    CC_SAFE_RELEASE_NULL(m_resource);
}

bool Character::init()
{
    return true;
}


NS_CC_YHGE_END