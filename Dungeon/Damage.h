#pragma once
#include <vector>
#include "enums.h"
class Damage
{
private:
	struct dmg {
		int damage;
		int ratio = 1;
	};
	std::vector<dmg> data;
	int n;
public:
	Damage();
	Damage& setdamage(int damage);
	Damage& increasedamage(int damage);
	Damage& setratio(species race, int ratio);
	int getdamage(species race);
};