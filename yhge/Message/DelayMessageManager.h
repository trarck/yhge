//
//  DelayMessageManager.h
//	延迟消息
//

#ifndef YHGE_MESSAGE_DelayMessageManager_H_
#define YHGE_MESSAGE_DelayMessageManager_H_

#include "Message.h"
#include "MessageManager.h"

NS_CC_YHGE_BEGIN

class DelayMessage:public cocos2d::CCObject
{
public:
    
    DelayMessage()
    :m_pMessage(NULL)
    ,m_fDelay(0.0f)
    {
        
    }
    
    DelayMessage(float delay,Message* message)
    :m_pMessage(message)
    ,m_fDelay(delay)
    {
        CC_SAFE_RETAIN(message);
    }
    
    ~DelayMessage()
    {
        CC_SAFE_RELEASE(m_pMessage);
    }
    
    inline void setMessage(Message* pMessage)
    {
        CC_SAFE_RETAIN(pMessage);
        CC_SAFE_RELEASE(m_pMessage);
        m_pMessage = pMessage;
    }
    
    inline Message* getMessage()
    {
        return m_pMessage;
    }
    
    float m_fDelay;

private:
    
    Message* m_pMessage;

    
};

class DelayMessageManager:public cocos2d::CCObject
{
public:
    
    DelayMessageManager();
    
    ~DelayMessageManager();
    
    static DelayMessageManager* sharedDelayMessageManager();
    
    bool init();
    
    void start();
    
    void stop();
    
    void update(float delta);
    
    void dispatchMessage(Message* message,float fDelay);
    
    inline void setMessageManager(MessageManager* pMessageManager)
    {
        CC_SAFE_RETAIN(pMessageManager);
        CC_SAFE_RELEASE(m_pMessageManager);
        m_pMessageManager = pMessageManager;
    }
    
    inline MessageManager* getMessageManager()
    {
        return m_pMessageManager;
    }
    
private:
    
    cocos2d::CCArray* m_pMessages;
    
    MessageManager* m_pMessageManager;
};

NS_CC_YHGE_END

#endif //YHGE_MESSAGE_DelayMessageManager_H_
