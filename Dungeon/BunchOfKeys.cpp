#include "BunchOfKeys.h"

BunchOfKeys::operator Item* ()
{
	return new BunchOfKeys(std::move(*this));
}

itemtype BunchOfKeys::getitemtype()
{
	return itemtype::keys;
}

BunchOfKeys::BunchOfKeys(int amount, std::string name) : Item(std::move(name))
{
	this->amount = amount;
}

int BunchOfKeys::keysleft()
{
	return amount;
}

BunchOfKeys& BunchOfKeys::operator+=(BunchOfKeys& keys)
{
	this->amount += keys.amount;
	keys.amount = 0;
	return *this;
}

Item* BunchOfKeys::getclone()
{
	return new BunchOfKeys(*this);
}

BunchOfKeys& BunchOfKeys::operator--()
{
	amount = std::max(0, amount - 1);
	return *this;
}
