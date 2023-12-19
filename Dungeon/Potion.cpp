#include "Potion.h"
#include "Enemy.h"

itemtype Potion::getitemtype()
{
    return itemtype::potion;
}

Potion::Potion(ContRuctor ctr, nlohmann::json data)
{
    this->ctr = ctr;
    ctr(std::move(data), this);
}

void Potion::use(Enemy* enemy)
{
    Use(data, enemy);
}

Potion::operator Item* ()
{
    return new Potion(std::move(*this));
}

Item* Potion::getclone()
{
    return new Potion(ctr, data);
}

std::string Potion::getid()
{
    return Getid();
}
