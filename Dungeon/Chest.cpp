#include "Chest.h"
#include <stdexcept>

Chest::Chest(int lvl)
{
	if (lvl < 0) throw std::invalid_argument("invalid chest lvl");
	isopened = !lvl;
	this->lvl = lvl;
}

Chest::Chest(const Chest& rhs)
{
	lvl = rhs.lvl;
	items = rhs.items;
	for (auto& now : items) now = now->getclone();
	isopened = rhs.isopened;
}

Chest::Chest(Chest&& rhs) noexcept
{
	lvl = rhs.lvl;
	items = std::move(rhs.items);
	isopened = rhs.isopened;
}

Chest& Chest::operator=(const Chest& rhs)
{
	lvl = rhs.lvl;
	for (auto now : items) delete now;
	items = rhs.items;
	for (auto& now : items) now = now->getclone();
	isopened = rhs.isopened;
	return *this;
}

Chest& Chest::operator=(Chest&& rhs) noexcept
{
	lvl = rhs.lvl;
	for (auto now : items) delete now;
	items = std::move(rhs.items);
	isopened = rhs.isopened;
	return *this;
}

bool Chest::cantakeitem()
{
	return isopened;
}

void Chest::trytoopen(Hero& hero)
{
	if (isopened) return;
	if (!hero.keys || !hero.keys->keysleft()) return;
	hero.keys->operator--();
	int agility = std::min(1, hero.getatribute(atribute::agility));
	int chance = std::max(1.0, 100 - 800.0 / agility);
	isopened = rand() % 100 <= chance;
}

const std::vector<Item*>& Chest::accessitems()
{
	return items;
}

int Chest::itemsleft()
{
	return items.size();
}

Item* Chest::takeitem(int i)
{
	if (i < 0 || i >= items.size()) throw std::runtime_error("invalid item index");
	if (!isopened) return 0;
	Item* ret = items[i];
	for (int j = i + 1; j < items.size(); j++) items[j - 1] = items[j];
	items.pop_back();
	return ret;
}

Chest& Chest::operator+=(Chest chest)
{
	lvl = std::max(lvl, chest.lvl);
	int i = items.size();
	items.resize(items.size() + chest.items.size());
	for (int j = 0; j < chest.items.size(); j++) {
		items[i] = chest.items[j];
		i++;
	}
	chest.items.clear();
	return *this;
}

Chest& Chest::operator+=(Item* item)
{
	if (!item) return *this;
	items.push_back(item);
	return *this;
}

Chest::~Chest()
{
	for (auto item : items) delete item;
}
