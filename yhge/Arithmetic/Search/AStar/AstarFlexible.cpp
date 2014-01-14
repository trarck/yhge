#include "AstarFlexible.h"
#include <yhge/CocosExt/CCGeometryValue.h>

NS_CC_YHGE_BEGIN


AstarFlexible::AstarFlexible(void)
:m_delegate(NULL)
{
	
}

AstarFlexible::~AstarFlexible(void)
{
	
}

//本身是否可以通过
bool AstarFlexible::isWorkable(int x,int y) 
{
	return m_delegate->isWorkable(x,y);
}

NS_CC_YHGE_END
