#pragma once
#include "Item.h"
#include "enums.h"
class BunchOfKeys : protected Item
{
private:
	int amount;
public:
	operator Item* () override;
	itemtype getitemtype() override;
	BunchOfKeys(int amount, std::string name = "");
	int keysleft();
	BunchOfKeys& operator+=(BunchOfKeys& keys); // join 2 Bunches of keys
	Item* getclone() override;
	BunchOfKeys& operator--();
};