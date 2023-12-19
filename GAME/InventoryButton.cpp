#include "InventoryButton.h"
using namespace std;
using namespace sf;
InventoryButton::InventoryButton(Font* font, float x, float y, float width, float height,
Texture* texture, Dungeon* dungeon, itemtype type, int i) : dungeon(dungeon), type(type), additionalindex(i)
{
	if (type != itemtype::potion) {
		float pictureratio = 0.72f;
		picture = Picture(x, y, width, height * pictureratio, texture);
		y += height * pictureratio;
		width /= 2;
		height -= height * pictureratio;
		int charactersize = 25;
		unequip = Button(x, y, width, height, font, L"unequip", charactersize);
		x += width;
		getinfo = Button(x, y, width, height, font, L"getinfo", charactersize);
	}
	else {
		float pictureratio = 0.60f;
		picture = Picture(x, y, width, height * pictureratio, texture);
		y += height * pictureratio;
		int charactersize = 25;
		height -= height * pictureratio;
		height /= 2;
		potionuse = Button(x, y, width, height, font, L"use", charactersize);
		y += height;
		width /= 2;
		unequip = Button(x, y, width, height, font, L"unequip", charactersize);
		x += width;
		getinfo = Button(x, y, width, height, font, L"getinfo", charactersize);
	}
}

void InventoryButton::update(RenderWindow& window, bool& shouldupdate)
{
	unequip.update(window);
	getinfo.update(window);
	if (type == itemtype::potion) potionuse.update(window);
	if (getinfo.is_pressed()) {
		//do something...
	}
	if (unequip.is_pressed() && dungeon->unequip(type, additionalindex)) {
		shouldupdate = 1;
	}
	if (type == itemtype::potion && potionuse.is_pressed() && dungeon->usepotion(additionalindex)) {
		shouldupdate = 1;
	}
}

void InventoryButton::render(RenderWindow& window)
{
	unequip.render(window);
	getinfo.render(window);
	picture.render(window);
	if (type == itemtype::potion) potionuse.render(window);
}
