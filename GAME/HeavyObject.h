#pragma once
#include "Textures.h"
#include "Sounds.h"
#include <filesystem>
#include <Windows.h>
typedef void(*MakeNextStep)(Dungeon&);
class HeavyObject
{
private:
	HINSTANCE loadnextstep;
	//potions
	std::vector<HINSTANCE> loads;
public:
	std::map<std::string, ContRuctor> potionsconstructors;
	ContRuctor getpotion(const std::string& id);
	MakeNextStep makenextstep;
	Textures textures;
	sf::Font* font;
	Sounds sounds;
	HeavyObject(std::string path, sf::Font* fnt);
	~HeavyObject();
};