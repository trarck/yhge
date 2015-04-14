#ifndef YHGE_COCOSEXT_CCSELECTORWRAP_H_
#define YHGE_COCOSEXT_CCSELECTORWRAP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

typedef void (Ref::*SEL_SelectorWrapD)(Ref* data);
#define WRAPD_SELECTOR(_SELECTOR) (SEL_SelectorWrapD)(&_SELECTOR)

class CCSelectorWrap : public Ref {
public:
    
	inline CCSelectorWrap()
        :_pTarget(NULL)
		,_selector(NULL)
        ,_data(NULL)
	{

	}

    ~CCSelectorWrap();

	inline bool initWithTarget(Ref* pTarget,SEL_SelectorWrapD selector,Ref* data)
	{
		setTarget(pTarget);
		_selector=selector;
        setData(data);
		return true;
	}
    

    inline void execute(){
        if(_selector){
		    (_pTarget->*_selector)(_data);
	    }
    }

    inline Ref* getTarget()
	{
		return _pTarget;
	}

	inline void setTarget(Ref* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(_pTarget);
		_pTarget=pTarget;
	}

	inline SEL_SelectorWrapD getSelector()
	{
		return _selector;
	}

	inline void setSelector(SEL_SelectorWrapD selector)
	{
		_selector=selector;
	}

    inline void setData(Ref* data)
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
	Ref* _pTarget;
	SEL_SelectorWrapD _selector;
    Ref* _data;
};

NS_CC_YHGE_END

#endif  // YHGE_COCOSEXT_CCSELECTORWRAP_H_
