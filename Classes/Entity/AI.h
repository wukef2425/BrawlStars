/**
* @file AI.h
* @author wukef
*/

#ifndef __AI_H__
#define __AI_H__

#include "Entity/Hero.h"

class AI : public Hero
{
public:
    static Hero* create(const std::string& filename);
};

#endif
