#include "CCParabolaMove.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN


CCParabolaMove* CCParabolaMove::create(float duration,const CCPoint& speed)
{
    CCParabolaMove *pRet = new CCParabolaMove();
    pRet->initWithDuration(duration, speed);
    pRet->autorelease();
    
    return pRet;
}

bool CCParabolaMove::initWithDuration(float duration, const CCPoint& speed)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_tSpeed= speed;
        return true;
    }
    
    return false;
}

Ref* CCParabolaMove::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParabolaMove* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParabolaMove*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCParabolaMove();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_tSpeed);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParabolaMove::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_previousPosition = m_startPosition = pTarget->getPosition();
}

CCActionInterval* CCParabolaMove::reverse(void)
{
    return CCParabolaMove::create(m_fDuration, ccp( -m_tSpeed.x, -m_tSpeed.y));
}

void CCParabolaMove::step(float delta)
{
    if (m_bFirstTick)
    {
        m_bFirstTick = false;
        m_elapsed = 0;
    }
    else
    {
        m_elapsed += delta;
    }

    this->update(delta);
}

void CCParabolaMove::update(float t)
{
    if (m_pTarget)
    {
        float sx=m_tSpeed.x*m_elapsed;
        float sy=m_tSpeed.y*m_elapsed+0.5*m_fGravity*m_elapsed*m_elapsed;

        CCPoint newPos=ccp(m_startPosition.x+sx,m_startPosition.y+sy);

        m_pTarget->setPosition(newPos);
        m_previousPosition = newPos;

    }
}

CCParabolaMoveTo* CCParabolaMoveTo::create(float duration, const CCPoint &position)
{
    CCParabolaMoveTo *pRet = new CCParabolaMoveTo();
    pRet->initWithDuration(duration, position);
    pRet->autorelease();
    return pRet;
}

CCParabolaMoveTo* CCParabolaMoveTo::create(float duration, const CCPoint &position,float height)
{
    CCParabolaMoveTo *pRet = new CCParabolaMoveTo();
    pRet->initWithDuration(duration, position,height);
    pRet->autorelease();
    return pRet;
}

bool CCParabolaMoveTo::initWithDuration(float duration, const CCPoint& position)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_endPosition= position;
        m_bUseHight=false;
        return true;
    }
    
    return false;
}

bool CCParabolaMoveTo::initWithDuration(float duration, const CCPoint& position,float height)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_endPosition= position;
        m_bUseHight=true;
        m_fHeight=height;
        return true;
    }
    
    return false;
}

Ref* CCParabolaMoveTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParabolaMoveTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParabolaMoveTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCParabolaMoveTo();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCParabolaMove::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_endPosition);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParabolaMoveTo::startWithTarget(CCNode *pTarget)
{   
    
    
    CCParabolaMove::startWithTarget(pTarget);
    float sy=m_endPosition.y-m_startPosition.y;
    float sx=m_endPosition.x-m_startPosition.x;
    
    if(m_bUseHight){
        m_fGravity=-2*m_fHeight/(m_fDuration*m_fDuration);
    }

    m_tSpeed.y=sy/m_fDuration-0.5*m_fDuration*m_fGravity;
    m_tSpeed.x= sx/m_fDuration;

}

void CCParabolaMoveTo::stop()
{
    m_pTarget->setPosition(m_endPosition);
    CCParabolaMove::stop();
}

NS_CC_YHGE_END