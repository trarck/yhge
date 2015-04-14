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
        m_bDispatchStopped=true;
    }

    inline void preventDefault(){
       m_bNoDefault=true;
    }

    inline bool isDispatchStopped() {
       return !m_bBubbles || (m_bBubbles & m_bDispatchStopped);
    }

    inline bool getPreventDefault() {
        return m_bCancelable && m_bNoDefault;
    }

    inline void setType(const std::string& type)
    {
        m_sType=type;
    }

    inline const std::string& getType()
    {
        return m_sType;
    }
	
    inline const std::string& getStrType()
    {
        return m_sType;
    }
	
    inline void setType(int type)
    {
        m_iType=type;
    }

    inline int getIntType()
    {
        return m_iType;
    }

    inline void setTarget(CCNode* pTarget)
    {
        CC_SAFE_RETAIN(pTarget);
        CC_SAFE_RELEASE(m_pTarget);
        m_pTarget = pTarget;
    }

    inline CCNode* getTarget()
    {
        return m_pTarget;
    }

    inline void setCurrentTarget(CCNode* pCurrentTarget)
    {
        CC_SAFE_RETAIN(pCurrentTarget);
        CC_SAFE_RELEASE(m_pCurrentTarget);
        m_pCurrentTarget = pCurrentTarget;
    }

    inline CCNode* getCurrentTarget()
    {
        return m_pCurrentTarget;
    }

    inline void setEventPhase(int nEventPhase)
    {
        m_nEventPhase = nEventPhase;
    }

    inline int getEventPhase()
    {
        return m_nEventPhase;
    }

    inline void setBubbles(bool bBubbles)
    {
        m_bBubbles = bBubbles;
    }

    inline bool getBubbles()
    {
        return m_bBubbles;
    }

    inline void setCancelable(bool bCancelable)
    {
        m_bCancelable = bCancelable;
    }

    inline bool getCancelable()
    {
        return m_bCancelable;
    }

    inline void setTimeStamp(int nTimeStamp)
    {
        m_nTimeStamp = nTimeStamp;
    }

    inline int getTimeStamp()
    {
        return m_nTimeStamp;
    }

	void setData(Ref* data)
    {
        CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_pData);
        m_pData=data;
    }

    inline Ref* getData()
    {
        return m_pData;
    }

protected:
    /**event string 类型*/
    std::string m_sType;
	
    /**event int 类型*/
    int m_iType;
	
    /**event目标*/
    CCNode* m_pTarget;
    /**event 当前处理目标*/
    CCNode* m_pCurrentTarget;
    /**
     * event 处理的阶段
     */
    int m_nEventPhase;
    /**event允许冒泡*/
    bool m_bBubbles;
    /**event是否可以取消，用于取消默认操作的执行*/
    bool m_bCancelable;
    /**event时间戳。精确到毫秒*/
    int m_nTimeStamp;

    /**是否停止冒泡*/
    bool m_bDispatchStopped;

    /**是否执行默认方法*/
    bool m_bNoDefault;

    /**event数据*/
	Ref* m_pData;
};

typedef yhge::Event YHEvent;

NS_CC_YHGE_END

#endif  // YHGE_EVENT_EVENT_H_