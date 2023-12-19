#include "ArtifactArmor.h"


ArtifactArmor::operator Item* ()
{
    return new ArtifactArmor(std::move(*this));
}

itemtype ArtifactArmor::getitemtype()
{
    return itemtype::artifactarmor;
}

ArtifactArmor::ArtifactArmor(armortype type, int defence, atribute stat, int boost, std::string name)
    : Armor(type, defence, std::move(name))
{
    this->stat = stat;
    this->boost = boost;
}

atribute ArtifactArmor::getatribute()
{
    return stat;
}

int ArtifactArmor::getboost()
{
    return boost;
}

Item* ArtifactArmor::getclone()
{
    return new ArtifactArmor(*this);
}
