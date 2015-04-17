#ifndef YHGE_EVENT_EVENT_H_
#define YHGE_EVENT_EVENT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

enum EventPhase{
    CAPTURING_PHASE=1,
    AT_TARGET,
    BUBBLING_PHASE
};

class Event:public Ref
{
public:

    Event();
    ~Event(void);

    bool initEvent(const std::string &eventType, bool canBubble, bool cancelable);

    inline bool initEvent(const std::string &eventType){
        return initEvent(eventType,true,true);
    }
	
    bool initEvent(int eventType, bool canBubble, bool cancelable);

    inline bool initEvent(int eventType){
        return initEvent(eventType,true,true);
    }
    
    inline void stopPropagation() {
        _bDispatchStopped=true;
    }

    inline void preventDefault(){
       _bNoDefault=true;
    }

    inline bool isDispatchStopped() {
       return !_bBubbles || (_bBubbles & _bDispatchStopped);
    }

    inline bool getPreventDefault() {
        return _bCancelable && _bNoDefault;
    }

    inline void setType(const std::string& type)
    {
        _sType=type;
    }

    inline const std::string& getType()
    {
        return _sType;
    }
	
    inline const std::string& getStrType()
    {
        return _sType;
    }
	
    inline void setType(int type)
    {
        _iType=type;
    }

    inline int getIntType()
    {
        return _iType;
    }

    inline void setTarget(Node* pTarget)
    {
        CC_SAFE_RETAIN(pTarget);
        CC_SAFE_RELEASE(_target);
        _target = pTarget;
    }

    inline Node* getTarget()
    {
        return _target;
    }

    inline void setCurrentTarget(Node* pCurrentTarget)
    {
        CC_SAFE_RETAIN(pCurrentTarget);
        CC_SAFE_RELEASE(_pCurrentTarget);
        _pCurrentTarget = pCurrentTarget;
    }

    inline Node* getCurrentTarget()
    {
        return _pCurrentTarget;
    }

    inline void setEventPhase(int nEventPhase)
    {
        _nEventPhase = nEventPhase;
    }

    inline int getEventPhase()
    {
        return _nEventPhase;
    }

    inline void setBubbles(bool bBubbles)
    {
        _bBubbles = bBubbles;
    }

    inline bool getBubbles()
    {
        return _bBubbles;
    }

    inline void setCancelable(bool bCancelable)
    {
        _bCancelable = bCancelable;
    }

    inline bool getCancelable()
    {
        return _bCancelable;
    }

    inline void setTimeStamp(int nTimeStamp)
    {
        _nTimeStamp = nTimeStamp;
    }

    inline int getTimeStamp()
    {
        return _nTimeStamp;
    }

	void setData(Ref* data)
    {
        CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(_data);
        _data=data;
    }

    inline Ref* getData()
    {
        return _data;
    }

protected:
    /**event string 类型*/
    std::string _sType;
	
    /**event int 类型*/
    int _iType;
	
    /**event目标*/
    Node* _target;
    /**event 当前处理目标*/
    Node* _pCurrentTarget;
    /**
     * event 处理的阶段
     */
    int _nEventPhase;
    /**event允许冒泡*/
    bool _bBubbles;
    /**event是否可以取消，用于取消默认操作的执行*/
    bool _bCancelable;
    /**event时间戳。精确到毫秒*/
    int _nTimeStamp;

    /**是否停止冒泡*/
    bool _bDispatchStopped;

    /**是否执行默认方法*/
    bool _bNoDefault;

    /**event数据*/
	Ref* _data;
};

typedef yhge::Event YHEvent;

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENT_H_