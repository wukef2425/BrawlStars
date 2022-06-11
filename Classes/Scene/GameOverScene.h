#pragma once
#ifndef __GAMEOVER_SCENE__H__
#define __GAMEOVER_SCENE__H__
#include "cocos2d.h"

USING_NS_CC;
class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void GameOverScene::ChangeScene(float dt);

    void GameOverScene::initTrophy();

    void GameOverScene::initHero();

    CREATE_FUNC(GameOverScene);

private:

    Size _visibleSize;
    Vec2 _origin;

    Sprite* character;
};

#endif // __GAMEOVER_SCENE__H__
