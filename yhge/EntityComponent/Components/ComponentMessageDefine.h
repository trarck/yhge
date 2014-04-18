#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_MESSAGEDEFINE_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_MESSAGEDEFINE_H_

#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

//message id从10000开始
enum
{
    //animation
    MSG_ANIMATION=10000,
    MSG_CHANGE_ANIMATION,
    MSG_ANIMATION_COMPLETE,
    //attack
    //normal attack
    MSG_ATTACK,
    //skill attack
    MSG_SKILL_ATTACK,
    MSG_SET_ATTACK_TARGET,
    MSG_AUTO_ATTACK,
    MSG_TARGET_DIE,
    MSG_BEATTACK,
    MSG_BEATTACK_FINISH,
    //move
    MSG_MOVE_TO,
    MSG_MOVE_DIRECTION,
    MSG_MOVE_DIRECTION_TO,
    MSG_MOVE_DIRECTION_STOP,
	MSG_MOVE_PATH,
    MSG_MOVE_PATH_FROM,
    MSG_MOVE_STOP,
    MSG_MOVE_COMPLETE,
    MSG_MOVE_STOPED,
    //sprite renderer
    MSG_RUN_ACTION,
    MSG_STOP_ACTION,
    MSG_STOP_ACTION_BY_TAG,
    MSG_RUN_ANIMATE,
    MSG_STOP_ANIMATE,
    MSG_STOP_ANIMATE_BY_TAG,
    //position
    MSG_POSITION_CHANGE,
    //entity
    MSG_ENTITY_DIE
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_MESSAGEDEFINE_H_
