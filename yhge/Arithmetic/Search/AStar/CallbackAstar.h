/**
 * MapCellInfo由成员函数来实现
 */

#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_CALLBACKASTAR_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_CALLBACKASTAR_H_

#include "AstarNode.h"
#include "Astar.h"

NS_CC_YHGE_BEGIN


typedef bool (CCObject::*SEL_CheckWorkableHandler)(int x,int y);
#define check_workable_selector(_SELECTOR) (SEL_CheckWorkableHandler)(&_SELECTOR)

/**
 * 使用回调函数进行障碍物判断
 * 使用继承，速度大概下降了8%。
 */
class CallbackAstar : public Astar {
public:
	
	CallbackAstar();
	~CallbackAstar(void);

	//由具体应用实现
	bool isWorkable(int x ,int y) ;

	void setCheckBarrierHandle(SEL_CheckWorkableHandler checkWorkableHandle,CCObject* target);

protected:
	
	//检查是否可通过的具体对像和方法。都是若引用
	SEL_CheckWorkableHandler m_checkWorkableHandle;
	CCObject* m_checkWorkableTarget;
};

NS_CC_YHGE_END

#endif // YHGE_ARITHMETIC_SEARCH_ASTAR_CALLBACKASTAR_H_