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
        _tSpeed= speed;
        return true;
    }
    
    return false;
}

Ref* CCParabolaMove::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParabolaMove* pCopy = NULL;
    if(pZone && pZone->_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParabolaMove*)(pZone->_pCopyObject);
    }
    else
    {
        pCopy = new CCParabolaMove();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(_fDuration, _tSpeed);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParabolaMove::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

CCActionInterval* CCParabolaMove::reverse(void)
{
    return CCParabolaMove::create(_fDuration, ccp( -_tSpeed.x, -_tSpeed.y));
}

void CCParabolaMove::step(float delta)
{
    if (_bFirstTick)
    {
        _bFirstTick = false;
        _elapsed = 0;
    }
    else
    {
        _elapsed += delta;
    }

    this->update(delta);
}

void CCParabolaMove::update(float t)
{
    if (_pTarget)
    {
        float sx=_tSpeed.x*_elapsed;
        float sy=_tSpeed.y*_elapsed+0.5*_fGravity*_elapsed*_elapsed;

        CCPoint newPos=ccp(_startPosition.x+sx,_startPosition.y+sy);

        _pTarget->setPosition(newPos);
        _previousPosition = newPos;

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
        _endPosition= position;
        _bUseHight=false;
        return true;
    }
    
    return false;
}

bool CCParabolaMoveTo::initWithDuration(float duration, const CCPoint& position,float height)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endPosition= position;
        _bUseHight=true;
        _fHeight=height;
        return true;
    }
    
    return false;
}

Ref* CCParabolaMoveTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCParabolaMoveTo* pCopy = NULL;
    if(pZone && pZone->_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCParabolaMoveTo*)(pZone->_pCopyObject);
    }
    else
    {
        pCopy = new CCParabolaMoveTo();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCParabolaMove::copyWithZone(pZone);
    
    pCopy->initWithDuration(_fDuration, _endPosition);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCParabolaMoveTo::startWithTarget(CCNode *pTarget)
{   
    
    
    CCParabolaMove::startWithTarget(pTarget);
    float sy=_endPosition.y-_startPosition.y;
    float sx=_endPosition.x-_startPosition.x;
    
    if(_bUseHight){
        _fGravity=-2*_fHeight/(_fDuration*_fDuration);
    }

    _tSpeed.y=sy/_fDuration-0.5*_fDuration*_fGravity;
    _tSpeed.x= sx/_fDuration;

}

void CCParabolaMoveTo::stop()
{
    _pTarget->setPosition(_endPosition);
    CCParabolaMove::stop();
}

NS_CC_YHGE_END