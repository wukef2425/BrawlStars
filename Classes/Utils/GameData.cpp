#include "Utils/GameData.h"
#include "Scene/FightScene.h"
#include "Scene/ChooseHero.h"

USING_NS_CC;

int GameData::remainingPlayer = OriginalPlayerNum;
int GameData::_chooseHero=ChangYiNumber;

int GameData::getRemainingPlayer()
{
	return remainingPlayer;
}

void GameData::deleteDiedPlayer()
{
	remainingPlayer--;
}

void GameData::resetPlayerNum()
{
	remainingPlayer = OriginalPlayerNum;
}

int GameData::getChooseHero()
{
	return _chooseHero;
}
//修改人物，非常无奈的笨办法
void GameData::ChangeHeroToShunDe()
{
	log("ShunDe");
	_chooseHero = ShunDeNumber;
}
void GameData::ChangeHeroToHaoQing()
{
	log("HaoQing");
	_chooseHero = HaoQingNumber;
}
void GameData::ChangeHeroToChangYi()
{
	log("ChangYi");
	_chooseHero = ChangYiNumber;
}
void GameData::ChangeHeroToYunHe()
{
	log("YunHe");
	_chooseHero = YunHeNumber;
}
void GameData::ChangeHeroToSanYue()
{
	log("SanYue");
	_chooseHero = SanYueNumber;
}