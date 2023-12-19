#include "Enemy.h"
#include "ArtifactArmor.h"
#include <stdexcept>
#include "Chest.h"

Enemy::Enemy(int lvl, species race, std::string name, int xpos, int ypos)
{
	looksight = direction::down;
	expratio = pow(10, 0.09);
	if (lvl > MAX_LVL || lvl < 1) throw std::invalid_argument("bad lvl");
	weapon = 0;
	armor.resize((int)armortype::LAST_ITEM);
	for (Armor*& i : armor) i = 0;
	keys = 0;
	lvluppoints = 0;
	atributes.resize(static_cast<int>(atribute::LAST_ITEM));
	armor.resize((int)armortype::LAST_ITEM);
	this->race = race;
	atributes[(int)atribute::agility] = 0;
	atributes[(int)atribute::force] = 0;
	atributes[(int)atribute::maxhp] = 1;
	hp = atributes[(int)atribute::maxhp];
	experiencetolvlup = std::max(1.l, expratio);
	this->lvluppoints = 0;
	this->lvl = 0;
	while (this->lvl < lvl) {
		this->receiveexperience(experiencetolvlup);
	}
	this->xpos = xpos;
	this->ypos = ypos;
	this->name = move(name);
}

Enemy& Enemy::operator=(const Enemy& rhs)
{
	looksight = rhs.looksight;
	expratio = rhs.expratio;
	hp = rhs.hp;
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	experiencetolvlup = rhs.experiencetolvlup;
	lvluppoints = rhs.lvluppoints;
	name = rhs.name;
	race = rhs.race;
	atributes = rhs.atributes;
	lvl = rhs.lvl;
	delete weapon;
	weapon = (rhs.weapon ? (Weapon*)rhs.weapon->getclone() : 0);
	for (Armor* now : armor) delete now;
	armor.resize(rhs.armor.size());
	for (int i = 0; i < armor.size(); i++) {
		armor[i] = (rhs.armor[i] ? (Armor*)rhs.armor[i]->getclone() : 0);
	}
	delete keys;
	keys = (rhs.keys ? (BunchOfKeys*)rhs.keys->getclone() : 0);
	for (Potion* now : potions) delete now;
	potions.resize(rhs.potions.size());
	for (int i = 0; i < potions.size(); i++) {
		potions[i] = (rhs.potions[i] ? (Potion*)rhs.potions[i]->getclone() : 0);
	}
	return *this;
}

Enemy& Enemy::operator=(Enemy&& rhs) noexcept
{
	looksight = rhs.looksight;
	expratio = rhs.expratio;
	hp = rhs.hp;
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	experiencetolvlup = rhs.experiencetolvlup;
	lvluppoints = rhs.lvluppoints;
	name = std::move(rhs.name);
	race = rhs.race;
	atributes = std::move(rhs.atributes);
	lvl = rhs.lvl;
	delete weapon;
	weapon = rhs.weapon;
	rhs.weapon = 0;
	for (Armor* now : armor) delete now;
	armor = std::move(rhs.armor);
	delete keys;
	keys = rhs.keys;
	rhs.keys = 0;
	for (Potion* now : potions) delete now;
	potions = std::move(rhs.potions);
	return *this;
}

Enemy::Enemy(const Enemy& rhs)
{
	looksight = rhs.looksight;
	expratio = rhs.expratio;
	hp = rhs.hp;
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	experiencetolvlup = rhs.experiencetolvlup;
	lvluppoints = rhs.lvluppoints;
	name = rhs.name;
	race = rhs.race;
	atributes = rhs.atributes;
	lvl = rhs.lvl;
	weapon = (rhs.weapon ? (Weapon*)rhs.weapon->getclone() : 0);
	armor.resize(rhs.armor.size());
	for (int i = 0; i < armor.size(); i++) {
		armor[i] = (rhs.armor[i] ? (Armor*)rhs.armor[i]->getclone() : 0);
	}
	keys = (rhs.keys ? (BunchOfKeys*)rhs.keys->getclone() : 0);
	potions.resize(rhs.potions.size());
	for (int i = 0; i < potions.size(); i++) {
		potions[i] = (rhs.potions[i] ? (Potion*)rhs.potions[i]->getclone() : 0);
	}
}

Enemy::Enemy(Enemy&& rhs) noexcept
{
	looksight = rhs.looksight;
	expratio = rhs.expratio;
	hp = rhs.hp;
	xpos = rhs.xpos;
	ypos = rhs.ypos;
	experiencetolvlup = rhs.experiencetolvlup;
	lvluppoints = rhs.lvluppoints;
	name = std::move(rhs.name);
	race = rhs.race;
	atributes = std::move(rhs.atributes);
	lvl = rhs.lvl;
	weapon = rhs.weapon;
	rhs.weapon = 0;
	armor = std::move(rhs.armor);
	keys = rhs.keys;
	rhs.keys = 0;
	potions = std::move(rhs.potions);
}

Chest Enemy::chestafterdeath()
{
	if (!isdead() || placedchest) return 0;
	Chest chest(0);
	chest += (Item*)weapon;
	weapon = 0;
	for (auto& now : armor) {
		chest += (Item*)now;
		now = 0;
	}
	chest += (Item*)keys;
	keys = 0;
	for (auto& now : potions) {
		chest += (Item*)now;
		now = 0;
	}
	return chest;
}

bool Enemy::hasweapon()
{
	return weapon;
}

bool Enemy::hasarmor(armortype type)
{
	return armor[(int)type];
}

bool Enemy::haskeys()
{
	return keys;
}

Enemy::~Enemy()
{
	delete weapon;
	for (Armor* arm : armor) delete arm;
	for (Potion* potion : potions) delete potion;
	delete keys;
}

bool Enemy::attack(Enemy& target)
{
	if (!weapon) return 1;
	Damage damage = weapon->getdamage();
	damage.increasedamage(atributes[static_cast<int>(atribute::force)]);
	if (!target.receivedamage(damage)) {
		this->receiveexperience(target.getexperienceafterdeath());
		return 1;
	}
	return 0;
}

void Enemy::equipitem(Item* item)
{
	if (!item) throw std::runtime_error("invalid item");
	switch (item->getitemtype())
	{
	case itemtype::armor: {
		Armor* armorptr = reinterpret_cast<Armor*>(item);
		int i = static_cast<int>(armorptr->getarmortype());
		if (armor[i]) throw std::runtime_error("armor slot is already busy");
		armor[i] = armorptr;
		break;
	}
	case itemtype::artifactarmor: {
		ArtifactArmor* armorptr = reinterpret_cast<ArtifactArmor*>(item);
		int i = static_cast<int>(armorptr->getarmortype());
		if (armor[i]) throw std::runtime_error("armor slot is already busy");
		atributes[static_cast<int>(armorptr->getatribute())] += armorptr->getboost();
		armor[i] = armorptr;
		break;
	}
	case itemtype::weapon: {
		if (weapon) throw std::runtime_error("weapon slot is already busy");
		weapon = (Weapon*)item;
		break;
	}
	case itemtype::artifactweapon: {
		if (weapon) throw std::runtime_error("weapon slot is already busy");
		ArtifactWeapon* weaponptr = (ArtifactWeapon*)item;
		atributes[(int)weaponptr->getatribute()] += weaponptr->getboost();
		weapon = (Weapon*)item;
		break;
	}
	case itemtype::keys: {
		BunchOfKeys* keyptr = (BunchOfKeys*)item;
		if (keys) {
			*keys += *keyptr;
			delete item;
		}
		else {
			keys = keyptr;
		}
		break;
	}
	case itemtype::potion: {
		potions.push_back((Potion*)item);
		break;
	}
	default:
		throw std::invalid_argument("invalid item type");
	}
}

bool Enemy::possibleequip(Item* item)
{
	if (!item) return 0;
	switch (item->getitemtype())
	{
	case itemtype::armor: {
		Armor* armorptr = reinterpret_cast<Armor*>(item);
		int i = static_cast<int>(armorptr->getarmortype());
		if (armor[i]) return 0;
		break;
	}
	case itemtype::artifactarmor: {
		ArtifactArmor* armorptr = reinterpret_cast<ArtifactArmor*>(item);
		int i = static_cast<int>(armorptr->getarmortype());
		if (armor[i]) return 0;
		break;
	}
	case itemtype::weapon: {
		if (weapon) return 0;
		break;
	}
	case itemtype::artifactweapon: {
		if (weapon) return 0;
		break;
	}
	case itemtype::keys: {
		break;
	}
	case itemtype::potion: {
		break;
	}
	default:
		throw std::invalid_argument("invalid item type");
		return 0;
	}
	return 1;
}

bool Enemy::unequip(itemtype type, int i)
{
	switch (type)
	{
	case itemtype::weapon: {
		if (!weapon) return 0;
		delete weapon;
		weapon = 0;
		break;
	}
	case itemtype::potion: {
		if (i >= potions.size() || i < 0) return 0;
		delete potions[i];
		for (int j = i + 1; j < potions.size(); j++) potions[j - 1] = potions[j];
		potions.pop_back();
		break;
	}
	case itemtype::armor: {
		if (i >= 3 || i < 0 || !armor[i]) return 0;
		delete armor[i];
		armor[i] = 0;
		break;
	}
	case itemtype::keys: {
		if (!keys) return 0;
		delete keys;
		keys = 0;
		break;
	}
	case itemtype::artifactarmor: {
		if (i >= 3 || i < 0 || !armor[i]) return 0;
		ArtifactArmor* armorptr = (ArtifactArmor*)armor[i];
		atributes[(int)armorptr->getatribute()] -= armorptr->getboost();
		delete armor[i];
		armor[i] = 0;
		break;
	}
	case itemtype::artifactweapon: {
		if (!weapon) return 0;
		ArtifactWeapon* weaponptr = (ArtifactWeapon*)weapon;
		atributes[(int)weaponptr->getatribute()] -= weaponptr->getboost();
		delete weapon;
		weapon = 0;
		break;
	}
	default:
		break;
	}
	return 1;
}

long long Enemy::getexperienceafterdeath()
{
	return std::max(1.l, expratio * (pow(expratio, lvl) - 1.l) / (expratio - 1.l) / 5);
}


void Enemy::receiveexperience(long long exp)
{
	experiencetolvlup -= exp;
	if (lvl == MAX_LVL) {
		experiencetolvlup = std::max(experiencetolvlup, 0LL);
		return;
	}
	while (experiencetolvlup <= 0) {
		experiencetolvlup += pow(expratio, lvl);
		lvl++;
		lvluppoints += std::min(1, lvl / 5);
		if (lvl == MAX_LVL) {
			experiencetolvlup = std::max(experiencetolvlup, 0LL);
			return;
		}
	}
}

bool Enemy::lvlup(atribute stat)
{
	if (!lvluppoints) return 0;
	for (int& now : atributes) now++;
	hp++;
	atributes[(int)stat]++;
	lvluppoints--;
	if (stat == atribute::maxhp) hp++;
	return 1;
}



int Enemy::getdefence()
{
	int defence = 0;
	for (int i = 0; i < armor.size(); i++) {
		if (armor[i]) defence += armor[i]->getdefence();
	}
	return defence;
}

int Enemy::getatribute(atribute atr)
{
	return atributes[(int)atr];
}

const std::vector<Potion*>& Enemy::getpotions()
{
	return potions;
}

bool Enemy::usepotion(int i)
{
	if (i < 0 || i >= potions.size()) return 0;
	potions[i]->use(this);
	delete potions[i];
	for (int j = i + 1; j < potions.size(); j++) potions[j - 1] = potions[j];
	potions.pop_back();
	return 1;
}

bool Enemy::isdead()
{
	return hp == 0;
}

int Enemy::getlvluppoints()
{
	return lvluppoints;
}

bool Enemy::receivedamage(Damage damage)
{
	hp -= std::max(0, damage.getdamage(race) - this->getdefence());
	hp = std::max(hp, 0);
	hp = std::min(hp, atributes[(int)atribute::maxhp]);
	return hp > 0;
}
