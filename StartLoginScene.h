#pragma once
#ifndef __STARTLOGIN_SCENE_H__
#define __STARTLOGIN_SCENE_H__

#include "cocos2d.h"

class StartLoginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    static void StartLoginScene::BGMOn();//ø™ º≤•∑≈±≥æ∞“Ù¿÷

    static void StartLoginScene::BGMOff();//‘›Õ£≤•∑≈±≥æ∞“Ù¿÷

    static void StartLoginScene::BGMContinue();//ºÃ–¯≤•∑≈±≥æ∞“Ù¿÷


    // implement the "static create()" method manually
    CREATE_FUNC(StartLoginScene);
};

static int BGM_ID;

#endif // __STARTLOGIN_SCENE_H__