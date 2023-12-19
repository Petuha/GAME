#include "Header.h"
using namespace std;
using namespace sf;
void startexit(GameState& st) {
	st = GameState::exit;
}
void startnewgame(GameState& st) {
	st = GameState::newgame;
}
void startloadgame(GameState& st) {
	st = GameState::loadgame;
}
vector<pair<Button, function<void(GameState&)>>> getstartbuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float charactersize) {
	float x = spacing, y = spacing, spaceratio = 3;
	vector<pair<Button, function<void(GameState&)>>> ret;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"New Game", charactersize), startnewgame });
	//x += btn_w + spacing;
	y += btn_h + spaceratio * spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Load Game", charactersize), startloadgame });
	//x += btn_w + spacing;
	y += btn_h + spaceratio * spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"Exit", charactersize), startexit });
	return ret;
}