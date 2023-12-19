#include "Square.h"
#include <stdexcept>
#include "LVL.h"

Square& SquareFloor::addchest(Chest chest)
{
	if (item) {
		this->chest = new Chest(std::move(chest));
		*this->chest += item;
		item = 0;
	}
	else if (this->chest) {
		*this->chest += std::move(chest);
	}
	else {
		this->chest = new Chest(std::move(chest));
	}
	return *this;
}

Square& SquareFloor::additem(Item* item)
{
	if (this->item) {
		throw std::runtime_error("item already exist");
	}
	else if (this->chest) {
		*this->chest += item;
	}
	else {
		this->item = item;
	}
	return *this;
}

bool SquareFloor::possiblestandon()
{
	return 1;
}

Square* SquareFloor::getclone()
{
	SquareFloor* ptr = new SquareFloor(*this);
	ptr->chest = (chest ? new Chest(*chest) : 0);
	ptr->item = (item ? item->getclone() : 0);
	return ptr;
}

squaretype SquareFloor::getsquaretype()
{
	return squaretype::floor;
}

SquareFloor::SquareFloor()
{
	item = 0;
	chest = 0;
}

SquareFloor::~SquareFloor()
{
	delete item;
	delete chest;
}

void SquareDoor::trytoopen(Hero& hero)
{
	if (isopened) return;
	if (!hero.keys || !hero.keys->keysleft()) return;
	hero.keys--;
	int agility = std::min(1, hero.getatribute(atribute::agility));
	int chance = std::max(1.0, 100 - 800.0 / agility);
	isopened = rand() % 100 <= chance;
}

SquareDoor::SquareDoor(bool isopened, int lvl = 1)
{
	this->isopened = isopened;
	this->lvl = lvl;
}

bool SquareDoor::possiblestandon()
{
	return isopened;
}

Square* SquareDoor::getclone()
{
	return new SquareDoor(*this);
}

squaretype SquareDoor::getsquaretype()
{
	return squaretype::door;
}


bool SquareWall::possiblestandon()
{
	return 0;
}

Square* SquareWall::getclone()
{
	return new SquareWall(*this);
}

squaretype SquareWall::getsquaretype()
{
	return squaretype::wall;
}

SquareLadder::SquareLadder(bool ladderup, int nextlvl)
{
	this->ladderup = ladderup;
	this->nextlvl = nextlvl;
}

bool SquareLadder::possiblestandon()
{
	return 1;
}

Square* SquareLadder::getclone()
{
	return new SquareLadder(*this);
}

squaretype SquareLadder::getsquaretype()
{
	return squaretype::ladder;
}

int SquareLadder::getnextlvl()
{
	return nextlvl;
}

void SquareLadder::setnextlvl(int newnextlvl)
{
	nextlvl = newnextlvl;
}

Square::~Square()
{
}
