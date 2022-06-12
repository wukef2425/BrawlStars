#pragma once
#ifndef __YUNHE_H__
#define __YUNHE_H__

#include "Entity/Player.h"

class YunHe :public Player
{
public:

    static YunHe* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;

    void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition) override;
};

#endif