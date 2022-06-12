#include "GameOverScene.h"
#include "Scene/StartMenuScene.h"
#include "Utils/GameData.h"

#include "cocos2d.h"
#include <string>

USING_NS_CC;


Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();

	_origin = Director::getInstance()->getVisibleOrigin();

	auto* setScene = Sprite::create("Scene/GameOverScene.png");      
	setScene->setScale(0.8f);
	setScene->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);     
	addChild(setScene, 0);

	initTrophy();

	initHero();
	
	scheduleOnce(SEL_SCHEDULE(&GameOverScene::ChangeScene), 3.0f);

	
	return true;
}

void GameOverScene::initTrophy()
{
	INT32 trophy=0;
	INT32 ranking= GameData::getRemainingPlayer();

	switch (ranking)
	{
		case 1:
			trophy = 10;
			break;
		case 2:
			trophy = 9;
			break;
		case 3:
			trophy = 8;
			break;
		case 4:
			trophy = 7;
			break;
		case 5:
			trophy = 6;
			break;
		case 6:
			trophy = 5;
			break;
		case 7:
			trophy = 4;
			break;
		case 8:
			trophy = 3;
			break;
		case 9:
			trophy = 2;
			break;
		case 10:
			trophy = 0;
			break;
		default:
			break;
	}

	GameData::_trophy = GameData::_trophy + trophy;
	if (ranking == 1)
	{
		auto victory= Sprite::create("Scene/Victory.png");
		victory->setPosition(_origin.x + 4*_visibleSize.width / 7, _origin.y + _visibleSize.height / 5);
		addChild(victory, 1);

	}
	auto _ranking = Label::createWithTTF(StringUtils::format("Ranking: %d", GameData::getRemainingPlayer()).c_str(), "fonts/arial.ttf", 55);
	_ranking->setColor(Color3B::YELLOW);
	_ranking->enableShadow();
	_ranking->enableGlow(Color4B(255, 0, 0, 0));
	_ranking->setAnchorPoint(Vec2(0, 1));
	_ranking->setPosition(Vec2(_origin.x+ _visibleSize.width / 17, 14*_visibleSize.height/15 + _origin.y));
	this->addChild(_ranking, 1);

	auto _trophy = Label::createWithTTF(StringUtils::format("%d",trophy).c_str(), "fonts/arial.ttf", 70);
	_trophy->setColor(Color3B::YELLOW);
	_trophy->enableShadow();
	_trophy->enableGlow(Color4B(255, 0, 0, 0));
	_trophy->setAnchorPoint(Vec2(0, 1));
	_trophy->setPosition(Vec2(_origin.x+ _visibleSize.width/6, 5*_visibleSize.height/6 + _origin.y));
	this->addChild(_trophy, 1);
}

void GameOverScene::initHero()
{
	int chooseHeroNumber = GameData::getChooseHero();
	switch (chooseHeroNumber)
	{
	case ChangYiNumber:
		character = Sprite::create("Hero/EndHero/ChangYi.png");
		break;
	case YunHeNumber:
		character = Sprite::create("Hero/EndHero/YunHe.png");
		break;
	case HaoQingNumber:
		character = Sprite::create("Hero/EndHero/HaoQing.png");
		break;
	case SanYueNumber:
		character = Sprite::create("Hero/EndHero/SanYue.png");
		break;
	case ShunDeNumber:
		character = Sprite::create("Hero/EndHero/ShunDe.png");
		break;
	default:
		break;
	}

	character->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2);
	addChild(character, 1);
}
void GameOverScene::ChangeScene(float dt)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StartMenuScene::createScene()));
}