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

    void InstructionScene::initReturnMenu();//·µ»ØÖ÷Ò³Ãæ

protected:

    void InstructionScene::menuReturnCallback(Ref* pSender);

    cocos2d::Menu* returnButton_;
};

#endif // #define __INSTRUCTION_SCENE_H__
