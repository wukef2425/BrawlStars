#include "Utils/GameData.h"
#include "Scene/FightScene.h"
#include "Scene/ChooseHero.h"

USING_NS_CC;

int GameData::remainingPlayer = OriginalPlayerNum;

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