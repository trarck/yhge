#ifndef YHGE_COMPONENTS_GRIDMOVECOMPONENT_H_
#define YHGE_COMPONENTS_GRIDMOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue
} MoveState;

class GridMoveComponent : public Component{

public:

    GridMoveComponent();
    ~GridMoveComponent();
    
    virtual bool init();
	bool init(float speed);
    
    virtual bool registerMessages();
    virtual void cleanupMessages();
    
    bool isMoving();
    MoveState getMoveState();
    CCPoint movingCoordinate();
    
	void calcMoveDuration(float directionX,float directionY);
    void calcSpeedVector(float directionX,float directionY);
	void calcTo();

    bool checkMoveable();
	void stop();
   
    //move with direction
    void moveWithDirection(float directionX,float directionY);
    void moveWithDirection(CCPoint direction);
    


	void prepareDirection(float directionX,float directionY);
	
	void calcDirection();
	void updateDirection(float delta);
    //move with path
    void moveWithPaths(CCArray* paths);
	void moveWithPaths(CCArray* paths, int fromIndex);
    void continueMoveWithPaths(CCArray* paths);
    void continueMoveWithPaths(CCArray* paths, int fromIndex);
	void restartMove();
	int getFirstPathIndex();
	void preparePath();
	void preparePath(int iPathIndex);
	void updatePath(float delta);
    void updateMoveAnimation();

    void doMoveStart();
    void doMoveStop();

	void doHit(CCPoint location);
    
    virtual void onMoveDirection(Message* message);
    virtual void onMoveDirectionStop(Message* message);
    virtual void onMoveTo(Message* message);
    virtual void onMovePath(Message* message);
    

	float getSpeed();
	void setSpeed(float speed);

	virtual void setDirection(float directionX ,float directionY);
	virtual void setDirection(CCPoint direction);
	virtual CCPoint getDirection();

    virtual void setDirectionX(float directionX);
	virtual float getDirectionX();
	virtual void setDirectionY(float directionY);
	virtual float getDirectionY();

	virtual void setNextDirection(float directionX,float directionY);
	virtual CCPoint getNextDirection();
	virtual void setNextDirectionX(int nextDirectionX);
	virtual int getNextDirectionX();
	virtual void setNextDirectionY(float nextDirectionY);
	virtual float getNextDirectionY();

	virtual void setKeepMoveDirection(bool bKeepMoveDirection);
	virtual bool isKeepMoveDirection();

	int getPathIndex();
	void setPathIndex(int pathIndex);

	CCArray* getCurrentPaths();
	void setCurrentPaths(CCArray* currentPaths);

	CCArray* getNextPaths();
	void setNextPaths(CCArray* nextPaths);

	CCPoint getTo();
	void setTo(CCPoint to);
protected:
	void _startMove();
    void _stopMove();
	void _prepareMove();
	void _continueUpdate();
	void _resetState();

	void continueMoveWithDirection(float directionX,float directionY);
    void continueMoveWithDirection(CCPoint direction);

	

	//移动相关
	//在地图坐标系的速度
	float m_speed;
    float m_speedX;
    float m_speedY;
    
	float m_direction;//float 角度
    float m_directionX;//vector
    float m_directionY;
	float m_lastDirectionX;
	float m_lastDirectionY;
	//只保留最后一个move direction。
	//如果一个格子没有移动完成，接收移动消息是无效的，但是为了保持连贯性，
	//把下一个移动消息保存起来。
	float m_nextDirectionX;//vector
    float m_nextDirectionY;
    bool m_isDirectionDirty;
    //direction移动结束后，是否接着原来的方向继续移动。
	bool m_bKeepMoveDirection;


	CCPoint m_startMoveViewPosition;
	float m_fViewSpeedX;
    float m_fViewSpeedY;

	bool m_moving;
	//一次移动的时间
	float m_movingDuration;
	//一次移动中的移动时间累计
	float m_movingDeltaTime;
    
    float m_nextDirection;
    //float m_lastDirection;

    CCPoint m_to;
    int m_directionFlagX;
    int m_directionFlagY;

	MoveState m_moveState;
    
    SEL_SCHEDULE m_update;
    
    bool m_hasEndPosition;
	int m_iFromIndex;
	CCArray* m_pCurrentPaths;
	CCArray* m_pNextPaths;
	int m_iPathIndex;
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_GRIDMOVECOMPONENT_H_
