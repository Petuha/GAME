#include "ChestButton.h"
using namespace std;
using namespace sf;
void ChestButton::update(RenderWindow& window, bool& shouldupdate)
{
	take.update(window);
	getinfo.update(window);
	if (getinfo.is_pressed()) {
		//do something...
	}
	if (take.is_pressed() && dungeon->takeitem(index)) {
		shouldupdate = 1;
	}
}

void ChestButton::render(RenderWindow& window)
{
	take.render(window);
	getinfo.render(window);
	picture.render(window);
}

ChestButton::ChestButton(Font* font, float x, float y, float width, float height,
	Texture* texture, Dungeon* dungeon, int i) : dungeon(dungeon), index(i)
{
	float pictureratio = 0.72f;
	picture = Picture(x, y, width, height * pictureratio, texture);
	y += height * pictureratio;
	width /= 2;
	height -= height * pictureratio;
	int charactersize = 25;
	take = Button(x, y, width, height, font, L"take", charactersize);
	x += width;
	getinfo = Button(x, y, width, height, font, L"getinfo", charactersize);
}
