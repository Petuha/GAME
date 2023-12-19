#pragma once
#include <vector>
#include "Hero.h"
#include "Enemy.h"
#include "LVL.h"
#include "enums.h"
class Dungeon
{
public:
	Dungeon(species herorace, std::string heroname, std::vector<LVL> lvls);
	bool useladder();
	bool possibleuseladder();
	bool bodymove(Enemy& enemy, direction dir);
	bool pickitem();
	bool possiblepickitem();
	bool possibleopenchest();
	bool possibleattack();
	bool attack();
	bool tryopenchest();
	bool tryopendoor();
	bool unequip(itemtype type, int i = 0);
	bool takeitem(int i);
	const std::vector<Item*>& accesschestitems();
	LVL& herolvl();
	LVL& operator[](int i);
	~Dungeon();
	bool gameover;
	Hero hero;
	bool attack(Enemy& atacker, Enemy& defender);
	bool usepotion(int i);
	bool possiblelvlup();
	bool lvlup(atribute atr);
private:
	std::vector<Enemy*> enemiesnearby(Enemy& enemy);
	std::vector<LVL> lvls;
};