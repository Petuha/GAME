#pragma once
#include "Item.h"
#include "enums.h"
#include <string>
#include <nlohmann\json.hpp>
typedef void(*ContRuctor)(nlohmann::json, void* ptr);
class Enemy;

class Potion : public Item
{
private:
	typedef void(*USE)(nlohmann::json&, Enemy*);
	typedef std::string (*GetId)();
	ContRuctor ctr;
	//friend void CONSTRUCTOR(nlohmann::json data, Potion* ptr);
public:
	nlohmann::json data;
	USE Use;
	GetId Getid;
	itemtype getitemtype() override;
	Potion(ContRuctor ctr, nlohmann::json data);
	void use(Enemy* enemy);
	operator Item* () override;
	Item* getclone() override;
	std::string getid();
};