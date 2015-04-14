#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_SCEENCOORDMOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_SCEENCOORDMOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"
#include "ISOPositionComponent.h"
#include "RendererComponent.h"

NS_CC_YHGE_BEGIN

/**
 * 移动组件
 * 直接移动屏幕坐标。
 * 万向移动.
 * 不是按格子，如果改变方向立即生效。
 */
class SceenCoordMoveComponent : public Component{

public:

    SceenCoordMoveComponent();
    
    ~SceenCoordMoveComponent();
    
    virtual bool init();
	bool init(float speed);
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
    
    virtual bool registerMessages();
    virtual void cleanupMessages();

    /**
     * 检查是否可以移动
     */
    bool checkMoveable();
    
    /**
     * 开始移动
     */
	void startMove();
    
    /**
     * 停止移动
     */
    void stopMove();
    
    /**
     * 移动到目标点
     */
	virtual void moveTo(const CCPoint& to);
    
    void continueMoveTo(const CCPoint& to);


    /**
     * 按方向移动
     */
    virtual void moveWithDirection(float direction);
    
    /**
     * 按方向移动
     * 是否要结束
     */
    virtual void moveWithDirection(float direction,bool hasTo);
    
    /**
     * 按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    virtual void moveWithDirection(float directionX,float directionY);
    
    /**
     * 按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    virtual void moveWithDirection(float directionX,float directionY,bool hasTo);
    
    /**
     * 继续按方向移动
     */
    void continueMoveWithDirection(float direction);
    
    /**
     * 继续按方向移动
     */
    void continueMoveWithDirection(float direction,bool hasTo);
    
    /**
     * 继续按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    void continueMoveWithDirection(float directionX,float directionY);
    
    /**
     * 继续按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    void continueMoveWithDirection(float directionX,float directionY,bool hasTo);
    
    /**
     * 按路径移动
     * 注意路径是屏幕坐标
     */
    virtual void moveWithPaths(CCArray* paths);
    
    /**
     * 按路径移动
     */
	virtual void moveWithPaths(CCArray* paths, int fromIndex);
    
    /**
     * 继续按路径移动
     */
    void continueMoveWithPaths(CCArray* paths);
    
    /**
     * 继续按路径移动
     */
    void continueMoveWithPaths(CCArray* paths, int fromIndex);
    
    /**
     * 重新按路径移动
     */
	void restartMoveWithPaths();
    
    /**
     * 路径移动之前进行检查
     */
	bool beforeMovePath();
    
    /**
     * 取得当前路径结点索引
     */
	int getCurrentPathIndex();
    
    /**
     * 计算方向
     * 主要用于按路径移动时
     */
	void calcDirection();
    
    /**
     * 计算速度分量
     */
    void calcSpeedVector();
    
    /**
     * 移动动画步骤
     * 通过方向移动的动画步骤
     */
    void updateTo(float delta);
    
    /**
     * 移动动画步骤
     * 通过方向移动的动画步骤
     */
    void updateDirection(float delta);
    
    /**
     * 移动动画步骤
     * 通过路径移动的动画步骤
     */
	void updatePath(float delta);
    
    /**
     * 移动的时候，方向改变。
     * 主要通知人物的面向动画
     */
    void doDirectionChange();
    
    /**
     * 开始移动的时候做一些事情。
     */
    void doMoveStart();
    
    /**
     * 移动结束的时候做一些事情。
     */
    void doMoveStop();
    
    /**
     * 移动被打断做一些事情。
     */
	void doHit(CCPoint location);
    
    /**
     * 处理按方向移动消息。
     */
    virtual void onMoveDirection(Message* message);
    
    /**
     * 处理按路径移动消息。
     */
    virtual void onMoveWithPath(Message* message);
    
    /**
     * 处理移动到目标点。
     */
    virtual void onMoveTo(Message* message);
    
    /**
     * 处理移动结束消息。
     */
    virtual void onMoveStop(Message* message);
    
    /**
     * 弧度转成8方向
     */
    static int hadap(float ang)
    {
        int index = 4 + floor(ang * 1.250000 + 0.625000);
        if (index == 0)
        {
            index = 8;
        }
        return index-1;
    }
    
public:
    
    typedef enum  {
        MoveIdle=0,
        MoveStop,
        MoveStart,
        MoveWillStop,
        MoveContinue
    } MoveState;
    
    typedef enum  {
        kMoveNone=0,
        kMoveDirection,
        kMovePath,
        kMoveTo
    } MoveType;
    
    
    inline bool isMoving()
    {
        return _moving;
    }
    
    inline MoveState getMoveState()
    {
        return _moveState;
    }
    
    void setMoveType(MoveType moveType)
    {
        _moveType = moveType;
    }
    
    MoveType getMoveType()
    {
        return _moveType;
    }
    
    inline float getSpeed()
    {
        return _speed;
    }
    
    inline void setSpeed(float speed)
    {
        _speed=speed;
    }
    
    inline void setDirection(float direction)
    {
        _direction=direction;
    }
    
    inline float getDirection()
    {
        return _direction;
    }
    
    inline CCPoint getTo()
    {
        return _to;
    }
    
    inline void setTo(CCPoint to)
    {
        _to=to;
    }
    
    inline void setCurrentPaths(CCArray* pCurrentPaths)
    {
        CC_SAFE_RETAIN(pCurrentPaths);
        CC_SAFE_RELEASE(_pCurrentPaths);
        _pCurrentPaths = pCurrentPaths;
    }
    
    inline CCArray* getCurrentPaths()
    {
        return _pCurrentPaths;
    }
    
    inline void setNextPaths(CCArray* pNextPaths)
    {
        CC_SAFE_RETAIN(pNextPaths);
        CC_SAFE_RELEASE(_pNextPaths);
        _pNextPaths = pNextPaths;
    }
    
    inline CCArray* getNextPaths()
    {
        return _pNextPaths;
    }

	inline void setPathIndex(int pathIndex)
    {
        _pathIndex = pathIndex;
    }
    
    inline int getPathIndex()
    {
        return _pathIndex;
    }
    
protected:
    
    /**
     * 准备移动到的数据
     */
    bool prepareTo(const CCPoint& to,const CCPoint& from);
    
    /**
     * 准备方向移动的数据
     */
    void prepareDirection(float direction);
    
    /**
     * 准备方向移动的数据
     */
    void prepareDirection(float directionX,float directionY);
    
    /**
     * 准备路径数据
     */
	void preparePath();
    
    void preparePath(int pathIndex);
    
    /**
     * 移动之前的准备
     */
    virtual void prepareMove();
    
    //开启更新定时器。为了使update不是虚函数，这里使用虚函数
    virtual void startMoveUpdateSchedule();
    virtual void stopMoveUpdateSchedule();

protected:
    //移动状态
	MoveState _moveState;
    
    //移动类型
    MoveType _moveType;
    
	//移动速度，屏幕坐标速度
	float _speed;
    
    //速度分量
    float _speedX;
    float _speedY;
    
    //移动方向。屏幕坐标角度
	float _direction;
    
    //移动方向的分量
    float _directionX;//vector
    float _directionY;
    
//    //下个移动方向
//    float _nextDirection;

    //移动方向标记
    int _directionFlagX;
    int _directionFlagY;
    
    //移动到的位置.屏幕坐标
    CCPoint _to;
    
    //是否正在移动
	bool _moving;
    
    //更新函数
    SEL_SCHEDULE _update;
    
    //是否需要检查移动结束。有时候是一直移动下去
    bool _hasEndPosition;
    
    
	int _fromIndex;
	CCArray* _pCurrentPaths;
	CCArray* _pNextPaths;
	int _pathIndex;
    
    ISOPositionComponent* _isoPositionComponent;
    RendererComponent* _rendererComponent;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_SCEENCOORDMOVECOMPONENT_H_
