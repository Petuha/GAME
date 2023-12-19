#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Dungeon/Dungeon.h"
#include <string>
#include <filesystem>
class Textures
{
private:
	std::vector<std::vector<sf::Texture>> races;
	std::vector<sf::Texture> squares;
	std::vector<sf::Texture> items;
	std::vector<sf::Texture> chests;
	std::map<std::string, sf::Texture> potions;
public:
	Textures(std::string path);
	sf::Texture* getenemy(species race, direction dir);
	sf::Texture* getenemy(Enemy& enemy);
	sf::Texture* getsquare(Square* square);
	sf::Texture* getitem(Item* item);
	sf::Texture* getitem(itemtype type);
	sf::Texture* getchest(Chest* chest);
};