#pragma once
#ifndef __SANYUE_H__
#define __SANYUE_H__

#include "Hero/Player.h"

class SanYue :public Player
{
private:
    /* 获取屏幕大小并按比例设置player位置 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static SanYue* createPlayer();

    static Hero* createAI();
};

#endif