#ifndef YHGE_COCOSEXT_CCACTIONMESSAGE_H_
#define YHGE_COCOSEXT_CCACTIONMESSAGE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/message.h>

NS_CC_YHGE_BEGIN

/**
 * action 执行完后会触发消息
 */

class CCActionMessage : public CCSequence
{
public:
    
    CCActionMessage();
    
    ~CCActionMessage();
    
    bool init(CCFiniteTimeAction* innerAction,Message* message);
    
    void callback();

    inline void setMessage(Message* message)
    {
        CC_SAFE_RETAIN(message);
        CC_SAFE_RELEASE(_message);
        _message = message;
    }
    
    inline Message* getMessage()
    {
        return _message;
    }
    
protected:
    
    Message* _message;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCACTIONMESSAGE_H_
