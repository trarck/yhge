#include "ISOCamera.h"
#include <float.h>

USING_NS_CC;

NS_CC_YHGE_ISOMETRIC_BEGIN

static const float kVisibleMax=3.402823466e+28F;
static const float kVisibleMin=-kVisibleMax;

ISOCamera::ISOCamera()
:_tWorldPosition(CCPointZero)
,_bSmoothMove(NULL)
,_scaleX(1.0f)
,_scaleY(1.0f)
,_delegate(NULL)
,_lastScaleX(1.0f)
,_lastScaleY(1.0f)
,_needCheckPositionRane(true)
,_minX(kVisibleMin)
,_maxX(kVisibleMax)
,_minY(kVisibleMin)
,_maxY(kVisibleMax)
{
    
}

ISOCamera::~ISOCamera()
{

}

bool ISOCamera::init()
{
	return true;
}

/**
 * 移动
 * 相对位置
 */
void  ISOCamera::move(float deltaX,float deltaY)
{
    _tWorldPosition.x+=deltaX;
    _tWorldPosition.y+=deltaY;

    this->updatePosition();
}

void ISOCamera::move(const CCPoint& delta)
{
    _tWorldPosition.x+=delta.x;
    _tWorldPosition.y+=delta.y;
    
    this->updatePosition();
}

/**
 * 移动
 * 绝对位置
 */
void  ISOCamera::moveTo(float x,float y)
{
    _tWorldPosition.x=x;
    _tWorldPosition.y=y;

    this->updatePosition();

}

void ISOCamera::moveTo(const CCPoint& position)
{
    _tWorldPosition.x=position.x;
    _tWorldPosition.y=position.y;
    
    this->updatePosition();
}


/**
 * 反向移动
 * 相对位置
 */
void  ISOCamera::moveOpposite(float deltaX,float deltaY)
{
    _tWorldPosition.x-=deltaX;
    _tWorldPosition.y-=deltaY;

    this->updatePosition();
}

void ISOCamera::moveOpposite(const CCPoint& delta)
{
    _tWorldPosition.x-=delta.x;
    _tWorldPosition.y-=delta.y;
    
    this->updatePosition();
}

/**
 * 更新坐标
 */
void ISOCamera::updatePosition()
{
    //如果超出范围，修正前后的值是不一样的，没有超出，则值是一致的。
    //如果超出范围，则相机可能不会移动，所以不需要更新。
    //相机里不做判断，则由具体的delegate做判断
    if (_needCheckPositionRane)
    {
        this->modifyWorldPositionInRange();
    }

    if (_delegate) {
        _delegate->onCameraMove(_tWorldPosition);
    }
//    _pGameWorld->setPosition(_tWorldPosition);
//    _pGameWorld->updateMapPosition(ccp(-_tWorldPosition.x,-_tWorldPosition.y));
}

/**
 * 缩放
 */
void ISOCamera::scaleBy(float scale)
{
    scaleBy(scale,scale);
}

/**
 * 缩放
 */
void ISOCamera::scaleBy(float scaleX,float scaleY)
{
    _lastScaleX=_scaleX;
    _lastScaleY=_scaleY;
    
    _scaleX+=scaleX;
    _scaleY+=scaleY;

    this->updateScale();
}

/**
 * 缩放
 */
void ISOCamera::scaleTo(float scale)
{
    scaleTo(scale, scale);
}

/**
 * 缩放
 */
void ISOCamera::scaleTo(float scaleX,float scaleY)
{
    _lastScaleX=_scaleX;
    _lastScaleY=_scaleY;
    
    _scaleX=scaleX;
    _scaleY=scaleY;
    
    this->updateScale();
}

/**
 * 更新缩放
 */
void ISOCamera::updateScale()
{
    //update position.新的缩放模式下的位置
    CCAssert(_lastScaleX!=0 && _lastScaleY!=0, "ISOCamera::updateScale neg is zero");
    
    float rate=_scaleX/_lastScaleY;

    _tWorldPosition.x*=rate;
    _tWorldPosition.y*=rate;

    //重新设置移动范围的大小
    if (_needCheckPositionRane)
    {
        _minX*=rate;
        _minY*=rate;
        _maxX*=rate;
        _maxY*=rate;
    }
    
    if (_needCheckPositionRane)
    {
        this->modifyWorldPositionInRange();
    }

    if (_delegate) {
        _delegate->onCameraScale(_scaleX,_scaleY);
        _delegate->onCameraMove(_tWorldPosition);
    }
}

/**
 * 取得屏幕坐标所在game的位置
 */
CCPoint ISOCamera::getLocationInWorld(const CCPoint& position)
{
    CCAssert(_scaleX!=0 && _scaleY!=0, "ISOCamera::updateScale neg is zero");
    
    float x=_tWorldPosition.x+position.x;
    float y=_tWorldPosition.y+position.y;

    x/=_scaleX;
    y/=_scaleY;

    return ccp(x,y);
}

/**
 * 取得game的位置在屏幕坐标所
 */
CCPoint ISOCamera::getLocationInScene(const CCPoint& position)
{
    float x=position.x*_scaleX-_tWorldPosition.x;
    float y=position.y*_scaleY-_tWorldPosition.y;

    //x*=_scaleX;
    //y*=_scaleY;

    return ccp(x,y);
}

/**
 * 设置可移动范围
 * 这里的单位是屏幕坐标系。和相机是否缩放没有关系。
 * 如果要把地图坐标转成屏幕坐标，则需要处理相机的缩放。
 */
void ISOCamera::setMoveRange(const CCRect& rect)
{
    _minX=rect.getMinX();
    _minY=rect.getMinY();
    _maxX=rect.getMaxX();
    _maxY=rect.getMaxY();
}

/**
 * 修正移动范围是否超过移动范围
 */
CCPoint ISOCamera::modifyPositionInRange(const CCPoint& position)
{
    CCPoint newPos=position;
    newPos.x=newPos.x<_minX?_minX:(newPos.x>_maxX?_maxX:newPos.x);
    newPos.y=newPos.y<_minY?_minY:(newPos.y>_maxY?_maxY:newPos.y);
    return newPos;
}

NS_CC_YHGE_ISOMETRIC_END