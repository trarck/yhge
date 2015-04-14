#include "CallbackAstar.h"
#include <yhge/CocosExt/CCGeometryValue.h>

NS_CC_YHGE_BEGIN

CallbackAstar::CallbackAstar(void)
:_checkWorkableHandle(NULL)
,_checkWorkableTarget(NULL)
{
	
}

CallbackAstar::~CallbackAstar(void)
{
	
}

//本身是否可以通过
bool CallbackAstar::isWorkable(int x,int y) 
{
	return (_checkWorkableTarget->*_checkWorkableHandle)(x,y);
}

void  CallbackAstar::setCheckBarrierHandle(SEL_CheckWorkableHandler checkWorkableHandle,Ref* target)
{
	_checkWorkableHandle=checkWorkableHandle;
	_checkWorkableTarget=target;
}

NS_CC_YHGE_END
