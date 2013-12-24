#ifndef YHGE_COCOSEXT_CCSELECTORWRAP_H_
#define YHGE_COCOSEXT_CCSELECTORWRAP_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

typedef void (CCObject::*SEL_SelectorWrapD)(CCObject* data);
#define WRAPD_SELECTOR(_SELECTOR) (SEL_SelectorWrapD)(&_SELECTOR)

class CCSelectorWrap : public CCObject {
public:
    
	inline CCSelectorWrap()
        :m_pTarget(NULL)
		,m_selector(NULL)
        ,m_data(NULL)
	{

	}

    ~CCSelectorWrap();

	inline bool initWithTarget(CCObject* pTarget,SEL_SelectorWrapD selector,CCObject* data)
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

    inline CCObject* getTarget()
	{
		return m_pTarget;
	}

	inline void setTarget(CCObject* pTarget)
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

    inline void setData(CCObject* data)
    {
        CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_data);
        m_data=data;
    }

    inline CCObject* getData()
    {
        return m_data;
    }

protected:
	CCObject* m_pTarget;
	SEL_SelectorWrapD m_selector;
    CCObject* m_data;
};

NS_CC_YHGE_END

#endif  // YHGE_COCOSEXT_CCSELECTORWRAP_H_
