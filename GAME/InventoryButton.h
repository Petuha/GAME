#pragma once
#include <SFML/Graphics.hpp>
#include "../Dungeon/Dungeon.h"
#include "Button.h"
#include "Picture.h"
class InventoryButton
{
private:
	Dungeon* dungeon;
	Button unequip;
	Button getinfo;
	Button potionuse;
	Picture picture;
	itemtype type;
	int additionalindex;
public:
	void update(sf::RenderWindow& window, bool& shouldupdate);
	void render(sf::RenderWindow& window);
	InventoryButton(sf::Font* font = 0, float x = 0, float y = 0, float width = 0, float height = 0,
		sf::Texture* texture = 0, Dungeon* dungeon = 0, itemtype type = itemtype::LAST_ITEM, int i = 0);
};