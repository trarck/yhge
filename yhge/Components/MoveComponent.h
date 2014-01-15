#ifndef COMPONENTS_MOVECOMPONENT_H_
#define COMPONENTS_MOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue
} MoveState;

class MoveComponent : public Component{

public:

    MoveComponent();
    ~MoveComponent();
    
    virtual bool init();
	bool init(float speed);
    
    virtual bool registerMessages();
    virtual void cleanupMessages();
    
    bool isMoving();
    MoveState getMoveState();
    CCPoint movingCoordinate();
    
    inline void calcSpeedVector(float directionVectorX,float directionVectorY){
        m_speedX=m_speed*directionVectorX;
        m_speedY=m_speed*directionVectorY;
    };

    bool beforeMove();
	void startMove();
    void stopMove();
    bool checkMoveable();
	//move to end point
	void moveTo(CCPoint to);

    //move with direction
    void moveWithDirection(float direction);
    void moveWithDirection(float direction,bool hasTo);
    void moveWithDirection(float directionX,float directionY);
    void moveWithDirection(float directionX,float directionY,bool hasTo);
    
    void continueMoveWithDirection(float direction);
    void continueMoveWithDirection(float direction,bool hasTo);
    void continueMoveWithDirection(float directionX,float directionY);
    void continueMoveWithDirection(float directionX,float directionY,bool hasTo);
		
    //move with path
    void moveWithPaths(CCArray* paths);
	void moveWithPaths(CCArray* paths, int fromIndex);
    void continueMoveWithPaths(CCArray* paths);
    void continueMoveWithPaths(CCArray* paths, int fromIndex);
	bool beforeMovePath();
	void restartMove();
	void preparePath();
	void calcDirection();
  
    void updateDirection(float delta);
	void updatePath(float delta);
    void updateMoveAnimation();
    void doMoveStart();
    void doMoveStop();
	void doHit(CCPoint location);
    
    virtual void onMoveDirection(Message* message);
    virtual void onMoveDirectionStop(Message* message);
    virtual void onMoveTo(Message* message);

public:
    
    float getSpeed()
    {
        return m_speed;
    }
    
    void setSpeed(float speed)
    {
        m_speed=speed;
    }
    
    void setDirection(float direction)
    {
        m_direction=direction;
        m_isDirectionDirty=false;
    }
    
    float getDirection()
    {
        return m_direction;
    }
    
    CCPoint getTo()
    {
        return m_to;
    }
    
    void setTo(CCPoint to)
    {
        m_to=to;
    }
    
    void setCurrentPaths(CCArray* pCurrentPaths)
    {
        CC_SAFE_RETAIN(pCurrentPaths);
        CC_SAFE_RELEASE(m_pCurrentPaths);
        m_pCurrentPaths = pCurrentPaths;
    }
    
    CCArray* getCurrentPaths()
    {
        return m_pCurrentPaths;
    }
    
    void setNextPaths(CCArray* pNextPaths)
    {
        CC_SAFE_RETAIN(pNextPaths);
        CC_SAFE_RELEASE(m_pNextPaths);
        m_pNextPaths = pNextPaths;
    }
    
    CCArray* getNextPaths()
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
	//移动相关
	float m_speed;
    float m_speedX;
    float m_speedY;
    
	float m_direction;//float 角度
    float m_directionX;//vector
    float m_directionY;
    
    bool m_isDirectionDirty;
    
	bool m_moving;
    
    float m_nextDirection;
    //float m_lastDirection;

    CCPoint m_to;
    int m_directionFlagX;
    int m_directionFlagY;

	MoveState m_moveState;
    
    SEL_SCHEDULE m_update;
    
    bool m_hasEndPosition;
	int m_fromIndex;
	CCArray* m_pCurrentPaths;
	CCArray* m_pNextPaths;
	int m_pathIndex;
};

NS_CC_YHGE_END

#endif //COMPONENTS_MOVECOMPONENT_H_
