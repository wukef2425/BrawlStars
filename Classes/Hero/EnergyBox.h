#ifndef __ENERGYBOX_H__
#define __ENERGYBOX_H__

#include "Entity/Player.h"

class EnergyBox :public Hero
{
private:

public:

    static Hero* createBox(Vec2 position);// 传入position在那个位置生成宝箱
};

#endif