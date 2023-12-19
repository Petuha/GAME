#pragma once
#include "Enemy.h"
#include "enums.h"
class LVL;
class Hero : public Enemy
{
private:
public:
	int stage;
	Hero(int stage, int lvl, species race, std::string name);
	Hero& operator=(const Hero& rhs);
	Hero& operator=(Hero&& rhs) noexcept;
	Hero(const Hero& rhs);
	Hero(Hero&& rhs) noexcept;
};