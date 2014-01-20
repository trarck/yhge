#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_

#include "GridMoveComponent.h"

NS_CC_YHGE_BEGIN

class ISOCamera;

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

    void setCamera(ISOCamera* camera)
    {
        m_camera = camera;
    }

    ISOCamera* getCamera()
    {
        return m_camera;
    }
    
    inline void setInnerOrigin(CCPoint innerOrigin)
    {
        m_innerOrigin = innerOrigin;
    }
    
    inline CCPoint getInnerOrigin()
    {
        return m_innerOrigin;
    }
    
    inline void setInnerOffsetSize(CCSize innerOffsetSize)
    {
        m_innerOffsetSize = innerOffsetSize;
    }
    
    inline CCSize getInnerOffsetSize()
    {
        return m_innerOffsetSize;
    }

protected:

    virtual void prepareMove();

    virtual void startMoveUpdateSchedule();

    /**
     * 检查是否需要移动相机
     */
    bool checkNeedMoveCamera();
    
protected:
    
    //相机，弱引用
    ISOCamera* m_camera;

    //相机的上次位置
    CCPoint m_lastCameraPosition;
    
    //相机移动时的偏移参数点。通常是屏幕的中心点。
    CCPoint m_innerOrigin;
    
    //当人物的距m_innerOrigin的距离，达到m_innerOffsetSize时，相机开始移动
    CCSize m_innerOffsetSize;
    
    //标记相机是否需要移动
    bool m_needMoveCamera;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_CAMERAFLOWGRIDMOVECOMPONENT_H_
