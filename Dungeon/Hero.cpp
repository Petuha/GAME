#include "Hero.h"
#include "LVL.h"

Hero::Hero(int stage, int lvl, species race, std::string name) :
	Enemy(lvl, race, std::move(name))
{
	this->stage = stage;
}

Hero& Hero::operator=(const Hero& rhs)
{
	this->Enemy::operator=(rhs);
	stage = rhs.stage;
	return *this;
}

Hero& Hero::operator=(Hero&& rhs) noexcept
{
	this->Enemy::operator=(std::move(rhs));
	stage = rhs.stage;
	return *this;
}

Hero::Hero(const Hero& rhs) : Enemy(rhs)
{
	stage = rhs.stage;
}

Hero::Hero(Hero&& rhs) noexcept : Enemy(std::move(rhs))
{
	stage = rhs.stage;
}
