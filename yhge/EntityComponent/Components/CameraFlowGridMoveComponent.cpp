/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "CameraFlowGridMoveComponent.h"
#include <yhge/Isometric/ISOCamera.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const CCSize kDefaultInnerOffsetSize=CCSizeMake(64.0f, 32.0f);

/**
 * 按地图的格子移动
 * 每次移动一个格子的距离
 * 原始数据使用地图坐标，移动过程(动画)使用屏幕坐标
 */
CameraFlowGridMoveComponent::CameraFlowGridMoveComponent()
:m_camera(NULL)
,m_lastCameraPosition(CCPointZero)
,m_innerOrigin(CCPointZero)
,m_innerOffsetSize(kDefaultInnerOffsetSize)
,m_needMoveCamera(false)
{
    CCLOG("CameraFlowGridMoveComponent create");
	m_name="GridMoveComponent";
}

CameraFlowGridMoveComponent::~CameraFlowGridMoveComponent()
{
    CCLOG("CameraFlowGridMoveComponent destroy");
}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void CameraFlowGridMoveComponent::updateDirection( float delta)
{
     GridMoveComponent::updateDirection(delta);
}

/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void CameraFlowGridMoveComponent::updatePath(float delta)
{
//    CCPoint scenePos=m_camera->getLocationInScene(m_rendererComponent->getRenderer()->getPosition());
    //CCLOG("scene:%f,%f",scenePos.x,scenePos.y);

//    CCLOG("dd %f,%f",m_camera->getWorldPosition().x,m_camera->getWorldPosition().y);
    
    if (m_needMoveCamera)
    {
        //CCLOG("needMoveCamera:%f,%f:%f,%f",scenePos.x,scenePos.y,m_rendererComponent->getRenderer()->getPosition().x,m_rendererComponent->getRenderer()->getPosition().y);

        float duration=m_movingDuration;
        float movingDelta=m_movingDeltaTime+delta;

        if(movingDelta<duration){
            float scale=m_camera->getScale();
            m_camera->move(scale*delta*m_fViewSpeedX,scale*delta*m_fViewSpeedY);
//            CCLOG("aa %f,%f",m_camera->getWorldPosition().x,m_camera->getWorldPosition().y);
        }else{
            float scale=m_camera->getScale();
            float endX=m_lastCameraPosition.x+scale*duration*m_fViewSpeedX;
            float endY=m_lastCameraPosition.y+scale*duration*m_fViewSpeedY;
            m_lastCameraPosition.x=endX;
            m_lastCameraPosition.y=endY;
            m_camera->moveTo(endX,endY);
//            CCLOG("bb %f,%f",endX,endY);
        }
    }

    //update 放在后面，否则一些状态会改变如m_movingDeltaTime，m_movingDeltaTime，m_fViewSpeedX
    GridMoveComponent::updatePath(delta);
}

void CameraFlowGridMoveComponent::prepareMove()
{
    GridMoveComponent::prepareMove();
    if(this->checkNeedMoveCamera()){
        m_lastCameraPosition=m_camera->getWorldPosition();
//        CCLOG("cc %f,%f",m_lastCameraPosition.x,m_lastCameraPosition.y);
    }
}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void CameraFlowGridMoveComponent::startMoveUpdateSchedule()
{
    switch (m_moveType)
    {
    case kMoveDirection:
        m_update=schedule_selector(CameraFlowGridMoveComponent::updateDirection);
        break;
    case kMovePath:
        m_update=schedule_selector(CameraFlowGridMoveComponent::updatePath);
        break;
    default:
        break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(m_update,this, 0, false);
}

//void CameraFlowGridMoveComponent::stopMoveUpdateSchedule()
//{
//    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(m_update,this);
//    m_update=NULL;
//}

bool CameraFlowGridMoveComponent::checkNeedMoveCamera()
{
    CCPoint scenePos=m_camera->getLocationInScene(m_rendererComponent->getRenderer()->getPosition());
    
    bool needMoveCamera=false;
    
    float offsetX=scenePos.x-m_innerOrigin.x;
    
    if (m_fViewSpeedX>0){
        needMoveCamera=offsetX>=m_innerOffsetSize.width;
    }else if (m_fViewSpeedX<0){
        needMoveCamera=offsetX<=-m_innerOffsetSize.width;
    }
    
    if (!needMoveCamera)
    {
        float offsetY=scenePos.y-m_innerOrigin.y;
        
        if (m_fViewSpeedY>0){
            needMoveCamera=offsetY>=m_innerOffsetSize.height;
        }else if (m_fViewSpeedY<0){
            needMoveCamera=offsetY<=-m_innerOffsetSize.height;
        }
    }
    
    m_needMoveCamera=needMoveCamera;

    return needMoveCamera;
}

NS_CC_YHGE_END
