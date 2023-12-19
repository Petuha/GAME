#pragma once
#include "Weapon.h"
#include <string>
#include "enums.h"
class ArtifactWeapon : public Weapon
{
private:
	atribute stat;
	int boost;
public:
	operator Item* () override;
	itemtype getitemtype() override;
	atribute getatribute();
	int getboost();
	ArtifactWeapon(int damage, atribute stat, int boost, std::string name = "");
	Damage getdamage() override;
	Item* getclone() override;
};