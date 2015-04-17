#include "Event.h"

NS_CC_YHGE_BEGIN

Event::Event()
:_sType("")
,_iType(0)
,_target(NULL)
,_pCurrentTarget(NULL)
,_nEventPhase(0)
,_bBubbles(true)
,_bCancelable(true)
,_nTimeStamp(0)
,_bDispatchStopped(false)
,_bNoDefault(false)
,_data(NULL)
{

}

Event::~Event()
{
    CC_SAFE_RELEASE(_target);
    CC_SAFE_RELEASE(_pCurrentTarget);
}

bool Event::initEvent(const std::string &eventType, bool canBubble, bool cancelable)
{
    _sType=eventType;
    _bBubbles=canBubble;
    _bCancelable=cancelable;
    
    _nTimeStamp=0;

    _bDispatchStopped=false;
    _bNoDefault=false;

    return true;
}

bool Event::initEvent(int eventType, bool canBubble, bool cancelable)
{
    _iType=eventType;
    _bBubbles=canBubble;
    _bCancelable=cancelable;
    
    _nTimeStamp=0;

    _bDispatchStopped=false;
    _bNoDefault=false;

    return true;
}


NS_CC_YHGE_END