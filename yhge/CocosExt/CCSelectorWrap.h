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
        :m_pTarget(NULL)
		,m_selector(NULL)
        ,m_data(NULL)
	{

	}

    ~CCSelectorWrap();

	inline bool initWithTarget(Ref* pTarget,SEL_SelectorWrapD selector,Ref* data)
	{
		setTarget(pTarget);
		m_selector=selector;
        setData(data);
		return true;
	}
    

    inline void execute(){
        if(m_selector){
		    (m_pTarget->*m_selector)(m_data);
	    }
    }

    inline Ref* getTarget()
	{
		return m_pTarget;
	}

	inline void setTarget(Ref* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(m_pTarget);
		m_pTarget=pTarget;
	}

	inline SEL_SelectorWrapD getSelector()
	{
		return m_selector;
	}

	inline void setSelector(SEL_SelectorWrapD selector)
	{
		m_selector=selector;
	}

    inline void setData(Ref* data)
    {
        CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_data);
        m_data=data;
    }

    inline Ref* getData()
    {
        return m_data;
    }

protected:
	Ref* m_pTarget;
	SEL_SelectorWrapD m_selector;
    Ref* m_data;
};

NS_CC_YHGE_END

#endif  // YHGE_COCOSEXT_CCSELECTORWRAP_H_
