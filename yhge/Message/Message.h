//
//  
//  消息是基于投递的，不存在父子关系。一个消息对应消息的处理函数（一个或多个），不存捕捉和冒泡。可以延迟发关。可以设置优先级。
//  注意和事件的区别，事件要复杂些。消息通常和简单发送执行，所以性能要高一些。
//  当然事件可以定义的很简单或遵循一定模式(dom事件模型)。
//
#ifndef YHGE_MESSAGE_MESSAGE_H_
#define YHGE_MESSAGE_MESSAGE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class Message : public Ref {

public:
    Message()
	:_type(0)
	,_sender(NULL)
	,_receiver(NULL)
	,_data(NULL)
	,_timeStamp(0.0f)
	,_extData(NULL)
	{
		
	}

    ~Message(void);
    
	bool initWithType(unsigned int type,Ref* sender ,Ref* receiver ,Ref *data){
		 _type=type;
		setSender(sender);
		setReceiver(receiver);
		setData(data);
		return true;
	}

    bool initWithType(unsigned int type,Ref* sender ,Ref* receiver){
		_type=type;
		setSender(sender);
		setReceiver(receiver);
    	return true;
	}

    bool initWithType(unsigned int type,Ref* sender){
		_type=type;
		setSender(sender);
  		return true;
	}

	unsigned int getType(){
		return _type;
	}
	void setType(unsigned int type){
	    _type=type;
	}

	Ref* getSender(){
		return _sender;
	}

	void setSender(Ref* sender){
		CC_SAFE_RETAIN(sender);
		CC_SAFE_RELEASE(_sender);
		_sender=sender;
	}

	Ref* getReceiver(){
		return _receiver;
	}

	void setReceiver(Ref* receiver){
		CC_SAFE_RETAIN(receiver);
		CC_SAFE_RELEASE(_receiver);
		_receiver=receiver;
	}
    
	Ref* getData(){
		return _data;
	}

    void setData(Ref* data){
		CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(_data);
		_data=data;
	}

	Ref* getExtData(){
		return _extData;
	}

    void setExtData(Ref* extData){
		CC_SAFE_RETAIN(extData);
		CC_SAFE_RELEASE(_extData);
		_extData=extData;
	}

private:
    unsigned int _type;//消息的类型或ID。
    Ref* _sender;//消息的发送者
	Ref* _receiver;//消息的接收者
    float _timeStamp;//发送时间
    Ref* _data;
	Ref* _extData;//附加数据。
};

NS_CC_YHGE_END

#endif  // YHGE_MESSAGE_MESSAGE_H_
