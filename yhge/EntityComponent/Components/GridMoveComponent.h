#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"
#include "ISOPositionComponent.h"
#include "RendererComponent.h"

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
    bool checkMoveable();

    /**
     * 按方向移动
     */
    void moveWithDirection(int directionX,int directionY);
    
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
	void calcTo();
    
    /**
     * 计算方向
     * 主要用于按路径移动时
     */
	void calcDirection();
    
    /**
     * 按方向移动时的定时更新器
     */
    void updateDirection(float delta);
    
    /**
     * 按路径移动
     */
    void moveWithPaths(CCArray* paths);
    
    /**
     * 按路径移动
     */
	void moveWithPaths(CCArray* paths, int fromIndex);
    
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
    
    /**
     * 是否在移动
     */
    inline bool isMoving()
    {
        return m_moving;
    }
    
    /**
     * 取得移动状态
     */
    inline MoveState getMoveState()
    {
        return m_moveState;
    }

	
    inline float getSpeed()
    {
        return m_speed;
    }
    
    inline void setSpeed(float speed)
    {
        m_speed=speed;
    }
	   
    inline void setDirectionX(int directionX)
    {
        m_lastDirectionX=m_directionX;
        m_directionX = directionX;
    }
	
    inline int getDirectionX()
    {
        return m_directionX;
    }
	
    inline void setDirectionY(int directionY)
    {
        m_lastDirectionY=m_directionY;
        m_directionY = directionY;
    }
    
    inline int getDirectionY()
    {
        return m_directionY;
    }

	inline void setNextDirection(int directionX,int directionY)
    {
        m_nextDirectionX=directionX;
        m_nextDirectionY=directionY;
    }

    inline void setNextDirectionX(int nextDirectionX)
    {
        m_nextDirectionX = nextDirectionX;
    }
    
    inline int getNextDirectionX()
    {
        return m_nextDirectionX;
    }
    
    inline void setNextDirectionY(int nextDirectionY)
    {
        m_nextDirectionY = nextDirectionY;
    }
    
    inline int getNextDirectionY()
    {
        return m_nextDirectionY;
    }

    inline void setKeepMoveDirection(bool bKeepMoveDirection)
    {
        m_bKeepMoveDirection = bKeepMoveDirection;
    }
    
    inline bool isKeepMoveDirection()
    {
        return m_bKeepMoveDirection;
    }
    
    inline CCPoint getTo()
    {
        return m_to;
    }
    
    inline void setTo(CCPoint to)
    {
        m_to=to;
    }

    inline void setCurrentPaths(CCArray* pCurrentPaths)
    {
        CC_SAFE_RETAIN(pCurrentPaths);
        CC_SAFE_RELEASE(m_pCurrentPaths);
        m_pCurrentPaths = pCurrentPaths;
    }
    
    inline CCArray* getCurrentPaths()
    {
        return m_pCurrentPaths;
    }
    
    inline void setNextPaths(CCArray* pNextPaths)
    {
        CC_SAFE_RETAIN(pNextPaths);
        CC_SAFE_RELEASE(m_pNextPaths);
        m_pNextPaths = pNextPaths;
    }
    
    inline CCArray* getNextPaths()
    {
        return m_pNextPaths;
    }
    
protected:
    
	void startMove();
	void prepareMove();
	void continueUpdate();
	void resetState();

protected:
    
	//地图坐标系的速度
	float m_speed;
    
    //速度分量
    float m_speedX;
    float m_speedY;
    
    //屏幕坐标系移动速度，由地图坐标系转换而来
	float m_fViewSpeedX;
    float m_fViewSpeedY;
    
    //地图坐标里的移动方向
    int m_directionX;//vector
    int m_directionY;
    
    //地图坐标里的上次移动方向
	int m_lastDirectionX;
	int m_lastDirectionY;
    
	//只保留最后一个move direction。
	//如果一个格子没有移动完成，接收移动消息是无效的，但是为了保持连贯性，
	//把下一个移动消息保存起来。
	int m_nextDirectionX;//vector
    int m_nextDirectionY;
    
    //direction移动结束后，是否接着原来的方向继续移动。
	bool m_bKeepMoveDirection;

	//一次移动的时间
	float m_movingDuration;
	//一次移动中的移动时间累计
	float m_movingDeltaTime;

    //移动到地图的哪个格子。地图坐标
    CCPoint m_to;
    
    //移动状态
	MoveState m_moveState;
    
    //是不是正在移动
	bool m_moving;
    
    //按路径移动时，路径数组的开始索引
	int m_fromIndex;
    //当前移动路径
	CCArray* m_pCurrentPaths;
    //下一个移动路径
	CCArray* m_pNextPaths;
    //当前移动路径进行的位置
	int m_pathIndex;
    
    
    //定时器函数
    SEL_SCHEDULE m_update;
    
    ISOPositionComponent* m_isoPositionComponent;
    RendererComponent* m_rendererComponent;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_GRIDMOVECOMPONENT_H_
