#include "Header.h"
using namespace std;
using namespace sf;
void loadgameescape(GameState& st) {
	st = GameState::start;
}

vector<pair<Button, function<void(GameState&)>>> getloadgamebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float charactersize) {
	vector<pair<Button, function<void(GameState&)>>> ret;
	ret.push_back({ Button(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape }), loadgameescape });
	return ret;
}