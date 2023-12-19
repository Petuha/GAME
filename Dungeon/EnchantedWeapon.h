#pragma once
#include "Weapon.h"
#include "enums.h"
class EnchantedWeapon : public Weapon
{
private:
	species efficientagainst;
	int ratio;
public:
	operator Item* () override;
	Damage getdamage() override;
	EnchantedWeapon(int damage, species efficientagainst, int ratio, std::string name = "");
	Item* getclone() override;
};