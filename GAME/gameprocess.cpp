#include "Header.h"
using namespace std;
using namespace sf;
void movedown(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.bodymove(dungeon.hero, direction::down);
	files.sounds.playsound(L"walk");
	files.makenextstep(dungeon);
}
void moveup(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.bodymove(dungeon.hero, direction::up);
	files.sounds.playsound(L"walk");
	files.makenextstep(dungeon);
}
void moveleft(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.bodymove(dungeon.hero, direction::left);
	files.sounds.playsound(L"walk");
	files.makenextstep(dungeon);
}
void moveright(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.bodymove(dungeon.hero, direction::right);
	files.sounds.playsound(L"walk");
	files.makenextstep(dungeon);
}
void gameescape(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	st = GameState::pause;
}
void gameuseladder(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.useladder();
}
void gamepickitem(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.pickitem();
}
void openchest(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	if (dungeon.tryopenchest()) {
		st = GameState::chestinventory;
	}
}
void openinventory(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	st = GameState::inventory;
}
void gameattack(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.attack();
	files.sounds.playsound(L"attack");
	files.makenextstep(dungeon);
}
void gamereturntotitlescreen(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	st = GameState::start;
}
void gamelvlupagility(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.lvlup(atribute::agility);
}
void gamelvlupforce(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.lvlup(atribute::force);
}
void gamelvlupmaxhp(Dungeon& dungeon, GameState& st, HeavyObject& files) {
	dungeon.lvlup(atribute::maxhp);
}
vector<pair<Button, function<void(Dungeon&, GameState&, HeavyObject&)>>> getgamebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, Font* btn_font, float textsize, Dungeon& dungeon) {
	vector<pair<Button, function<void(Dungeon&, GameState&, HeavyObject&)>>> ret;
	//game over
	if (dungeon.gameover) {
		float ratio = 0.5;
		btn_h = h * ratio;
		btn_w = w * ratio;
		ret.push_back({ Button((w - btn_w) / 2, (h - btn_h) / 2, btn_w, btn_h, btn_font,
			L"        Game is over\n(return to start screen)",
			60, {}, Color::Red, Color::Black), gamereturntotitlescreen });
		return ret;
	}
	//wasd bottom left
	ret.push_back({ Button(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape }), gameescape });
	float x = spacing, y = h - spacing - btn_h;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"A", textsize, {Keyboard::A}), moveleft });
	x += spacing + btn_w;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"S", textsize, {Keyboard::S}), movedown });
	y -= spacing + btn_h;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"W", textsize, {Keyboard::W}), moveup });
	y += spacing + btn_h;
	x += spacing + btn_w;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"D", textsize, {Keyboard::D}), moveright });
	//attack, items and ladder bottom right
	x = w - spacing - btn_w, y = h - spacing - btn_h;
	if (dungeon.possibleattack()) {
		ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"ATACK", textsize, {Keyboard::F}), gameattack });
		y -= spacing + btn_h;
	}
	if (dungeon.possibleuseladder()) {
		ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"U", textsize, {Keyboard::U}), gameuseladder });
		y -= spacing + btn_h;
	}
	if (dungeon.possiblepickitem()) {
		ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"T", textsize, {Keyboard::T}), gamepickitem });
		y -= spacing + btn_h;
	}
	//chest, inventory and lvlup top right
	x = w - spacing - btn_w, y = spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"I", textsize, {Keyboard::I}), openinventory });
	y += spacing + btn_h;
	if (dungeon.possibleopenchest()) {
		ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"O", textsize, {Keyboard::O}), openchest });
	}
	if (!dungeon.possiblelvlup()) return ret;
	x -= btn_w + spacing, y = spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"agility", textsize, {}), gamelvlupagility });
	x -= btn_w + spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"force", textsize, {}), gamelvlupforce });
	x -= btn_w + spacing;
	ret.push_back({ Button(x, y, btn_w, btn_h, btn_font, L"maxhp", textsize, {}), gamelvlupmaxhp });
	return ret;
}

void renderbar(RenderWindow& window, float x, float y, float width, float height, float ratio,
	Color front, Color back, const string& text = "", Font* font = 0) {
	RectangleShape hpbar;
	hpbar.setFillColor(back);
	hpbar.setSize(Vector2f(width, height));
	hpbar.setPosition(Vector2f(x, y));
	window.draw(hpbar);
	hpbar.setFillColor(front);
	hpbar.setSize(Vector2f(width * ratio, height));
	window.draw(hpbar);
	if (!text.size()) return;
	Text txt;
	txt.setFont(*font);
	txt.setString(text);
	txt.setFillColor(Color::Black);
	txt.setCharacterSize(30);
	txt.setPosition(Vector2f(
		x + (width - txt.getGlobalBounds().width) / 2.f,
		y + (height - txt.getGlobalBounds().height) / 2.f - 9 //MAGIC NUM
	));
	window.draw(txt);
}

void renderenemy(Enemy& enemy, int i_start, int j_start, float squaresize, float spacingw, float spacingh,
	Textures& textures, RenderWindow& window, bool renderhp) {
	float x = spacingw + (enemy.ypos - j_start) * squaresize;
	float y = spacingh + (enemy.xpos - i_start) * squaresize;
	Picture(x, y, squaresize, squaresize, textures.getenemy(enemy)).render(window);
	if (!renderhp) return;
	float hpbarratio = 0.1;
	renderbar(window, x, y + squaresize * (1 - hpbarratio), squaresize, squaresize * hpbarratio,
		1.0 * enemy.hp / enemy.getatribute(atribute::maxhp), Color::Green, Color::Red);

}

void renderdungeon(float w, float h, HeavyObject& files, RenderWindow& window, Dungeon& dungeon) {
	float squaresize = 100;
	int maxsquaresw = 5, maxsquaresh = 5;
	int squaresw = min(dungeon.herolvl().getfield().width(), maxsquaresw);
	int squaresh = min(dungeon.herolvl().getfield().height(), maxsquaresh);
	float spacingw = (w - squaresw * squaresize) / 2.f;
	float spacingh = (h - squaresh * squaresize) / 2.f;
	int i_start = max(dungeon.hero.xpos - squaresh / 2, 0);
	if (i_start + squaresh > dungeon.herolvl().getfield().height()) {
		i_start = dungeon.herolvl().getfield().height() - squaresh;
	}
	int j_start = max(dungeon.hero.ypos - squaresw / 2, 0);
	if (j_start + squaresw > dungeon.herolvl().getfield().width()) {
		j_start = dungeon.herolvl().getfield().width() - squaresw;
	}
	float y = spacingh;
	float x = spacingw;
	float itemratio = 0.3;
	float itemsize = squaresize * itemratio;
	float chestratio = 0.66;
	float chestheight = squaresize * chestratio;
	for (int cnt1 = 0, i = i_start; cnt1 < squaresh; cnt1++, i++, y += squaresize) {
		for (int cnt2 = 0, j = j_start; cnt2 < squaresw; cnt2++, j++, x += squaresize) {
			Picture(x, y, squaresize, squaresize,
				files.textures.getsquare(dungeon.herolvl().getsquare(i, j))).render(window);
			if (dungeon.herolvl().getsquaretype(i, j) == squaretype::floor) {
				SquareFloor* ptr = (SquareFloor*)dungeon.herolvl().getsquare(i, j);
				if (ptr->item) {
					//render item
					Picture(x + (squaresize - itemsize) / 2.f, y + (squaresize - itemsize) / 2.f, itemsize, itemsize,
						files.textures.getitem(ptr->item)).render(window);
				}
				if (ptr->chest) {
					//render chest
					Picture(x + (squaresize - squaresize) / 2.f, y + (squaresize - chestheight), squaresize, chestheight,
						files.textures.getchest(ptr->chest)).render(window);
				}
			}
		}
		x = spacingw;
	}
	for (Enemy& now : dungeon.herolvl().getenemies()) {
		if (now.xpos >= i_start && now.xpos < i_start + squaresw &&
			now.ypos >= j_start && now.ypos < j_start + squaresh) {
			renderenemy(now, i_start, j_start, squaresize, spacingw, spacingh, files.textures, window, 1);
		}
	}
	renderenemy(dungeon.hero, i_start, j_start, squaresize, spacingw, spacingh, files.textures, window, 0);
	//hp and lvl top left
	//hp
	float spacing = 30;
	x = y = spacing;
	float hpwidth = 300, hpheight = 25;
	renderbar(window, x, y, hpwidth, hpheight, 1.0 * dungeon.hero.hp / dungeon.hero.getatribute(atribute::maxhp),
		Color::Green, Color::Red, to_string(dungeon.hero.hp) + "/" + to_string(dungeon.hero.getatribute(atribute::maxhp)),
		files.font);
	y += spacing + hpheight;
	//lvl
	//renderbar(window, x, y, hpwidth, hpheight, 1.0 * dungeon.hero.)

}