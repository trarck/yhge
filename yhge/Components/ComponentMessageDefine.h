//
//  GameMessage.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#ifndef GAME_MESSAGES_H_
#define GAME_MESSAGES_H_

#include "CCMessage.h"

//message id从10000开始
enum
{
    MSG_ANIMATION=10000,
    MSG_CHANGE_ANIMATION,
    //attack
    MSG_ATTACK,
    MSG_SET_ATTACK_TARGET,
    MSG_AUTO_ATTACK,
    MSG_TARGET_DIE,
    //move
    MSG_MOVE_TO,
    MSG_MOVE_DIRECTION,
    MSG_MOVE_DIRECTION_TO,
    MSG_MOVE_DIRECTION_STOP,
	MSG_MOVE_PATH
};



#endif //GAME_MESSAGES_H_
