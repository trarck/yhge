#ifndef YHGE_ISOMETRIC_ISOCAMERA_H_
#define YHGE_ISOMETRIC_ISOCAMERA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ISOCameraDelegate
{
public:
    
    /**
     * 相机移动
     * worldPosition是相机所在的世界坐标
     */
    virtual void onCameraMove(const CCPoint& worldPosition)=0;
    
    /**
     * 相机移动结束
     * worldPosition是相机所在的世界坐标
     */
    virtual void onCameraMoveEnd(const CCPoint& worldPosition){};
    
    /**
     * 相机缩放
     * scaleX,scaleY是相机的缩放值
     */
    virtual void onCameraScale(float scaleX,float scaleY){};
    
    /**
     * 相机缩放结束
     * scaleX,scaleY是相机的缩放值
     */
    virtual void onCameraScaleEnd(float scaleX,float scaleY){};
    
};


/**
 * 相机
 * 分为二种：1.不处理缩放，缩放交给游戏世界处理
 *         2.处理绽放，并需要游戏世界配合。
 */
class ISOCamera: public CCObject
{
public:
	ISOCamera();
	~ISOCamera();
    bool init();  
	
    //CREATE_FUNC(ISOCamera);

    /**
     * 移动
     * 相对位置，屏幕坐标系的值。
     */
	void move(float deltaX,float deltaY);
    
    /**
     * 移动
     * 绝对位置，屏幕坐标系的值。
     */
    void moveTo(float x,float y);

    /**
     * 反向移动
     * 相对位置
     * 移动相机，其实在反向移动游戏世界
     */
	void moveOpposite(float deltaX,float deltaY);
    
    /**
     * 更新坐标
     */
    void updatePosition();
    
    /**
     * 缩放
     */
    void scaleBy(float scale);
    
    /**
     * 缩放
     */
    void scaleBy(float scaleX,float scaleY);
    
    /**
     * 缩放
     */
    void scaleTo(float scale);
    
    /**
     * 缩放
     */
    void scaleTo(float scaleX,float scaleY);
    
    /**
     * 更新缩放
     */
    void updateScale();

    /**
     * 取得屏幕坐标所在game的位置
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
    
    inline void setMoveDelegate(ISOCameraDelegate* moveDelegate)
    {
        m_delegate = moveDelegate;
    }
    
    inline ISOCameraDelegate* getMoveDelegate()
    {
        return m_delegate;
    }
    
    inline float getScale()
    {
        CCAssert(m_scaleX==m_scaleX, "m_scaleX and m_scaleX is not the same");
        return m_scaleX;
    }
    
    inline void setScaleX(float scaleX)
    {
        m_scaleX = scaleX;
    }
    
    inline float getScaleX()
    {
        return m_scaleX;
    }
    
    inline void setScaleY(float scaleY)
    {
        m_scaleY = scaleY;
    }
    
    inline float getScaleY()
    {
        return m_scaleY;
    }
    
    inline void setLastScaleX(float lastScaleX)
    {
        m_lastScaleX = lastScaleX;
    }
    
    inline float getLastScaleX()
    {
        return m_lastScaleX;
    }
    
    inline void setLastScaleY(float lastScaleY)
    {
        m_lastScaleY = lastScaleY;
    }
    
    inline float getLastScaleY()
    {
        return m_lastScaleY;
    }

protected:
    /**
     * 平滑移动
     */
    bool m_bSmoothMove;
    
    /**
     * 相机所在游戏世界位置
     * 移动相机，其实在反向移动游戏世界.所以在设置游戏世界位置时，坐标值都取反
     */
    CCPoint m_tWorldPosition;
    
    /**
     * 相机移动事件代理
     * weak reference
     */
    ISOCameraDelegate* m_delegate;

    /**
     * 相机的缩放参数
     * 相机本身是不能缩放，只能对观察的世界进行缩放。和世界的缩放值保持一致。
     * 相机放大，game world在放大。
     * 相机缩小，game world在缩小。
     */
    float m_scaleX;
    float m_scaleY;
    
    //旧的缩放
    float m_lastScaleX;
    float m_lastScaleY;
};

NS_CC_YHGE_END

#endif // YHGE_ISOMETRIC_ISOCAMERA_H_
