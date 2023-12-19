#include "ArtifactWeapon.h"

ArtifactWeapon::operator Item* ()
{
    return new ArtifactWeapon(std::move(*this));
}

itemtype ArtifactWeapon::getitemtype()
{
    return itemtype::artifactweapon;
}

atribute ArtifactWeapon::getatribute()
{
    return stat;
}

int ArtifactWeapon::getboost()
{
    return boost;
}

ArtifactWeapon::ArtifactWeapon(int damage, atribute stat, int boost, std::string name) : Weapon(damage, std::move(name))
{
    this->stat = stat;
    this->boost = boost;
}

Damage ArtifactWeapon::getdamage() {
    return Weapon::getdamage();
}

Item* ArtifactWeapon::getclone()
{
    return new ArtifactWeapon(*this);
}
