#include "AstarFlexible.h"
#include <yhge/CocosExt/CCGeometryValue.h>

NS_CC_YHGE_BEGIN


AstarFlexible::AstarFlexible(void)
:_delegate(NULL)
{
	
}

AstarFlexible::~AstarFlexible(void)
{
	
}

//本身是否可以通过
bool AstarFlexible::isWorkable(int x,int y) 
{
	return _delegate->isWorkable(x,y);
}

NS_CC_YHGE_END
