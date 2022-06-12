#pragma once
#ifndef __HAOQING_H__
#define __HAOQING_H__

#include "Entity/Player.h"

class HaoQing :public Player
{
public:

    static HaoQing* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;

    void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition) override;
};

#endif