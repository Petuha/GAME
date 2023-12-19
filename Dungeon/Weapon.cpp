#include "Weapon.h"
Weapon::operator Item* ()
{
    return new Weapon(std::move(*this));
}
itemtype Weapon::getitemtype()
{
    return itemtype::weapon;
}
Damage Weapon::getdamage()
{
    Damage ret;
    ret.setdamage(damage);
    return ret;
}
Weapon::Weapon(int damage, std::string name) : Item(std::move(name))
{
    this->damage = damage;
}

Item* Weapon::getclone()
{
    return new Weapon(*this);
}
