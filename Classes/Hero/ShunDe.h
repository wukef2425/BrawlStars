#pragma once
#ifndef __SHUNDE_H__
#define __SHUNDE_H__

#include "Entity/Player.h"

class ShunDe :public Player
{
public:

    static ShunDe* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;

    void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition) override;
};

#endif