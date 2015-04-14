#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"
#include "ISOPositionComponent.h"
#include "RendererComponent.h"
#include "ComponentDelegates.h"

NS_CC_YHGE_BEGIN

/**
 * 按地图的格子移动
 */
class GridMoveComponent : public Component{

public:

    GridMoveComponent();
    ~GridMoveComponent();
    
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
    
    /**
     * 注册消息
     */
    virtual bool registerMessages();
    
    /**
     * 消除消息
     */
    virtual void cleanupMessages();
    
    /**
     * 停止移动
     * 马上停止，不需要格子移动结束。
     */
	void stop();
    
    /**
     * 停止移动
     * 不会马上停止，要等一个格子移动完成。
     */
    void stopMove();
    
    /**
     * 检查是不是可以移动
     */
    virtual bool checkMoveable();

    /**
     * 按方向移动
     */
    virtual void moveWithDirection(int directionX,int directionY);
    
    /**
     * 继续方向移动
     */
	void continueMoveWithDirection(int directionX,int directionY);
    
    /**
     * 移动之前准备一下
     */
	void prepareDirection(int directionX,int directionY);

    /**
     * 计算移动时间
     */
	void calcMoveDuration(int directionX,int directionY);
    
    /**
     * 计算屏幕速度
     */
    void calcSpeedVector(int directionX,int directionY);
    
    /**
     * 计算移动到的位置
     */
	virtual void calcTo();
    
    /**
     * 计算方向
     * 主要用于按路径移动时
     */
	virtual void calcDirection();
    
    /**
     * 按方向移动时的定时更新器
     * 由于每帧都执行，这里尽量不使用虚函数。所以把起动函数设置为虚函数
     */
    void updateDirection(float delta);
    
    /**
     * 按路径移动
     * 路径结点是反向的。即第一个结点是终点。
     * 主要原因是为了配合A星的搜索结果,减少一次数组元素的反向。
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
     * 重新开始路径移动
     */
	void restartMoveWithPaths();
    
    /**
     * 准备移动路径
     */
	void preparePath();
    
	void preparePath(int pathIndex);
    
    /**
     * 取得当前路径结点索引
     */
	int getCurrentPathIndex();

    /**
     * 按路径移动时的定时更新器
     * 由于每帧都执行，这里尽量不使用虚函数。所以把起动函数设置为虚函数
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
    virtual void onMoveWithDirection(Message* message);
    
    /**
     * 处理按路径移动消息。
     */
    virtual void onMoveWithPath(Message* message);

    /**
     * 处理按路径移动消息。
     */
    virtual void onMoveWithPathFrom(Message* message);
    
    /**
     * 处理移动结束消息。
     */
    virtual void onMoveStop(Message* message);
    
    /**
     * 设置方向。
     */
    virtual void setDirection(int directionX ,int directionY);
    
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
        kMovePath
    } MoveType;
    
    /**
     * 是否在移动
     */
    inline bool isMoving()
    {
        return _moving;
    }
    
    /**
     * 取得移动状态
     */
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
	   
    inline void setDirectionX(int directionX)
    {
        _lastDirectionX=_directionX;
        _directionX = directionX;
    }
	
    inline int getDirectionX()
    {
        return _directionX;
    }
	
    inline void setDirectionY(int directionY)
    {
        _lastDirectionY=_directionY;
        _directionY = directionY;
    }
    
    inline int getDirectionY()
    {
        return _directionY;
    }

	inline void setNextDirection(int directionX,int directionY)
    {
        _nextDirectionX=directionX;
        _nextDirectionY=directionY;
    }

    inline void setNextDirectionX(int nextDirectionX)
    {
        _nextDirectionX = nextDirectionX;
    }
    
    inline int getNextDirectionX()
    {
        return _nextDirectionX;
    }
    
    inline void setNextDirectionY(int nextDirectionY)
    {
        _nextDirectionY = nextDirectionY;
    }
    
    inline int getNextDirectionY()
    {
        return _nextDirectionY;
    }

    inline void setKeepMoveDirection(bool bKeepMoveDirection)
    {
        _bKeepMoveDirection = bKeepMoveDirection;
    }
    
    inline bool isKeepMoveDirection()
    {
        return _bKeepMoveDirection;
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
    
    inline void setMoveableDelegate(GirdMoveableDelegate* moveableDelegate)
    {
        _moveableDelegate = moveableDelegate;
    }
    
    inline GirdMoveableDelegate* getMoveableDelegate()
    {
        return _moveableDelegate;
    }
    
protected:
    
    /**
     * 开始移动
     */
	virtual void startMove();
    
    /**
     * 移动之前的准备
     */
	virtual void prepareMove();
    
    /**
     * 继续更新
     */
	void continueUpdate();
    
    /**
     * 重置状态
     */
	void resetState();
    
    /**
     * 移动完成
     */
    virtual void completeMove();
    
    //开启更新定时器。为了使update不是虚函数，这里使用虚函数
    virtual void startMoveUpdateSchedule();
    virtual void stopMoveUpdateSchedule();

    virtual SEL_SCHEDULE getUpdateDirectionHandle();
    virtual SEL_SCHEDULE getUpdatePathHandle();

protected:
    //移动状态
	MoveState _moveState;

    //移动类型
    MoveType _moveType;

	//地图坐标系的速度
	float _speed;
    
    //速度分量
    float _speedX;
    float _speedY;
    
    //屏幕坐标系移动速度，由地图坐标系转换而来
	float _fViewSpeedX;
    float _fViewSpeedY;
    
    //地图坐标里的移动方向
    int _directionX;//vector
    int _directionY;
    
    //地图坐标里的上次移动方向
	int _lastDirectionX;
	int _lastDirectionY;
    
	//只保留最后一个move direction。
	//如果一个格子没有移动完成，接收移动消息是无效的，但是为了保持连贯性，
	//把下一个移动消息保存起来。
	int _nextDirectionX;//vector
    int _nextDirectionY;
    
    //direction移动结束后，是否接着原来的方向继续移动。
	bool _bKeepMoveDirection;

	//一次移动的时间
	float _movingDuration;
	//一次移动中的移动时间累计
	float _movingDeltaTime;

    //移动到地图的哪个格子。地图坐标
    CCPoint _to;
    
    //是不是正在移动
	bool _moving;
    
    //按路径移动时，路径数组的开始索引
	int _fromIndex;
    //当前移动路径
	CCArray* _pCurrentPaths;
    //下一个移动路径
	CCArray* _pNextPaths;
    //当前移动路径进行的位置
	int _pathIndex;
    
    GirdMoveableDelegate* _moveableDelegate;
    
    //定时器函数
    SEL_SCHEDULE _update;
    
    ISOPositionComponent* _isoPositionComponent;
//    RendererComponent* _rendererComponent;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_
