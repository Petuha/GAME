#pragma once
#include "Item.h"
#include "Chest.h"
#include "enums.h"

class Square
{
public:
	virtual bool possiblestandon() = 0;
	virtual squaretype getsquaretype() = 0;
	virtual Square* getclone() = 0;
	virtual ~Square();
};

class SquareFloor : protected Square
{
private:
public:
	Item* item;
	Chest* chest;
	Square& addchest(Chest chest);
	Square& additem(Item* item);
	bool possiblestandon() override;
	Square* getclone() override;
	squaretype getsquaretype() override;
	SquareFloor();
	~SquareFloor() override;
};

class SquareDoor : protected Square
{
	int lvl;
public:
	bool isopened;
	void trytoopen(Hero& hero);
	SquareDoor(bool isopened, int lvl);
	bool possiblestandon() override;
	Square* getclone() override;
	squaretype getsquaretype() override;
};

class SquareWall : protected Square
{
public:
	bool possiblestandon() override;
	Square* getclone() override;
	squaretype getsquaretype() override;
};

class SquareLadder : protected Square
{
private:
	int nextlvl;
public:
	bool ladderup;
	SquareLadder(bool ladderup, int nextlvl);
	int getnextlvl();
	void setnextlvl(int newnextlvl);
	bool possiblestandon() override;
	Square* getclone() override;
	squaretype getsquaretype() override;
};