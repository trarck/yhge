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
    virtual void onCameraMove(const Vec2& worldPosition)=0;
    
    /**
     * 相机移动结束
     * worldPosition是相机所在的世界坐标
     */
    virtual void onCameraMoveEnd(const Vec2& worldPosition){};
    
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
class ISOCamera: public Ref
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
	void move(const Vec2& delta);
    
    /**
     * 移动
     * 绝对位置，屏幕坐标系的值。
     */
    void moveTo(float x,float y);
    
    /**
     * 移动
     * 绝对位置，屏幕坐标系的值。
     */
    void moveTo(const Vec2& position);

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
	void moveOpposite(const Vec2& delta);
    
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
     * 由于_worldPosition记录的是旧的缩放下相机所在世界的位置。为了保持显示的一致性，要把_worldPosition进行缩放修正。
     * 在新的缩放模式下，相机的移动是相对新的缩放模式的。
     */
    void updateScale();

    /**
     * 取得屏幕坐标所在game的位置
     */
    Vec2 getLocationInWorld(const Vec2& position);
    
    /**
     * 取得game的位置在屏幕坐标所
     */
    Vec2 getLocationInScene(const Vec2& position);


    /**
     * 设置可显示范围
     * 这里的单位是屏幕坐标系。和相机是否缩放没有关系。
     * 如果要把地图坐标转成屏幕坐标，则需要处理相机的缩放。
     */
    void setMoveRange(const CCRect& rect);

    inline void setMoveRange(float minX,float minY,float maxX,float maxY)
    {
        _minX=minX;
        _minY=minY;
        _maxX=maxX;
        _maxY=maxY;
    }

    /**
     * 修正移动范围是否超过移动范围
     */
    Vec2 modifyPositionInRange(const Vec2& position);

    /**
     * 修正移动范围是否超过移动范围
     * 直接修改成员变量，减少参数传递
     */
    inline void modifyWorldPositionInRange()
    {
        _worldPosition.x=_worldPosition.x<_minX
            ?_minX:(_worldPosition.x>_maxX?_maxX:_worldPosition.x);
        _worldPosition.y=_worldPosition.y<_minY
            ?_minY:(_worldPosition.y>_maxY?_maxY:_worldPosition.y);
    }

    inline const Vec2& getWorldPosition()
    {
        return _worldPosition;
    }

    inline void setSmoothMove(bool smoothMove)
    {
        _smoothMove = smoothMove;
    }
    
    inline bool isSmoothMove()
    {
        return _smoothMove;
    }
    
    inline void setMoveDelegate(ISOCameraDelegate* moveDelegate)
    {
        _delegate = moveDelegate;
    }
    
    inline ISOCameraDelegate* getMoveDelegate()
    {
        return _delegate;
    }
    
    inline float getScale()
    {
        CCAssert(_scaleX==_scaleX, "_scaleX and _scaleX is not the same");
        return _scaleX;
    }
    
    inline void setScaleX(float scaleX)
    {
        _scaleX = scaleX;
    }
    
    inline float getScaleX()
    {
        return _scaleX;
    }
    
    inline void setScaleY(float scaleY)
    {
        _scaleY = scaleY;
    }
    
    inline float getScaleY()
    {
        return _scaleY;
    }
    
    inline void setLastScaleX(float lastScaleX)
    {
        _lastScaleX = lastScaleX;
    }
    
    inline float getLastScaleX()
    {
        return _lastScaleX;
    }
    
    inline void setLastScaleY(float lastScaleY)
    {
        _lastScaleY = lastScaleY;
    }
    
    inline float getLastScaleY()
    {
        return _lastScaleY;
    }

    void setNeedCheckPositionRane(bool needCheckPositionRane)
    {
        _needCheckPositionRane = needCheckPositionRane;
    }

    bool isNeedCheckPositionRane()
    {
        return _needCheckPositionRane;
    }

    void setMinX(float minX)
    {
        _minX = minX;
    }

    float getMinX()
    {
        return _minX;
    }

    void setMaxX(float maxX)
    {
        _maxX = maxX;
    }

    float getMaxX()
    {
        return _maxX;
    }

    void setMinY(float minY)
    {
        _minY = minY;
    }

    float getMinY()
    {
        return _minY;
    }

    void setMaxY(float maxY)
    {
        _maxY = maxY;
    }

    float getMaxY()
    {
        return _maxY;
    }
protected:
    /**
     * 平滑移动
     */
    bool _smoothMove;
    
    /**
     * 相机所在游戏世界位置
     * 移动相机，其实在反向移动游戏世界.所以在设置游戏世界位置时，坐标值都取反
     */
    Vec2 _worldPosition;
    
    /**
     * 相机移动事件代理
     * weak reference
     */
    ISOCameraDelegate* _delegate;

    /**
     * 相机的缩放参数
     * 相机本身是不能缩放，只能对观察的世界进行缩放。和世界的缩放值保持一致。
     * 相机放大，game world在放大。
     * 相机缩小，game world在缩小。
     */
    float _scaleX;
    float _scaleY;
    
    //旧的缩放
    float _lastScaleX;
    float _lastScaleY;

    //是否需要对位置做范围检查
    bool _needCheckPositionRane;
    //相机的可视范围
    float _minX;
    float _maxX;
    float _minY;
    float _maxY;
};

NS_CC_YHGE_ISOMETRIC_END

#endif // YHGE_ISOMETRIC_ISOCAMERA_H_
