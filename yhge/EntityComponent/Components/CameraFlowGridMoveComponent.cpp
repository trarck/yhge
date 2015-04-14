/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "CameraFlowGridMoveComponent.h"
#include <yhge/Isometric/ISOCamera.h>

USING_NS_CC;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_YHGE_BEGIN

static const CCSize kDefaultInnerOffset=CCSizeMake(64.0f, 32.0f);

/**
 * 按地图的格子移动
 * 每次移动一个格子的距离
 * 原始数据使用地图坐标，移动过程(动画)使用屏幕坐标
 */
CameraFlowGridMoveComponent::CameraFlowGridMoveComponent()
:_camera(NULL)
,_lastCameraPosition(CCPointZero)
,_innerOrigin(CCPointZero)
,_innerOffset(kDefaultInnerOffset)
,_needMoveCamera(false)
{
	_name="GridMoveComponent";
}

CameraFlowGridMoveComponent::~CameraFlowGridMoveComponent()
{

}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void CameraFlowGridMoveComponent::updateDirection( float delta)
{
    if (_needMoveCamera)
    {
        this->moveCamera(delta);
    }
    GridMoveComponent::updateDirection(delta);
}

/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void CameraFlowGridMoveComponent::updatePath(float delta)
{
//    CCPoint scenePos=_camera->getLocationInScene(_rendererComponent->getRenderer()->getPosition());
    //CCLOG("scene:%f,%f",scenePos.x,scenePos.y);

//    CCLOG("dd %f,%f",_camera->getWorldPosition().x,_camera->getWorldPosition().y);
    
    if (_needMoveCamera)
    {
        this->moveCamera(delta);
    }

    //update 放在后面，否则一些状态会改变如_movingDeltaTime，_movingDeltaTime，_fViewSpeedX
    GridMoveComponent::updatePath(delta);
}

void CameraFlowGridMoveComponent::prepareMove()
{
    GridMoveComponent::prepareMove();
    if(this->checkNeedMoveCamera()){
        _lastCameraPosition=_camera->getWorldPosition();
//        CCLOG("cc %f,%f",_lastCameraPosition.x,_lastCameraPosition.y);
    }
}

//开启更新定时器。为了使update不是虚函数，这里使用虚函数
void CameraFlowGridMoveComponent::startMoveUpdateSchedule()
{
    switch (_moveType)
    {
    case kMoveDirection:
        _update=schedule_selector(CameraFlowGridMoveComponent::updateDirection);
        break;
    case kMovePath:
        _update=schedule_selector(CameraFlowGridMoveComponent::updatePath);
        break;
    default:
        break;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(_update,this, 0, false);
}

//void CameraFlowGridMoveComponent::stopMoveUpdateSchedule()
//{
//    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(_update,this);
//    _update=NULL;
//}

bool CameraFlowGridMoveComponent::checkNeedMoveCamera()
{
//    CCPoint scenePos=_camera->getLocationInScene(_rendererComponent->getRenderer()->getPosition());
     CCPoint scenePos=_camera->getLocationInScene(_isoPositionComponent->getRendererPosition());
    
    bool needMoveCamera=false;
    
    float offsetX=scenePos.x-_innerOrigin.x;
    
    if (_fViewSpeedX>0){
        needMoveCamera=offsetX>=_innerOffset.width;
    }else if (_fViewSpeedX<0){
        needMoveCamera=offsetX<=-_innerOffset.width;
    }
    
    if (!needMoveCamera)
    {
        float offsetY=scenePos.y-_innerOrigin.y;
        
        if (_fViewSpeedY>0){
            needMoveCamera=offsetY>=_innerOffset.height;
        }else if (_fViewSpeedY<0){
            needMoveCamera=offsetY<=-_innerOffset.height;
        }
    }
    
    _needMoveCamera=needMoveCamera;

    return needMoveCamera;
}

/**
 * 移动相机
 */
void CameraFlowGridMoveComponent::moveCamera(float delta)
{
    //CCLOG("needMoveCamera:%f,%f:%f,%f",scenePos.x,scenePos.y,_rendererComponent->getRenderer()->getPosition().x,_rendererComponent->getRenderer()->getPosition().y);
    
    float duration=_movingDuration;
    float movingDelta=_movingDeltaTime+delta;
    
    if(movingDelta<duration){
        float scale=_camera->getScale();
        _camera->move(scale*delta*_fViewSpeedX,scale*delta*_fViewSpeedY);
        //CCLOG("aa %f,%f",_camera->getWorldPosition().x,_camera->getWorldPosition().y);
    }else{
        float scale=_camera->getScale();
        float endX=_lastCameraPosition.x+scale*duration*_fViewSpeedX;
        float endY=_lastCameraPosition.y+scale*duration*_fViewSpeedY;
        
//        float dx=endX-_lastCameraPosition.x;
//        float dy=endY-_lastCameraPosition.y;
        
        _lastCameraPosition.x=endX;
        _lastCameraPosition.y=endY;

        //不能使用delta，好象有问题。
        
//        _camera->move(dx, dy);
        _camera->moveTo(endX,endY);
        //CCLOG("bb %f,%f",endX,endY);
    }
}

NS_CC_YHGE_END
