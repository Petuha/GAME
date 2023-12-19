#pragma once
#include "Hero.h"
#include "Item.h"
#include "enums.h"
class Chest
{
private:
	int lvl;
	std::vector<Item*> items;
	bool isopened;
public:
	Chest(int lvl);
	Chest(const Chest& rhs);
	Chest(Chest&& rhs) noexcept;
	Chest& operator=(const Chest& rhs);
	Chest& operator=(Chest&& rhs) noexcept;
	bool cantakeitem();
	void trytoopen(Hero& hero);
	const std::vector<Item*>& accessitems();
	int itemsleft();
	Item* takeitem(int i);
	Chest& operator+=(Chest chest);
	Chest& operator+=(Item* item);
	~Chest();
};