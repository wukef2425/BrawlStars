#ifndef __ENERGYBOX_H__
#define __ENERGYBOX_H__

#include "Entity/Player.h"

class EnergyBox :public Hero
{
private:
    /* 获取屏幕大小并按比例设置player位置 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static Hero* createBox(Vec2 position);// 传入position在那个位置生成宝箱
};

#endif