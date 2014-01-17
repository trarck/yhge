#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_MOVECOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_MOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"
#include "ISOPositionComponent.h"
#include "RendererComponent.h"

NS_CC_YHGE_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue
} MoveState;

/**
 * 移动组件
 * 直接移动屏幕坐标。
 * 万向移动
 */
class MoveComponent : public Component{

public:

    MoveComponent();
    
    ~MoveComponent();
    
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
	void moveTo(CCPoint to);

    /**
     * 按方向移动
     */
    void moveWithDirection(float direction);
    
    /**
     * 按方向移动
     * 是否要结束
     */
    void moveWithDirection(float direction,bool hasTo);
    
    /**
     * 按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    void moveWithDirection(float directionX,float directionY);
    
    /**
     * 按方向移动
     * 不是方向，而是直接使用偏移量。不常用
     */
    void moveWithDirection(float directionX,float directionY,bool hasTo);
    
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
     * 重新按路径移动
     */
	void restartMoveWithPaths();
    
    /**
     * 路径移动之前进行检查
     */
	bool beforeMovePath();
    
    /**
     * 准备路径数据
     */
	void preparePath();
    
    void preparePath(int pathIndex);
    
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
    void calcSpeedVector(float directionVectorX,float directionVectorY);
    
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
    
    inline bool isMoving()
    {
        return m_moving;
    }
    
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
    
    inline void setDirection(float direction)
    {
        m_direction=direction;
    }
    
    inline float getDirection()
    {
        return m_direction;
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

	inline void setPathIndex(int pathIndex)
    {
        m_pathIndex = pathIndex;
    }
    
    inline int getPathIndex()
    {
        return m_pathIndex;
    }

protected:
	//移动速度，屏幕坐标速度
	float m_speed;
    
    //速度分量
    float m_speedX;
    float m_speedY;
    
    //移动方向。角度
	float m_direction;
    
    //移动方向的分量
    float m_directionX;//vector
    float m_directionY;
    
    //下个移动方向
    float m_nextDirection;

    //移动方向标记
    int m_directionFlagX;
    int m_directionFlagY;
    
    //移动到的位置
    CCPoint m_to;

    //移动状态
	MoveState m_moveState;
    
    //是否正在移动
	bool m_moving;
    
    //更新函数
    SEL_SCHEDULE m_update;
    
    //是否需要检查移动结束。有时候是一直移动下去
    bool m_hasEndPosition;
    
    
	int m_fromIndex;
	CCArray* m_pCurrentPaths;
	CCArray* m_pNextPaths;
	int m_pathIndex;
    
    ISOPositionComponent* m_isoPositionComponent;
    RendererComponent* m_rendererComponent;
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_MOVECOMPONENT_H_
