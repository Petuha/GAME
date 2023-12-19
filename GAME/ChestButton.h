#pragma once
#include <SFML/Graphics.hpp>
#include "../Dungeon/Dungeon.h"
#include "Button.h"
#include "Picture.h"
class ChestButton
{
private:
	Dungeon* dungeon;
	Button take;
	Button getinfo;
	Picture picture;
	int index;
public:
	void update(sf::RenderWindow& window, bool& shouldupdate);
	void render(sf::RenderWindow& window);
	ChestButton(sf::Font* font = 0, float x = 0, float y = 0, float width = 0, float height = 0,
		sf::Texture* texture = 0, Dungeon* dungeon = 0, int i = 0);
};

