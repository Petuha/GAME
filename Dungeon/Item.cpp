#include "Item.h"

Item::Item(std::string name)
{
	this->name = move(name);
}

