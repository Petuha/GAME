#include "Damage.h"
Damage::Damage()
{
	n = static_cast<int>(species::LAST_ITEM);
	data.resize(n);
}
Damage& Damage::setdamage(int damage) {
	for (int i = 0; i < n; i++) data[i].damage = damage;
	return *this;
}
Damage& Damage::increasedamage(int damage)
{
	for (int i = 0; i < n; i++) data[i].damage += damage;
	return *this;
}
Damage& Damage::setratio(species race, int ratio) {
	data[static_cast<int>(race)].ratio = ratio;
	return *this;
}

int Damage::getdamage(species race)
{
	return data[(int)race].damage * data[(int)race].ratio;
}
