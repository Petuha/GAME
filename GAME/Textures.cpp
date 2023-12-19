#include "Textures.h"
using namespace std;
using namespace sf;
Textures::Textures(string path)
{
	wstring temppath(path.begin(), path.end());
	path += "Sprites";
	races.resize((int)species::LAST_ITEM, vector<Texture>(4));
	map<direction, string> dirs;
	dirs[direction::up] = "up";
	dirs[direction::down] = "down";
	dirs[direction::left] = "left";
	dirs[direction::right] = "right";
	for (auto& now : dirs) {
		if (!races[(int)species::human][(int)now.first].loadFromFile(path + "/species/human/" + now.second + ".png")) {
			throw runtime_error("No sprite.");
		}
		if (!races[(int)species::demon][(int)now.first].loadFromFile(path + "/species/demon/" + now.second + ".png")) {
			throw runtime_error("No sprite.");
		}
		if (!races[(int)species::skeleton][(int)now.first].loadFromFile(path + "/species/skeleton/" + now.second + ".png")) {
			throw runtime_error("No sprite.");
		}
	}
	items.resize((int)itemtype::LAST_ITEM);
	if (!items[(int)itemtype::armor].loadFromFile(path + "/itemonground/armor.png")) {
		throw runtime_error("No sprite.");
	}
	if (!items[(int)itemtype::artifactarmor].loadFromFile(path + "/itemonground/armor.png")) {
		throw runtime_error("No sprite.");
	}
	if (!items[(int)itemtype::keys].loadFromFile(path + "/itemonground/keys.png")) {
		throw runtime_error("No sprite.");
	}
	if (!items[(int)itemtype::potion].loadFromFile(path + "/itemonground/potion.png")) {
		throw runtime_error("No sprite.");
	}
	if (!items[(int)itemtype::weapon].loadFromFile(path + "/itemonground/weapon.png")) {
		throw runtime_error("No sprite.");
	}
	if (!items[(int)itemtype::artifactweapon].loadFromFile(path + "/itemonground/weapon.png")) {
		throw runtime_error("No sprite.");
	}
	squares.resize((int)squaretype::LAST_ITEM + 2);
	map<squaretype, string> floors;
	floors[squaretype::door] = "doorclosed";
	floors[squaretype::floor] = "floor";
	floors[squaretype::ladder] = "ladderup";
	floors[squaretype::wall] = "wall";
	for (auto& now : floors) {
		if (!squares[(int)now.first].loadFromFile(path + "/floor/" + now.second + ".png")) {
			throw runtime_error("No sprite.");
		}
	}
	if (!squares[squares.size() - 1].loadFromFile(path + "/floor/dooropened.png")) {
		throw runtime_error("No sprite.");
	}
	if (!squares[squares.size() - 2].loadFromFile(path + "/floor/ladderdown.png")) {
		throw runtime_error("No sprite.");
	}
	chests.resize(2);
	if (!chests[0].loadFromFile(path + "/chest/closed.png")) {
		throw runtime_error("No sprite.");
	}
	if (!chests[1].loadFromFile(path + "/chest/opened.png")) {
		throw runtime_error("No sprite.");
	}

	temppath += L"plugin/Sprites/";
	path += "/";
	for (auto& file : std::filesystem::recursive_directory_iterator(temppath)) {
		string name = file.path().filename().string();
		for (int i = 0; i < 4 && name.size(); i++) name.pop_back();
		if (!potions[name].loadFromFile(file.path().string().c_str())) {
			potions.erase(name);
			throw runtime_error("Could not load plugin sprite.");
		}
	}
}

Texture* Textures::getenemy(species race, direction dir)
{
	return &races[(int)race][(int)dir];
}

Texture* Textures::getenemy(Enemy& enemy)
{
	return &races[(int)enemy.race][(int)enemy.looksight];
}

Texture* Textures::getsquare(Square* square)
{
	if (square->getsquaretype() == squaretype::door) {
		SquareDoor* ptr = (SquareDoor*)square;
		if (ptr->isopened) return &squares[squares.size() - 1];
	}
	if (square->getsquaretype() == squaretype::ladder) {
		SquareLadder* ptr = (SquareLadder*)square;
		if (!ptr->ladderup) return &squares[squares.size() - 2];
	}
	return &squares[(int)square->getsquaretype()];
}

Texture* Textures::getitem(Item* item)
{
	if (item->getitemtype() != itemtype::potion) {
		return &items[(int)item->getitemtype()];
	}
	Potion* ptr = (Potion*)item;
	if (potions.find(ptr->getid()) == potions.end()) return &items[(int)itemtype::potion];
	return &potions[ptr->getid()];
}

Texture* Textures::getitem(itemtype type)
{
	return &items[(int)type];
}

Texture* Textures::getchest(Chest* chest)
{
	return &chests[chest->cantakeitem()];
}
