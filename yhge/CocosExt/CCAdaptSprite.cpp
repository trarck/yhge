#include "CCCallFuncNO.h"

NS_CC_YHGE_BEGIN

CCCallFuncNO::CCCallFuncNO()
:m_pData(NULL)
{

}

CCCallFuncNO::~CCCallFuncNO()
{
	CC_SAFE_RELEASE(m_pData);
}

CCCallFuncNO * CCCallFuncNO::actionWithTarget(CCObject* pSelectorTarget, SEL_CallFuncNO selector, CCObject* d) 
{
    return CCCallFuncNO::create(pSelectorTarget, selector, d);
}

CCCallFuncNO * CCCallFuncNO::create(CCObject* pSelectorTarget, SEL_CallFuncNO selector, CCObject* d)
{
    CCCallFuncNO* pRet = new CCCallFuncNO();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, d)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCCallFuncNO::initWithTarget(CCObject* pSelectorTarget,
        SEL_CallFuncNO selector, CCObject* d) {

	if (pSelectorTarget) 
    {
        pSelectorTarget->retain();
    }

    if (m_pSelectorTarget) 
    {
        m_pSelectorTarget->release();
    }

    m_pSelectorTarget = pSelectorTarget;

    m_pData = d;
    m_pCallFuncNO = selector;
    return true;
}

CCObject * CCCallFuncNO::copyWithZone(CCZone* zone) {
    CCZone* pNewZone = NULL;
    CCCallFuncNO* pRet = NULL;

    if (zone && zone->m_pCopyObject) {
        //in case of being called at sub class
        pRet = (CCCallFuncNO*) (zone->m_pCopyObject);
    } else {
        pRet = new CCCallFuncNO();
        zone = pNewZone = new CCZone(pRet);
    }

    CCCallFunc::copyWithZone(zone);
    pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncNO, m_pData);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCallFuncNO::execute() {
    if (m_pCallFuncNO) {
        (m_pSelectorTarget->*m_pCallFuncNO)(m_pTarget, m_pData);
    }
}
    
    
NS_CC_YHGE_END
