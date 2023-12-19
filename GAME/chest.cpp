//#include "Header.h"
#include "ChestButton.h"
#include "HeavyObject.h"
#include "GameState.h"
using namespace std;
using namespace sf;
vector<ChestButton> getchestobjects(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float textsize, Dungeon& dungeon, int& page, HeavyObject& files) {
	vector<ChestButton> ret;
	float x = spacing, y = spacing;
	float picsize = btn_w * 2;
	int itemsinstring = 5, columns = 3;
	int as = dungeon.accesschestitems().size(), sz;
	sz = ceil(1.0 * as / (itemsinstring * columns));
	page = max(0, min(page, sz - 1));
	int index = page * itemsinstring * columns;
	for (int i = 0; i < columns && index < as; i++) {
		for (int j = 0; j < itemsinstring && index < as; j++) {
			ret.push_back(ChestButton(btn_font, x, y, picsize, picsize,
				files.textures.getitem(dungeon.accesschestitems()[index]), &dungeon, index));
			x += picsize + spacing;
			index++;
		}
		x = spacing;
		y += spacing + picsize;
	}
	return ret;
}
void chestescape(Dungeon& dungeon, GameState& st, int& page) {
	page = 0;
	st = GameState::game;
}
void pageleft(Dungeon& dungeon, GameState& st, int& page) {
	page--;
}
void pageright(Dungeon& dungeon, GameState& st, int& page) {
	page++;
}
vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> getchestbuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float textsize, Dungeon& dungeon) {
	vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> ret;
	ret.push_back({ Button(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape }), chestescape });
	float x = w - spacing - btn_w, y = h - spacing - btn_h;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L">", 30, {Keyboard::Right}), pageright });
	x -= spacing + btn_w;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"<", 30, {Keyboard::Left}), pageleft });
	return ret;
}