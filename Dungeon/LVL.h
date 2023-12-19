#pragma once
#include "Square.h"
#include "../Matrix/Matrix.h"
#include "enums.h"
#include "Enemy.h"
#include <vector>
class LVL
{
private:
	Matrix<Square*> field;
	std::vector<Enemy> enemies;
	int enterx;
	int entery;
	int exitx;
	int exity;
public:
	LVL(int height, int width, int enterx, int entery, int exitx, int exity);
	LVL& operator=(const LVL& rhs);
	LVL& operator=(LVL&& rhs) noexcept;
	LVL(const LVL& rhs);
	LVL(LVL&& rhs) noexcept;
	~LVL();
	void changesquaretype(int x, int y, SquareFloor square);
	void changesquaretype(int x, int y, SquareDoor square);
	void changesquaretype(int x, int y, SquareWall square);
	void changeladderupnext(int newnext);
	void changeladderdownnext(int newnext);
	bool possibleplacechest(int x, int y);
	LVL& addenemy(Enemy enemy);
	std::vector<Enemy>& getenemies();
	const Matrix<Square*>& getfield();
	squaretype getsquaretype(int x, int y);
	Square* getsquare(int x, int y);
	bool possiblestandon(int x, int y);
	bool correctcords(int x, int y);
	LVL& additem(int x, int y, Item* item);
	LVL& addchest(int x, int y, Chest chest);
	bool moveenemy(Enemy& enemy, direction dir);
	void setcordstoenter(Enemy& enemy);
	void setcordstoexit(Enemy& enemy);
};