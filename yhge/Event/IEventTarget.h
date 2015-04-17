#ifndef YHGE_EVENT_IEVENTTARGET_H_
#define YHGE_EVENT_IEVENTTARGET_H_

#include "EventListenerManager.h"

NS_CC_YHGE_BEGIN

class IEventTarget
{
public:

    virtual void addEventListener(const char* type,Ref* handleObject,yhge::SEL_EventHandle handle)=0;
    
    virtual void removeEventListener(const char* type,Ref* handleObject,yhge::SEL_EventHandle handle) =0;

    virtual CCArray* getEventListeners(const char*type)=0;

    virtual void dispatchEvent(yhge::Event event)=0;

    virtual void trigger(const char*type,Ref*data,bool bubbles)=0;
};

NS_CC_YHGE_END

#endif //YHGE_EVENT_IEVENTTARGET_H_