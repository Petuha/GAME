#include "LVL.h"

LVL::LVL(int height, int width, int enterx, int entery, int exitx, int exity)
{
	if (enterx == exitx && entery == exity) throw std::invalid_argument("exit can not be enter");
	if (height == 1 && width == 1 || height <= 0 || width <= 0) throw std::invalid_argument("invalid field size");
	if (enterx < 0 || enterx > height || entery < 0 || entery > width) throw std::invalid_argument("invalid enter cords");
	if (exitx < 0 || exitx > height || exity < 0 || exity > width) throw std::invalid_argument("invalid exit cords");
	field.resize(height, width);
	this->enterx = enterx;
	this->entery = entery;
	this->exitx = exitx;
	this->exity = exity;
	field[enterx][entery] = (Square*)new SquareLadder(0, 0);
	field[exitx][exity] = (Square*)new SquareLadder(1, 0);
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (x == enterx && y == entery || x == exitx && y == exity) continue;
			field[x][y] = (Square*)new SquareFloor;
		}
	}
}

LVL::LVL(const LVL& rhs)
{
	field = rhs.field;
	for (auto& now : field) now = now->getclone();
	enemies = rhs.enemies;
	enterx = rhs.enterx;
	entery = rhs.entery;
	exitx = rhs.exitx;
	exity = rhs.exity;
}

LVL::LVL(LVL&& rhs) noexcept
{
	enemies = rhs.enemies;
	enterx = rhs.enterx;
	entery = rhs.entery;
	exitx = rhs.exitx;
	exity = rhs.exity;
	field = std::move(field);
}

LVL::~LVL()
{
	for (auto now : field) delete now;
}

LVL& LVL::operator=(const LVL& rhs)
{
	if (this == &rhs) return *this;
	for (auto& now : field) delete now;
	field = rhs.field;
	for (auto& now : field) now = now->getclone();
	enemies = rhs.enemies;
	enterx = rhs.enterx;
	entery = rhs.entery;
	exitx = rhs.exitx;
	exity = rhs.exity;
	return *this;
}

LVL& LVL::operator=(LVL&& rhs) noexcept
{
	if (this == &rhs) return *this;
	enemies = rhs.enemies;
	enterx = rhs.enterx;
	entery = rhs.entery;
	exitx = rhs.exitx;
	exity = rhs.exity;
	for (auto now : field) delete now;
	field = std::move(field);
	return *this;
}

void LVL::changesquaretype(int x, int y, SquareFloor square)
{
	delete field[x][y];
	field[x][y] = (Square*)new SquareFloor(std::move(square));
}

void LVL::changesquaretype(int x, int y, SquareDoor square)
{
	delete field[x][y];
	field[x][y] = (Square*)new SquareDoor(std::move(square));
}

void LVL::changesquaretype(int x, int y, SquareWall square)
{
	delete field[x][y];
	field[x][y] = (Square*)new SquareWall(std::move(square));
}

void LVL::changeladderupnext(int newnext)
{
	SquareLadder* ptr = (SquareLadder*)field[exitx][exity];
	ptr->setnextlvl(newnext);
}

void LVL::changeladderdownnext(int newnext)
{
	SquareLadder* ptr = (SquareLadder*)field[enterx][entery];
	ptr->setnextlvl(newnext);
}

bool LVL::possibleplacechest(int x, int y)
{
	if (!correctcords(x, y)) return 0;
	return getsquaretype(x, y) == squaretype::floor;
}

LVL& LVL::addenemy(Enemy enemy)
{
	if (enemy.xpos < 0 || enemy.xpos >= field.height() || enemy.ypos < 0 || enemy.ypos >= field.width()) {
		throw std::invalid_argument("incorrect enemy position");
	}
	enemies.push_back(std::move(enemy));
	return *this;
}

std::vector<Enemy>& LVL::getenemies()
{
	return enemies;
}

const Matrix<Square*>& LVL::getfield()
{
	return field;
}

squaretype LVL::getsquaretype(int x, int y)
{
	return field[x][y]->getsquaretype();
}

Square* LVL::getsquare(int x, int y)
{
	return field[x][y];
}

bool LVL::possiblestandon(int x, int y)
{
	if (x < 0 || x >= field.height() || y < 0 || y >= field.width()) return 0;
	Square* ptr = (Square*)field[x][y];
	return field[x][y]->possiblestandon();
}

bool LVL::correctcords(int x, int y)
{
	return x >= 0 && x < field.height() && y >= 0 && y < field.width();
}

LVL& LVL::additem(int x, int y, Item* item)
{
	if (field[x][y]->getsquaretype() != squaretype::floor) {
		throw std::invalid_argument("incorrect square");
	}
	SquareFloor* ptr = (SquareFloor*) field[x][y];
	ptr->additem(item);
	return *this;
}

LVL& LVL::addchest(int x, int y, Chest chest)
{
	if (field[x][y]->getsquaretype() != squaretype::floor) {
		throw std::invalid_argument("incorrect square");
	}
	SquareFloor* ptr = (SquareFloor*)field[x][y];
	ptr->addchest(std::move(chest));
	return *this;
}

bool LVL::moveenemy(Enemy& enemy, direction dir)
{
	enemy.looksight = dir;
	switch (dir)
	{
	case direction::up:
		if (possiblestandon(enemy.xpos - 1, enemy.ypos)) {
			enemy.xpos--;
			return 1;
		}
		break;
	case direction::down:
		if (possiblestandon(enemy.xpos + 1, enemy.ypos)) {
			enemy.xpos++;
			return 1;
		}
		break;
	case direction::left:
		if (possiblestandon(enemy.xpos, enemy.ypos - 1)) {
			enemy.ypos--;
			return 1;
		}
		break;
	case direction::right:
		if (possiblestandon(enemy.xpos, enemy.ypos + 1)) {
			enemy.ypos++;
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}

void LVL::setcordstoenter(Enemy& enemy)
{
	enemy.xpos = enterx;
	enemy.ypos = entery;
}

void LVL::setcordstoexit(Enemy& enemy)
{
	enemy.xpos = exitx;
	enemy.ypos = exity;
}
