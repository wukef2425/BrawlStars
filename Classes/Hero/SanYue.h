#pragma once
#ifndef __SANYUE_H__
#define __SANYUE_H__

#include "Entity/Player.h"

class SanYue :public Player
{
public:

    static SanYue* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;

    void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition) override;
};

#endif