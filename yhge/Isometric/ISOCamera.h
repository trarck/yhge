#ifndef YHGE_ISOMETRIC_ISOCAMERA_H_
#define YHGE_ISOMETRIC_ISOCAMERA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ISOCameraMoveDelegate
{
public:
    
    /**
     * 相机移动调用
     */
    virtual void onCameraMove(const CCPoint& worldPosition)=0;
    
    /**
     * 相机移动结束调用
     */
    virtual void onCameraMoveEnd(const CCPoint& worldPosition){};
    
};

class ISOCamera: public CCObject
{
public:
	ISOCamera();
	~ISOCamera();
    bool init();  
	
    //CREATE_FUNC(ISOCamera);

    /**
     * 移动
     * 相对位置
     */
	void move(float deltaX,float deltaY);
    
    /**
     * 移动
     * 绝对位置
     */
    void moveTo(float x,float y);

    /**
     * 反向移动
     * 相对位置
     */
	void moveOpposite(float deltaX,float deltaY);
    
    /**
     * 更新坐标
     */
    void updatePosition();

    /**
     * 取得坐标所在game的位置
     */
    CCPoint getLocationInWorld(const CCPoint& position);

    inline void setSmoothMove(bool bSmoothMove)
    {
        m_bSmoothMove = bSmoothMove;
    }
    
    inline bool isSmoothMove()
    {
        return m_bSmoothMove;
    }
    
    inline void setMoveDelegate(ISOCameraMoveDelegate* moveDelegate)
    {
        m_moveDelegate = moveDelegate;
    }
    
    inline ISOCameraMoveDelegate* getMoveDelegate()
    {
        return m_moveDelegate;
    }

protected:
    /**
     * 平滑移动
     */
    bool m_bSmoothMove;
    
    /**
     * 相机所在游戏世界位置
     */
    CCPoint m_tWorldPosition;
    
    /**
     * 相机移动事件代理
     * weak reference
     */
    ISOCameraMoveDelegate* m_moveDelegate;
};

NS_CC_YHGE_END

#endif // YHGE_ISOMETRIC_ISOCAMERA_H_
