#pragma once
#ifndef __SHUNDE_H__
#define __SHUNDE_H__

#include "Hero/Player.h"

class ShunDe :public Player
{
private:
    /* 获取屏幕大小并按比例设置player位置 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static ShunDe* createPlayer();

    static Hero* createAI();

    void ultimateSkill() override;
};

#endif