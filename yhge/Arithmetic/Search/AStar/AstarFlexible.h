/**
 * MapCellInfo由成员函数来实现
 */

#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_

#include "AstarNode.h"
#include "Astar.h"

NS_CC_YHGE_BEGIN

class AstarDelegate
{
public:

	/**
	 *检查是否可以通过
	 */
	virtual bool isWorkable(int x,int y);

};

class AstarFlexible : public Astar {
public:
	
	AstarFlexible();
	~AstarFlexible(void);

	//由具体应用实现
	bool isWorkable(int x ,int y) ;

protected:	
    
    //弱引用
	AstarDelegate* _delegate;
};

NS_CC_YHGE_END

#endif // YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_