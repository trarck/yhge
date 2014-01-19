#include "ISOCamera.h"
#include <float.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const float kVisibleMin=-3.402823466e+38F;
static const float kVisibleMax=3.402823466e+38F;

ISOCamera::ISOCamera()
:m_tWorldPosition(CCPointZero)
,m_bSmoothMove(NULL)
,m_scaleX(1.0f)
,m_scaleY(1.0f)
,m_delegate(NULL)
,m_lastScaleX(1.0f)
,m_lastScaleY(1.0f)
,m_needCheckPositionRane(true)
,m_minX(kVisibleMin)
,m_maxX(kVisibleMax)
,m_minY(kVisibleMin)
,m_maxY(kVisibleMax)
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
    m_tWorldPosition.x+=deltaX;
    m_tWorldPosition.y+=deltaY;

    this->updatePosition();
}

/**
 * 移动
 * 绝对位置
 */
void  ISOCamera::moveTo(float x,float y)
{
    m_tWorldPosition.x=x;
    m_tWorldPosition.y=y;

    this->updatePosition();

}


/**
 * 反向移动
 * 相对位置
 */
void  ISOCamera::moveOpposite(float deltaX,float deltaY)
{
    m_tWorldPosition.x-=deltaX;
    m_tWorldPosition.y-=deltaY;

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
    if (m_needCheckPositionRane)
    {
        this->modifyWorldPositionInRange();
    }

    if (m_delegate) {
        m_delegate->onCameraMove(m_tWorldPosition);
    }
//    m_pGameWorld->setPosition(m_tWorldPosition);
//    m_pGameWorld->updateMapPosition(ccp(-m_tWorldPosition.x,-m_tWorldPosition.y));
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
    m_lastScaleX=m_scaleX;
    m_lastScaleY=m_scaleY;
    
    m_scaleX+=scaleX;
    m_scaleY+=scaleY;

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
    m_lastScaleX=m_scaleX;
    m_lastScaleY=m_scaleY;
    
    m_scaleX=scaleX;
    m_scaleY=scaleY;
    
    this->updateScale();
}

/**
 * 更新缩放
 */
void ISOCamera::updateScale()
{
    //update position.新的缩放模式下的位置
    CCAssert(m_lastScaleX!=0 && m_lastScaleY!=0, "ISOCamera::updateScale neg is zero");
    
    m_tWorldPosition.x=m_tWorldPosition.x*m_scaleX/m_lastScaleY;
    m_tWorldPosition.y=m_tWorldPosition.y*m_scaleY/m_lastScaleY;
    
    if (m_needCheckPositionRane)
    {
        this->modifyWorldPositionInRange();
    }

    if (m_delegate) {
        m_delegate->onCameraScale(m_scaleX,m_scaleY);
        m_delegate->onCameraMove(m_tWorldPosition);
    }
}

/**
 * 取得屏幕坐标所在game的位置
 */
CCPoint ISOCamera::getLocationInWorld(const CCPoint& position)
{
    CCAssert(m_scaleX!=0 && m_scaleY!=0, "ISOCamera::updateScale neg is zero");
    
    float x=m_tWorldPosition.x+position.x;
    float y=m_tWorldPosition.y+position.y;

    x/=m_scaleX;
    y/=m_scaleY;

    return ccp(x,y);
}
/**
 * 设置可显示范围
 * 这里的单位是屏幕坐标系。和相机是否缩放没有关系。
 * 如果要把地图坐标转成屏幕坐标，则需要处理相机的缩放。
 */
void ISOCamera::setVisibleRange(const CCRect& rect)
{
    m_minX=rect.getMinX();
    m_minY=rect.getMinY();
    m_maxX=rect.getMaxX();
    m_maxY=rect.getMaxY();
}

/**
 * 修正移动范围是否超过显示范围
 */
CCPoint ISOCamera::modifyPositionInRange(const CCPoint& position)
{
    CCPoint newPos=position;
    newPos.x=newPos.x<m_minX?m_minX:(newPos.x>m_maxX?m_maxX:newPos.x);
    newPos.y=newPos.x<m_minY?m_minY:(newPos.y>m_maxY?m_maxY:newPos.y);
    return newPos;
}

NS_CC_YHGE_END