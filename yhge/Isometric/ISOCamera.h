#ifndef YHGE_ISOMETRIC_ISOCAMERA_H_
#define YHGE_ISOMETRIC_ISOCAMERA_H_

#include "cocos2d.h"
#include "IsometricMacros.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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
     * 相对当前的缩放大小的移动，不是原始大小，这样看上去很平滑。不会出现当放大时，相机移动过快，缩小时相机移动缓慢。
     */
	void move(float deltaX,float deltaY);
    
    /**
     * 移动
     * 相对位置，屏幕坐标系的值。
     */
	void move(const CCPoint& delta);
    
    /**
     * 移动
     * 绝对位置，屏幕坐标系的值。
     */
    void moveTo(float x,float y);
    
    /**
     * 移动
     * 绝对位置，屏幕坐标系的值。
     */
    void moveTo(const CCPoint& position);

    /**
     * 反向移动
     * 相对位置
     * 移动相机，其实在反向移动游戏世界
     */
	void moveOpposite(float deltaX,float deltaY);
    
    /**
     * 反向移动
     * 相对位置
     * 移动相机，其实在反向移动游戏世界
     */
	void moveOpposite(const CCPoint& delta);
    
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
     * 由于m_tWorldPosition记录的是旧的缩放下相机所在世界的位置。为了保持显示的一致性，要把m_tWorldPosition进行缩放修正。
     * 在新的缩放模式下，相机的移动是相对新的缩放模式的。
     */
    void updateScale();

    /**
     * 取得屏幕坐标所在game的位置
     */
    CCPoint getLocationInWorld(const CCPoint& position);
    
    /**
     * 取得game的位置在屏幕坐标所
     */
    CCPoint getLocationInScene(const CCPoint& position);


    /**
     * 设置可显示范围
     * 这里的单位是屏幕坐标系。和相机是否缩放没有关系。
     * 如果要把地图坐标转成屏幕坐标，则需要处理相机的缩放。
     */
    void setMoveRange(const CCRect& rect);

    inline void setMoveRange(float minX,float minY,float maxX,float maxY)
    {
        m_minX=minX;
        m_minY=minY;
        m_maxX=maxX;
        m_maxY=maxY;
    }

    /**
     * 修正移动范围是否超过移动范围
     */
    CCPoint modifyPositionInRange(const CCPoint& position);

    /**
     * 修正移动范围是否超过移动范围
     * 直接修改成员变量，减少参数传递
     */
    inline void modifyWorldPositionInRange()
    {
        m_tWorldPosition.x=m_tWorldPosition.x<m_minX
            ?m_minX:(m_tWorldPosition.x>m_maxX?m_maxX:m_tWorldPosition.x);
        m_tWorldPosition.y=m_tWorldPosition.y<m_minY
            ?m_minY:(m_tWorldPosition.y>m_maxY?m_maxY:m_tWorldPosition.y);
    }

    inline const CCPoint& getWorldPosition()
    {
        return m_tWorldPosition;
    }

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

    void setNeedCheckPositionRane(bool needCheckPositionRane)
    {
        m_needCheckPositionRane = needCheckPositionRane;
    }

    bool isNeedCheckPositionRane()
    {
        return m_needCheckPositionRane;
    }

    void setMinX(float minX)
    {
        m_minX = minX;
    }

    float getMinX()
    {
        return m_minX;
    }

    void setMaxX(float maxX)
    {
        m_maxX = maxX;
    }

    float getMaxX()
    {
        return m_maxX;
    }

    void setMinY(float minY)
    {
        m_minY = minY;
    }

    float getMinY()
    {
        return m_minY;
    }

    void setMaxY(float maxY)
    {
        m_maxY = maxY;
    }

    float getMaxY()
    {
        return m_maxY;
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

    //是否需要对位置做范围检查
    bool m_needCheckPositionRane;
    //相机的可视范围
    float m_minX;
    float m_maxX;
    float m_minY;
    float m_maxY;
};

NS_CC_YHGE_ISOMETRIC_END

#endif // YHGE_ISOMETRIC_ISOCAMERA_H_
