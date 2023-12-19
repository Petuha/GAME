#include "Armor.h"

Armor::operator Item* ()
{
	return new Armor(std::move(*this));
}

itemtype Armor::getitemtype()
{
	return itemtype::armor;
}

armortype Armor::getarmortype()
{
	return type;
}

Armor::Armor(armortype type, int defence, std::string name) : Item(std::move(name))
{
	this->type = type;
	this->defence = defence;
}

int Armor::getdefence()
{
	return defence;
}

Item* Armor::getclone()
{
	return new Armor(*this);
}
