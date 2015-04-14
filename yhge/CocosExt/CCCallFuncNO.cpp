#include "CCCallFuncNO.h"

NS_CC_YHGE_BEGIN

CCCallFuncNO::CCCallFuncNO()
:_pData(NULL)
{

}

CCCallFuncNO::~CCCallFuncNO()
{
	CC_SAFE_RELEASE(_pData);
}

CCCallFuncNO * CCCallFuncNO::actionWithTarget(Ref* pSelectorTarget, SEL_CallFuncNO selector, Ref* d) 
{
    return CCCallFuncNO::create(pSelectorTarget, selector, d);
}

CCCallFuncNO * CCCallFuncNO::create(Ref* pSelectorTarget, SEL_CallFuncNO selector, Ref* d)
{
    CCCallFuncNO* pRet = new CCCallFuncNO();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, d)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCCallFuncNO::initWithTarget(Ref* pSelectorTarget,
        SEL_CallFuncNO selector, Ref* d) {

	if (pSelectorTarget) 
    {
        pSelectorTarget->retain();
    }

    if (_pSelectorTarget) 
    {
        _pSelectorTarget->release();
    }

    _pSelectorTarget = pSelectorTarget;

    _pData = d;
    _pCallFuncNO = selector;
    return true;
}

Ref * CCCallFuncNO::copyWithZone(CCZone* zone) {
    CCZone* pNewZone = NULL;
    CCCallFuncNO* pRet = NULL;

    if (zone && zone->_pCopyObject) {
        //in case of being called at sub class
        pRet = (CCCallFuncNO*) (zone->_pCopyObject);
    } else {
        pRet = new CCCallFuncNO();
        zone = pNewZone = new CCZone(pRet);
    }

    CCCallFunc::copyWithZone(zone);
    pRet->initWithTarget(_pSelectorTarget, _pCallFuncNO, _pData);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCallFuncNO::execute() {
    if (_pCallFuncNO) {
        (_pSelectorTarget->*_pCallFuncNO)(_pTarget, _pData);
    }
}
    
    
NS_CC_YHGE_END
