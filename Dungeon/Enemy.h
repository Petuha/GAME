#pragma once
#include <vector>
#include <string>
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Item.h"
#include "BunchOfKeys.h"
#include "Damage.h"
#include "ArtifactArmor.h"
#include "ArtifactWeapon.h"
#include "EnchantedWeapon.h"
#include "enums.h"
class Chest;
constexpr int MAX_LVL = 100;
class Enemy
{
public:
	Enemy(int lvl, species race, std::string name = "", int xpos = 0, int ypos = 0);
	bool attack(Enemy& target); // 1 - stays alive, 0 - is dead
	void equipitem(Item* item);
	bool possibleequip(Item* item);
	bool unequip(itemtype type, int i = 0);
	int getatribute(atribute atr);
	const std::vector<Potion*>& getpotions();
	bool usepotion(int i);
	bool lvlup(atribute stat);
	bool isdead();
	int getlvluppoints();
	~Enemy();
	void receiveexperience(long long exp);
	Enemy& operator=(const Enemy& rhs);
	Enemy& operator=(Enemy&& rhs) noexcept;
	Enemy(const Enemy& rhs);
	Enemy(Enemy&& rhs) noexcept;
	int hp;
	int xpos;
	int ypos;
	Chest chestafterdeath();
	BunchOfKeys* keys;
	direction looksight;
	species race;
	bool hasweapon();
	bool hasarmor(armortype type);
	bool haskeys();
	std::string name;
protected:
	bool placedchest = 0;
	long double expratio;
	long long experiencetolvlup;
	long long getexperienceafterdeath();
	int lvluppoints;

	std::vector<int> atributes;
	int lvl;
	Weapon* weapon;
	std::vector<Armor*> armor;
	std::vector<Potion*> potions;
	int getdefence();
	bool receivedamage(Damage damage);
};