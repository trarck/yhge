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
    
    DelayMessage(float delay,cocos2d::Message* message)
    :m_pMessage(message)
    ,m_fDelay(delay)
    {
        CC_SAFE_RETAIN(message);
    }
    
    ~DelayMessage()
    {
        CC_SAFE_RELEASE(m_pMessage);
    }
    
    inline void setMessage(cocos2d::Message* pMessage)
    {
        CC_SAFE_RETAIN(pMessage);
        CC_SAFE_RELEASE(m_pMessage);
        m_pMessage = pMessage;
    }
    
    inline cocos2d::Message* getMessage()
    {
        return m_pMessage;
    }
    
    float m_fDelay;

private:
    
    cocos2d::Message* m_pMessage;

    
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
    
    void dispatchMessage(cocos2d::Message* message,float fDelay);
    
    inline void setMessageManager(cocos2d::MessageManager* pMessageManager)
    {
        CC_SAFE_RETAIN(pMessageManager);
        CC_SAFE_RELEASE(m_pMessageManager);
        m_pMessageManager = pMessageManager;
    }
    
    inline cocos2d::MessageManager* getMessageManager()
    {
        return m_pMessageManager;
    }
    
private:
    
    cocos2d::CCArray* m_pMessages;
    
    cocos2d::MessageManager* m_pMessageManager;
};

NS_CC_YHGE_END

#endif //YHGE_MESSAGE_DelayMessageManager_H_
