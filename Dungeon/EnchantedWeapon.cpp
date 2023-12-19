#include "EnchantedWeapon.h"

EnchantedWeapon::operator Item* ()
{
    return new EnchantedWeapon(std::move(*this));
}

Damage EnchantedWeapon::getdamage()
{
    Damage ret;
    ret.setdamage(damage);
    ret.setratio(efficientagainst, ratio);
    return ret;
}

EnchantedWeapon::EnchantedWeapon(int damage, species efficientagainst, int ratio, std::string name)
    : Weapon(damage, std::move(name))
{
    this->efficientagainst = efficientagainst;
    this->ratio = ratio;
}

Item* EnchantedWeapon::getclone()
{
    return new EnchantedWeapon(*this);
}
