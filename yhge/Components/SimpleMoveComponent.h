#ifndef YHGE_COMPONENTS_MOVECOMPONENT_H_
#define YHGE_COMPONENTS_MOVECOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue
} MoveState;

class SimpleMoveComponent : public Component{

public:

    SimpleMoveComponent();
    ~SimpleMoveComponent();
    
    virtual bool init();
    bool initWithSpeed(float speed);
    
    virtual bool registerMessages();
    virtual void cleanupMessages();

	void preparePath();

    float getSpeed();
	void setSpeed(float speed);

	void setDirection(float direction);
    float getDirection();
    
    CCPoint getTo();
	void setTo(CCPoint to);
    
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


    
    void updateDirection(float delta);
    void updateMoveAnimation();
    void didMoveStart();
    void didMoveStop();
	void didHit(CCPoint location);
    
    virtual void onMoveDirection(Message* message);
    virtual void onMoveDirectionStop(Message* message);
    virtual void onMoveTo(Message* message);

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
    
    CCPoint m_to;
    int m_directionFlagX;
    int m_directionFlagY;

	MoveState m_moveState;
    
    SEL_SCHEDULE m_update;
    
    bool m_hasEndPosition;

};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_MOVECOMPONENT_H_
