#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_

#include "GridMoveComponent.h"

NS_CC_YHGE_BEGIN

//前置声明
namespace isometric {
    class ISOCamera;
}

/**
 * 按地图的格子移动
 */
class CameraFlowGridMoveComponent : public yhge::GridMoveComponent{

public:

    CameraFlowGridMoveComponent();
    ~CameraFlowGridMoveComponent();

    /**
     * 移动动画步骤
     * 现在直接使用地图坐标
     * 以后优化使用view视图的坐标，减少坐标转换
     */
    void updateDirection( float delta);

    /**
     * 移动动画步骤
     * 通过路径移动的动画步骤
     */
    void updatePath(float delta);

    void setCamera(isometric::ISOCamera* camera)
    {
        _camera = camera;
    }

    isometric::ISOCamera* getCamera()
    {
        return _camera;
    }
    
    inline void setInnerOrigin(CCPoint innerOrigin)
    {
        _innerOrigin = innerOrigin;
    }
    
    inline CCPoint getInnerOrigin()
    {
        return _innerOrigin;
    }
    
    inline void setInnerOffset(CCSize innerOffset)
    {
        _innerOffset = innerOffset;
    }
    
    inline CCSize getInnerOffset()
    {
        return _innerOffset;
    }

protected:

    virtual void prepareMove();

    virtual void startMoveUpdateSchedule();

    /**
     * 检查是否需要移动相机
     */
    bool checkNeedMoveCamera();
    
    /**
     * 移动相机
     */
    void moveCamera(float delta);
    
protected:
    
    //相机，弱引用
    isometric::ISOCamera* _camera;

    //相机的上次位置
    CCPoint _lastCameraPosition;
    
    //相机移动时的偏移参数点。通常是屏幕的中心点。
    CCPoint _innerOrigin;
    
    //当人物的距_innerOrigin的距离，达到_innerOffset时，相机开始移动
    //注意是距离值，不是范围大小。
    CCSize _innerOffset;
    
    //标记相机是否需要移动
    bool _needMoveCamera;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_
