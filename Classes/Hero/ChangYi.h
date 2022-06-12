#pragma once
#ifndef __CHANGYI_H__
#define __CHANGYI_H__

#include "Entity/Player.h"

class ChangYi :public Player
{
public:

    static ChangYi* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;

    void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition) override;
};

#endif