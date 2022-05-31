/**
* @file FightScene.h
* @author wukef & wyf
*/

#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "Hero/Player.h"

class FightScene : public cocos2d::Scene
{
private:

    Player* currentPlayer;

public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void FightScene::listenToUserOperation(const std::string& filename);

    bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent);


    CREATE_FUNC(FightScene);

};

#endif // #define __FIGHT_SCENE_H__
