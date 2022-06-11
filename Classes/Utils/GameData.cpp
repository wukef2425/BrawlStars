#include "Utils/GameData.h"
#include "Scene/FightScene.h"
#include "Scene/ChooseHero.h"

USING_NS_CC;

GameData::AllHero GameData::_hero = GameData::YunHe;
int GameData::remainingPlayer = 2;

int GameData::getRemainingPlayer()
{
	return remainingPlayer;
}

void GameData::deleteDiedPlayer()
{
	remainingPlayer--;
}