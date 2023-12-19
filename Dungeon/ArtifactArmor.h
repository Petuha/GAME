#pragma once
#include "Armor.h"
#include "enums.h"
class ArtifactArmor : public Armor
{
private:
	int boost;
	atribute stat;
public:
	operator Item*() override;
	itemtype getitemtype() override;
	ArtifactArmor(armortype type, int defence, atribute stat, int boost, std::string name = "");
	atribute getatribute();
	int getboost();
	Item* getclone() override;
};