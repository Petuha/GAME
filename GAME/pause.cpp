#include "Header.h"
using namespace std;
using namespace sf;
void pauseescape(Dungeon& dungeon, GameState& st) {
	st = GameState::game;
}

void pausecontinue(Dungeon& dungeon, GameState& st) {
	st = GameState::game;
}

void pausesave(Dungeon& dungeon, GameState& st) {
	// do something
}

void pausereturntomainmenu(Dungeon& dungeon, GameState& st) {
	st = GameState::start;
}

void pauseexit(Dungeon& dungeon, GameState& st) {
	st = GameState::exit;
}

vector<pair<Button, function<void(Dungeon&, GameState&)>>> getpausebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float charactersize) {
	float x = spacing, y = spacing, spaceratio = 3;
	vector<pair<Button, function<void(Dungeon&, GameState&)>>> ret;
	ret.push_back({ Button(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape }), pauseescape });
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Continue", charactersize), pausecontinue });
	y += btn_h + spaceratio * spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Save", charactersize), pausesave });
	y += btn_h + spaceratio * spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Return to main menu", charactersize), pausereturntomainmenu });
	y += btn_h + spaceratio * spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Exit", charactersize), pauseexit });
	return ret;
}