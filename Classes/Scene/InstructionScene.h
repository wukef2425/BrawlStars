#pragma once
#ifndef __INSTRUCTION_SCENE_H__
#define __INSTRUCTION_SCENE_H__

#include "cocos2d.h"

class InstructionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(InstructionScene);
};

#endif // #define __INSTRUCTION_SCENE_H__
