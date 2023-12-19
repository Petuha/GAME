#pragma once
#include <string>
#include "enums.h"
class Item
{
protected:
	std::string name;
public:
	virtual itemtype getitemtype() = 0;
	Item(std::string name = "");
	virtual operator Item*() = 0;
	virtual Item* getclone() = 0;
};