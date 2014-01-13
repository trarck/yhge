#include "ISOCamera.h"
#include "ISOCoordinateLayer.h"


USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOCamera::ISOCamera()
:m_tWorldPosition(CCPointZero)
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
    m_tWorldPosition.x-=deltaX;
    m_tWorldPosition.y-=deltaY;

    this->updatePosition();
}

/**
 * 移动
 * 绝对位置
 */
void  ISOCamera::moveTo(float x,float y)
{
    m_tWorldPosition.x=-x;
    m_tWorldPosition.y=-y;

    this->updatePosition();

}


/**
 * 反向移动
 * 相对位置
 */
void  ISOCamera::moveOpposite(float deltaX,float deltaY)
{
    m_tWorldPosition.x+=deltaX;
    m_tWorldPosition.y+=deltaY;

    this->updatePosition();
}

/**
 * 更新坐标
 */
void ISOCamera::updatePosition()
{
    if (m_moveDelegate) {
        m_moveDelegate->onCameraMove(m_tWorldPosition);
    }
//    m_pGameWorld->setPosition(m_tWorldPosition);
//    m_pGameWorld->updateMapPosition(ccp(-m_tWorldPosition.x,-m_tWorldPosition.y));
}

/**
 * 取得坐标所在game的位置
 */
CCPoint  ISOCamera::getLocationInWorld(const CCPoint& position)
{
    return ccp(position.x-m_tWorldPosition.x,position.y-m_tWorldPosition.y);
}


NS_CC_YHGE_END