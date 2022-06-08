/**
* @file FightScene.h
* @author wukef & wyf
*/

#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__


#include "Hero/Player.h"
#include "Hero/PolarBear.h"
#include "Utils/FightUtils.h"

#include "Hero/ChangYi.h"
#include "Hero/YunHe.h"
#include "Hero/ShunDe.h"
#include "Hero/SanYue.h"
#include "Hero/HaoQing.h"

#include "cocos2d.h"
using namespace std;

class FightScene : public cocos2d::Scene
{
private:

    Size _visibleSize;
    Vec2 _origin;

    Player* currentPlayer;

    Hero* AI;


    /*µÿÕº–≈œ¢ª„◊‹*/
    cocos2d::TMXTiledMap* _tileMap;
    TMXLayer* _background;	 			//±≥æ∞≤„
    TMXLayer* _barrier;					//’œ∞≠ŒÔÕº≤„
    TMXLayer* _collidable;				//≈ˆ◊≤ Ù–‘Õº≤„
    TMXLayer* _grass;					//≤›¥‘Õº≤„
    TMXLayer* _smoke;		         	//∂æ—ÃÕº≤„
    int _xSmokeMin;					//∂æ—ÃŒª÷√
    int	_xSmokeMax;					//∂æ—ÃŒª÷√
    int	_ySmokeMin;					//∂æ—ÃŒª÷√
    int	_ySmokeMax;					//∂æ—ÃŒª÷√
    Sprite* _smokeCell;		            //∂æ—Ãµ•‘™∏Ò



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

    void smokeMove();

    void setCamera();
    
    void FightScene::initMap();

    void FightScene::initHero();

    void FightScene::initAI();

    void FightScene::initUI();
    //CREATE_FUNC(FightScene);
    void FightScene::update(float dt);

    Vec2 tileCoordFormPosition(const Vec2& position);

    void FightScene::setPlayerPosition(Point position);
  
};

#endif // #define __FIGHT_SCENE_H__
