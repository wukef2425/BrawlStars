#include "Utils/FightUtils.h"
#include "Scene/FightScene.h"
#include "Scene/ChooseHero.h"

USING_NS_CC;

FightUtils::AllMap FightUtils::_map = FightUtils::MapA;
FightUtils::AllHero FightUtils::_hero = FightUtils::ChangYi;
INT32 FightUtils::_heroNumber = 0;
