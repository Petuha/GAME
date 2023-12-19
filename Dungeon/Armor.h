#pragma once
#include "Item.h"
#include "enums.h"
class Armor : protected Item
{
protected:
	armortype type;
	int defence;
public:
	operator Item* () override;
	itemtype getitemtype() override;
	armortype getarmortype();
	Armor(armortype type, int defence, std::string name = "");
	int getdefence();
	Item* getclone() override;
};