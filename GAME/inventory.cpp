#include "Header.h"
using namespace std;
using namespace sf;
vector<InventoryButton> getinventoryobjects(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float textsize, Dungeon& dungeon, int& page, HeavyObject& files) {
	vector<InventoryButton> ret;
	int potionsonscreen = 5, as = dungeon.hero.getpotions().size(), sz;
	sz = ceil(1.0 * as / potionsonscreen);
	page = max(0, min(page, sz - 1));
	float picsize = 2 * btn_w;
	float x = spacing, y = h - spacing - btn_h - spacing - picsize;
	//potions
	Item* ptr;
	for (int i = page * potionsonscreen, cnt = 0; i < as && cnt < potionsonscreen; i++, cnt++) {
		ret.push_back(InventoryButton(btn_font, x, y, picsize, picsize, 
			files.textures.getitem(dungeon.hero.getpotions()[i]), // here get pointer to actual potion
			&dungeon, itemtype::potion, i));
		x += spacing + picsize;
	}
	//weapon
	x = spacing, y = spacing;
	ptr = (Item*)Weapon(1);
	if (dungeon.hero.hasweapon()) {
		ret.push_back(InventoryButton(btn_font, x, y, picsize, picsize, files.textures.getitem(ptr),
			&dungeon, itemtype::weapon));
	}
	delete ptr;
	//keys
	x += spacing + picsize;
	ptr = (Item*)BunchOfKeys(1);
	if (dungeon.hero.haskeys()) {
		ret.push_back(InventoryButton(btn_font, x, y, picsize, picsize, files.textures.getitem(ptr),
			&dungeon, itemtype::keys));
	}
	delete ptr;
	y += spacing + picsize;
	x = spacing;
	//armor
	ptr = (Item*)Armor(armortype::chest, 1);
	for (int i = 0; i < (int)armortype::LAST_ITEM; i++) {
		if (dungeon.hero.hasarmor((armortype)i)) {
			ret.push_back(InventoryButton(btn_font, x, y, picsize, picsize, files.textures.getitem(ptr),
				&dungeon, itemtype::armor, i));
		}
		x += spacing + picsize;
	}
	delete ptr;
	return ret;
}
void inventoryescape(Dungeon& dungeon, GameState& st, int& page) {
	page = 0;
	st = GameState::game;
}
void potionright(Dungeon& dungeon, GameState& st, int& page) {
	page++;
}
void potionleft(Dungeon& dungeon, GameState& st, int& page) {
	page--;
}
vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> getinventorybuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float textsize, Dungeon& dungeon) {
	vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> ret;
	ret.push_back({ Button(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape }), inventoryescape });
	float x = w - spacing - btn_w, y = h - spacing - btn_h;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L">", 30, {Keyboard::Right}), potionright });
	x -= spacing + btn_w;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"<", 30, {Keyboard::Left}), potionleft });
	return ret;
}