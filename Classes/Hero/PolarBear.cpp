/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* PolarBear::createAI()
{
    auto player = AI::create("Hero/FightHero/polar-bear.png");

    player->health_ = 100;//当前生命

    player->healthInit_ = 100;//最大生命

    player->attack_ = 20;//攻击值

    player->defend_ = 8;//防御值

    return player;
}