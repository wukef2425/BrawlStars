/**
* @file FightScene.h
* @author wukef & wyf
*/

#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "Hero/Player.h"
#include "Hero/PolarBear.h"

class FightScene : public cocos2d::Scene
{
private:

    Player* currentPlayer;

    Hero* AI;

    cocos2d::TMXTiledMap* _tileMap;

public:

    cocos2d::Scene* createScene();
    static FightScene* create(TMXTiledMap* map);
    FightScene(TMXTiledMap* map);

    //static cocos2d::Scene* createScene();

    virtual bool init();

    void listenToUserOperation();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent);

    void createAI(float delta);

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

    void showSpark(const std::string& filename, cocos2d::Node*& node);

    void bindPlayer(Player* player);

    void setCamera();

    void loadingFightScene();

    //CREATE_FUNC(FightScene);

};

#endif // #define __FIGHT_SCENE_H__
