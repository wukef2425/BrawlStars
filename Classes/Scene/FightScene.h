#pragma once
#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"

class FightScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(FightScene);



    

};

#endif // #define __FIGHT_SCENE_H__
