#ifndef YHGE_COMPONENTS_MOVECOMPONENT_H_
#define YHGE_COMPONENTS_MOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue,
} MoveState;

class MoveComponent : public Component{

public:

    MoveComponent();
    ~MoveComponent();
    
	bool init(float speed);

	CCPoint movingCoordinate();

	void preparePath();

	void calcDirection();

	void moveWithDirection(float dirX ,float dirY);
	void moveWithDirection(CCPoint dir);
	void moveWithPaths(CCArray* paths);
	void moveWithPaths(CCArray* paths, int fromIndex);

	bool beforeMove();
	bool beforeMovePath();
	void startMove();
	void continueMoveWithPaths(bool *paths);
	void continueMoveWithDirection(CCPoint dir);
	void stopMove();
	void updateDirection(float delta);
	void updatePath(float delta);

	void updateMoveAnimation();
	void didMoveStop();
	void didHit(CCPoint location);

	inline void setPathIndex(int pathIndex)
    {
        m_pathIndex = pathIndex;
    }
    
    inline int getPathIndex()
    {
        return m_pathIndex;
    }
    
    inline void setSpeed(float speed)
    {
        m_speed = speed;
    }
    
    inline float getSpeed()
    {
        return m_speed;
    }
    
    inline void setDirection(CCPoint direction)
    {
        m_direction = direction;
    }
    
    inline CCPoint getDirection()
    {
        return m_direction;
    }
    
    inline void setTo(CCPoint to)
    {
        m_to = to;
    }
    
    inline CCPoint getTo()
    {
        return m_to;
    }
    
    inline void setNextDirection(CCPoint nextDirection)
    {
        m_nextDirection = nextDirection;
    }
    
    inline CCPoint getNextDirection()
    {
        return m_nextDirection;
    }
    
    inline void setLastDirection(CCPoint lastDirection)
    {
        m_lastDirection = lastDirection;
    }
    
    inline CCPoint getLastDirection()
    {
        return m_lastDirection;
    }
    
    inline void setFromIndex(int fromIndex)
    {
        m_fromIndex = fromIndex;
    }
    
    inline int getFromIndex()
    {
        return m_fromIndex;
    }
    
    inline void setCurrentPaths(CCArray* currentPaths)
    {
        CC_SAFE_RETAIN(currentPaths);
        CC_SAFE_RELEASE(m_currentPaths);
        m_currentPaths = currentPaths;
    }
    
    inline CCArray* getCurrentPaths()
    {
        return m_currentPaths;
    }
    
    inline void setNextPaths(CCArray* nextPaths)
    {
        CC_SAFE_RETAIN(nextPaths);
        CC_SAFE_RELEASE(m_nextPaths);
        m_nextPaths = nextPaths;
    }
    
    inline CCArray* getNextPaths()
    {
        return m_nextPaths;
    }
    
    inline void setMoving(bool moving)
    {
        m_moving = moving;
    }
    
    inline bool isMoving()
    {
        return m_moving;
    }
    
    inline void setInStep(bool inStep)
    {
        m_inStep = inStep;
    }
    
    inline bool isInStep()
    {
        return m_inStep;
    }
    
    inline void setMoveState(MoveState moveState)
    {
        m_moveState = moveState;
    }
    
    inline MoveState getMoveState()
    {
        return m_moveState;
    }

protected:
	//移动相关
    int m_pathIndex;
    float m_speed;
    CCPoint m_direction;
    CCPoint m_to;
    CCPoint m_nextDirection;
    CCPoint m_lastDirection;
    int m_fromIndex;
    CCArray* m_currentPaths;
    CCArray* m_nextPaths;
    bool m_moving;
    bool m_inStep;
    MoveState m_moveState;
	
	void* updateStep_;
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_MOVECOMPONENT_H_
