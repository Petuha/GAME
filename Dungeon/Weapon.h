#pragma once
#include "Item.h"
#include <string>
#include "Damage.h"
#include "enums.h"
class Weapon : protected Item
{
protected:
	int damage;
public:
	operator Item* () override;
	itemtype getitemtype() override;
	virtual Damage getdamage();
	Weapon(int damage, std::string name = "");
	Item* getclone() override;
};