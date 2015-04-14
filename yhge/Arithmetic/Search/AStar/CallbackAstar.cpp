#include "CallbackAstar.h"
#include <yhge/CocosExt/CCGeometryValue.h>

NS_CC_YHGE_BEGIN

CallbackAstar::CallbackAstar(void)
:m_checkWorkableHandle(NULL)
,m_checkWorkableTarget(NULL)
{
	
}

CallbackAstar::~CallbackAstar(void)
{
	
}

//本身是否可以通过
bool CallbackAstar::isWorkable(int x,int y) 
{
	return (m_checkWorkableTarget->*m_checkWorkableHandle)(x,y);
}

void  CallbackAstar::setCheckBarrierHandle(SEL_CheckWorkableHandler checkWorkableHandle,Ref* target)
{
	m_checkWorkableHandle=checkWorkableHandle;
	m_checkWorkableTarget=target;
}

NS_CC_YHGE_END
