#include "Dungeon.h"

Dungeon::~Dungeon()
{
}

Dungeon::Dungeon(species herorace, std::string heroname, std::vector<LVL> lvlslist) : lvls(std::move(lvlslist)),
hero(0, 1, herorace, std::move(heroname))
{
	gameover = 0;
	if (!lvls.size()) return;
	lvls.begin()->changeladderdownnext(lvls.size() - 1);
	lvls.rbegin()->changeladderupnext(0);
	for (int i = 1; i < lvls.size(); i++) lvls[i].changeladderdownnext(i - 1);
	for (int i = lvls.size() - 2; i >= 0; i--) lvls[i].changeladderupnext(i + 1);
	herolvl().setcordstoenter(hero);
}

bool Dungeon::useladder()
{
	if (!possibleuseladder()) return 0;
	SquareLadder* ptr = (SquareLadder*)herolvl().getsquare(hero.xpos, hero.ypos);
	hero.stage = ptr->getnextlvl();
	if (ptr->ladderup) herolvl().setcordstoenter(hero);
	else herolvl().setcordstoexit(hero);
}

bool Dungeon::possibleuseladder()
{
	return lvls[hero.stage].getsquaretype(hero.xpos, hero.ypos) == squaretype::ladder;
}

bool Dungeon::attack(Enemy& atacker, Enemy& defender)
{
	if (atacker.xpos != defender.xpos || atacker.ypos != defender.ypos) return 0;
	atacker.attack(defender);
	if (&defender == &hero && hero.isdead()) gameover = 1;
	if (defender.isdead()) {
		std::vector<std::pair<int, int>> change = { {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
		for (std::pair<int, int> p : change) {
			if (!lvls[hero.stage].possibleplacechest(defender.xpos + p.first, defender.ypos + p.second)) {
				continue;
			}
			lvls[hero.stage].addchest(defender.xpos + p.first, defender.ypos + p.second, defender.chestafterdeath());
			return 1;
		}
		throw std::runtime_error("can't place chest");
	}
	return 0;
}

bool Dungeon::usepotion(int i)
{
	return hero.usepotion(i);
}

bool Dungeon::possiblelvlup()
{
	return hero.getlvluppoints();
}

bool Dungeon::lvlup(atribute atr)
{
	return hero.lvlup(atr);
}

bool Dungeon::bodymove(Enemy& enemy, direction dir)
{
	return lvls[hero.stage].moveenemy(enemy, dir);
}

bool Dungeon::pickitem()
{
	if (!possiblepickitem()) return 0;
	SquareFloor* ptr = (SquareFloor*)lvls[hero.stage].getsquare(hero.xpos, hero.ypos);
	if (!hero.possibleequip(ptr->item)) return 0;
	hero.equipitem(ptr->item);
	ptr->item = 0;
	return 1;
}

bool Dungeon::possiblepickitem()
{
	if (lvls[hero.stage].getsquaretype(hero.xpos, hero.ypos) != squaretype::floor) return 0;
	SquareFloor* ptr = (SquareFloor*)lvls[hero.stage].getsquare(hero.xpos, hero.ypos);
	if (!ptr->item) return 0;
	return 1;
}

bool Dungeon::possibleopenchest()
{
	if (herolvl().getsquaretype(hero.xpos, hero.ypos) != squaretype::floor) return 0;
	SquareFloor* ptr = (SquareFloor*)herolvl().getsquare(hero.xpos, hero.ypos);
	return ptr->chest;
}

bool Dungeon::possibleattack()
{
	return enemiesnearby(hero).size() != 0;
}

bool Dungeon::attack()
{
	if (!possibleattack()) return 0;
	Enemy* target = enemiesnearby(hero)[0];
	for (auto& now : enemiesnearby(hero)) {
		if (now->hp < target->hp) target = now;
	}
	if (attack(hero, *target)) {
		for (int i = target - &herolvl().getenemies()[0] + 1; i < herolvl().getenemies().size(); i++) {
			std::swap(herolvl().getenemies()[i - 1], herolvl().getenemies()[i]);
		}
		herolvl().getenemies().pop_back();
	}
	return 1;
}

bool Dungeon::tryopenchest()
{
	if (lvls[hero.stage].getsquaretype(hero.xpos, hero.ypos) != squaretype::floor) return 0;
	SquareFloor* ptr = (SquareFloor*)lvls[hero.stage].getsquare(hero.xpos, hero.ypos);
	if (!ptr->chest) return 0;
	ptr->chest->trytoopen(hero);
	return ptr->chest->cantakeitem();
}

std::pair<int, int> cordschange(direction dir) {
	std::pair<int, int> change = { 0, 0 };
	switch (dir) {
	case direction::up:
		change = { -1, 0 };
		break;
	case direction::down:
		change = { 1, 0 };
		break;
	case direction::left:
		change = { 0, -1 };
		break;
	case direction::right:
		change = { 0, 1 };
		break;
	default:
		break;
	}
	return change;
}

bool Dungeon::tryopendoor()
{
	std::pair<int, int> doorcords = cordschange(hero.looksight);
	doorcords.first += hero.xpos;
	doorcords.second += hero.ypos;
	if (!lvls[hero.stage].correctcords(doorcords.first, doorcords.second)) {
		return 0;
	}
	if (lvls[hero.stage].getsquaretype(doorcords.first, doorcords.second) != squaretype::door) {
		return 0;
	}
	SquareDoor* ptr = (SquareDoor*)lvls[hero.stage].getsquare(doorcords.first, doorcords.second);
	ptr->trytoopen(hero);
	return 1;
}

bool Dungeon::unequip(itemtype type, int i)
{
	return hero.unequip(type, i);
}

bool Dungeon::takeitem(int i)
{
	SquareFloor* sptr = (SquareFloor*) herolvl().getsquare(hero.xpos, hero.ypos);
	Item* ptr = sptr->chest->accessitems()[i];
	if (!hero.possibleequip(ptr)) return 0;
	hero.equipitem(sptr->chest->takeitem(i));
	return 1;
}

const std::vector<Item*>& Dungeon::accesschestitems()
{
	if (lvls[hero.stage].getsquaretype(hero.xpos, hero.ypos) != squaretype::floor) return {};
	SquareFloor* ptr = (SquareFloor*)lvls[hero.stage].getsquare(hero.xpos, hero.ypos);
	if (!ptr->chest || !ptr->chest->cantakeitem()) return {};
	return ptr->chest->accessitems();
}

std::vector<Enemy*> Dungeon::enemiesnearby(Enemy& enemy)
{
	std::vector<Enemy*> ret;
	for (auto& now : lvls[hero.stage].getenemies()) {
		if (now.xpos == hero.xpos && now.ypos == hero.ypos) ret.push_back(&now);
	}
	return ret;
}

LVL& Dungeon::herolvl()
{
	return lvls[hero.stage];
}

LVL& Dungeon::operator[](int i)
{
	return lvls[i];
}
