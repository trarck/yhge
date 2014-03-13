#include "CCActionMessage.h"
#include <yhge/message.h>

NS_CC_YHGE_BEGIN

CCActionMessage::CCActionMessage()
:m_message(NULL)
{
    
}

CCActionMessage::~CCActionMessage()
{
    CC_SAFE_RELEASE_NULL(m_message);
}

bool CCActionMessage::init(CCFiniteTimeAction* innerAction,Message* message)
{
    CCCallFunc* callback=CCCallFunc::create(this, callfunc_selector(CCActionMessage::callback));
    
    if (CCSequence::initWithTwoActions(innerAction, callback)) {
        
        setMessage(message);
        
        return true;
    }
    
    return false;
}

void CCActionMessage::callback()
{
    MessageManager::defaultManager()->dispatchMessage(m_message);
}

NS_CC_YHGE_END
