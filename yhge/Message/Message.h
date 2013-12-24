//
//  
//  消息是基于投递的，不存在父子关系。一个消息对应消息的处理函数（一个或多个），不存捕捉和冒泡。可以延迟发关。可以设置优先级。
//  注意和事件的区别，事件要复杂些。消息通常和简单发送执行，所以性能要高一些。
//  当然事件可以定义的很简单或遵循一定模式(dom事件模型)。
//
#ifndef YHGE_MESSAGE_MESSAGE_H_
#define YHGE_MESSAGE_MESSAGE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class Message : public CCObject {

public:
    Message()
	:m_type(0)
	,m_sender(NULL)
	,m_receiver(NULL)
	,m_pData(NULL)
	,m_timeStamp(0.0f)
	,m_pExtData(NULL)
	{
		
	}

    ~Message(void);
    
	bool initWithType(unsigned int type,CCObject* sender ,CCObject* receiver ,CCObject *data){
		 m_type=type;
		setSender(sender);
		setReceiver(receiver);
		setData(data);
		return true;
	}

    bool initWithType(unsigned int type,CCObject* sender ,CCObject* receiver){
		m_type=type;
		setSender(sender);
		setReceiver(receiver);
    	return true;
	}

    bool initWithType(unsigned int type,CCObject* sender){
		m_type=type;
		setSender(sender);
  		return true;
	}

	unsigned int getType(){
		return m_type;
	}
	void setType(unsigned int type){
	    m_type=type;
	}

	CCObject* getSender(){
		return m_sender;
	}

	void setSender(CCObject* sender){
		CC_SAFE_RETAIN(sender);
		CC_SAFE_RELEASE(m_sender);
		m_sender=sender;
	}

	CCObject* getReceiver(){
		return m_receiver;
	}

	void setReceiver(CCObject* receiver){
		CC_SAFE_RETAIN(receiver);
		CC_SAFE_RELEASE(m_receiver);
		m_receiver=receiver;
	}
    
	CCObject* getData(){
		return m_pData;
	}

    void setData(CCObject* data){
		CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_pData);
		m_pData=data;
	}

    CCDictionary* getDictionary(){
		 return (CCDictionary*) m_pData;
	}

	CCObject* getExtData(){
		return m_pExtData;
	}

    void setExtData(CCObject* ExtData){
		CC_SAFE_RETAIN(ExtData);
		CC_SAFE_RELEASE(m_pExtData);
		m_pExtData=ExtData;
	}

private:
    unsigned int m_type;//消息的类型或ID。
    CCObject* m_sender;//消息的发送者
	CCObject* m_receiver;//消息的接收者
    float m_timeStamp;//发送时间
    CCObject* m_pData;
	CCObject* m_pExtData;//附加数据。
};

NS_CC_YHGE_END

#endif  // YHGE_MESSAGE_MESSAGE_H_
