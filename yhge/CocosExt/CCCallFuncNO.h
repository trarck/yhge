#ifndef YHGE_COCOSEXT_CCCALLFUNCNO_H_
#define YHGE_COCOSEXT_CCCALLFUNCNO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

typedef void (Ref::*SEL_CallFuncNO)(Node*, Ref*);
#define callfuncNO_selector(_SELECTOR) (SEL_CallFuncNO)(&_SELECTOR)

/**
 * 加入对call function ccobject作为参数的支持
 */
class CCCallFuncNO : public CCCallFuncN
{
public:
    virtual long getClassTypeInfo() {
        static const long id = cocos2d::getHashCodeByString(typeid(CCCallFunc).name());
		return id;
    }

	CCCallFuncNO();
	~CCCallFuncNO();
    /** creates the action with the callback and the data to pass as an argument 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCCallFuncNO * actionWithTarget(Ref* pSelectorTarget, SEL_CallFuncNO selector, Ref* d);

    /** creates the action with the callback and the data to pass as an argument */
    static CCCallFuncNO * create(Ref* pSelectorTarget, SEL_CallFuncNO selector, Ref* d);

    /** initializes the action with the callback and the data to pass as an argument */
    virtual bool initWithTarget(Ref* pSelectorTarget, SEL_CallFuncNO selector, Ref* d);
    // super methods
    virtual Ref* copyWithZone(CCZone *pZone);
    virtual void execute();

protected:
    Ref            *_data;
	SEL_CallFuncNO _pCallFuncNO;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCCALLFUNCNO_H_
