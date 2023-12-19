#include "Header.h"
#include "GetButtons.h"
#include "Renders.h"
using namespace sf;
using namespace std;
using namespace nlohmann;
void getnextrace(species& race) {
	static int i = 0;
	i++;
	i %= (int)species::LAST_ITEM;
	race = (species)i;
}
int cnt = 0;
Dungeon generatedungeon(species herorace, string heroname, HeavyObject& files) {
	//modify lvls here
	Dungeon dungeon(herorace, std::move(heroname), {
		LVL(2, 2, 0, 0, 1, 1),
		LVL(5, 5, 1, 3, 0, 0),
		LVL(6, 6, 3, 3, 5, 5),
		LVL(10, 1, 0, 0, 9, 0),
		LVL(10, 10, 4, 5, 9, 9)
		});
	Enemy enemy(1, species::human);

	enemy = Enemy(100, species::skeleton, "ahah", 1, 1);
	enemy.equipitem(Armor(armortype::chest, 100));
	for (auto& now : files.potionsconstructors) {
		enemy.equipitem(Potion(now.second, {}));
	}
	dungeon[0].addenemy(enemy);
	for (int i = 0; i < 100; i++) dungeon[0].getenemies()[0].lvlup(atribute::maxhp);
	dungeon[0].additem(1, 0, Weapon(200, "Dubina"));
	dungeon[0].addchest(0, 1, Chest(10));


	for (int i = 0; i < 4; i++) dungeon[1].changesquaretype(i, 1, SquareWall());
	dungeon[1].changesquaretype(3, 2, SquareWall());
	dungeon[1].changesquaretype(3, 3, SquareWall());
	dungeon[1].addchest(2, 2, Chest(0));
	dungeon[1].additem(0, 2, BunchOfKeys(100));
	for (int i = 0; i < 6; i++) dungeon[1].additem(2, 2, Potion(files.getpotion("HealingPotion"), { {"hptoheal", 1}}));
	dungeon[1].additem(2, 2, ArtifactWeapon(100, atribute::agility, 2));
	dungeon[1].additem(2, 2, EnchantedWeapon(100, species::skeleton, 2));
	for (int i = 0; i < 23 + 9; i++) dungeon[1].additem(2, 2, Weapon(10));
	dungeon[1].additem(2, 2, Armor(armortype::chest, 100));
	dungeon[1].additem(2, 2, Armor(armortype::legs, 100));
	dungeon[1].additem(2, 2, Armor(armortype::head, 100));
	enemy = Enemy(1, species::skeleton);
	enemy.xpos = enemy.ypos = 0;
	enemy.equipitem(Weapon(1));
	dungeon[1].addenemy(enemy);

	for (int i = 1; i < 6; i++) dungeon[2].changesquaretype(4, i, SquareWall());
	for (int i = 1; i < 4; i++) dungeon[2].changesquaretype(i, 1, SquareWall());

	for (int i = 1; i < 9; i++) dungeon[4].changesquaretype(i, 1, SquareWall());
	for (int i = 2; i < 9; i++) dungeon[4].changesquaretype(8, i, SquareWall());
	for (int i = 1; i < 8; i++) dungeon[4].changesquaretype(i, 8, SquareWall());
	for (int i = 3; i < 8; i++) dungeon[4].changesquaretype(1, i, SquareWall());
	for (int i = 2; i < 7; i++) dungeon[4].changesquaretype(i, 3, SquareWall());
	for (int i = 4; i < 7; i++) dungeon[4].changesquaretype(6, i, SquareWall());
	for (int i = 3; i < 6; i++) dungeon[4].changesquaretype(i, 6, SquareWall());
	dungeon[4].changesquaretype(3, 5, SquareWall());
	enemy = Enemy(10, species::demon);
	enemy.equipitem(Weapon(1));
	for (int i = 0; i < 6; i++) {
		enemy.xpos = i, enemy.ypos = 9;
		dungeon[4].addenemy(enemy);
	}
	return dungeon;
}

int main()
{
	//window sizes
	float w = 1200, h = 900;
	//starting window
	RenderWindow window(VideoMode(static_cast<unsigned int>(w), static_cast<unsigned int>(h)), "Game!");
	//slow loading objects
	Font font;
	if (!font.loadFromFile("Fonts/arialmt.ttf")) throw runtime_error("No font.");
	HeavyObject files("", &font);
	//game button settings
	float gamebtn_w = 100.f, gamebtn_h = 100.f, gamespacing = 30.f;
	float charactersize = 30, btncharactersize = 30;
	//start settings
	float menubtn_w, menubtn_h = 100.f, menuspacing = 30.f;
	menubtn_w = w - 2 * menuspacing;
	vector<pair<Button, function<void(GameState&)>>> startbuttons;
	//game settings
	vector<pair<Button, function<void(Dungeon&, GameState&, HeavyObject&)>>> gamebuttons;
	//pause settings
	vector<pair<Button, function<void(Dungeon&, GameState&)>>> pausebuttons;
	//newgame settings
	float racebtnwidth = 150, racebtnheight = 150;
	Button changerace(menuspacing, menuspacing, racebtnwidth, racebtnheight, &font, L"Race", 30);
	float startgamebtn_w = 300, startgamebtn_h = 150;
	Button startgame(w - menuspacing - startgamebtn_w, h - menuspacing - startgamebtn_h, startgamebtn_w,
		startgamebtn_h, &font, L"Start New Game", 36);
	Button newgameescape(0, 0, 0, 0, 0, L"", 0, { Keyboard::Escape });
	//loadgame settings
	vector<pair<Button, function<void(GameState&)>>> loadgamebuttons;
	//inventory settings
	vector<InventoryButton> inventoryobjects;
	vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> inventorybuttons;
	int inventorypage = 0;
	//chest settings
	int chestpage = 0;
	vector<pair<Button, function<void(Dungeon&, GameState&, int&)>>> chestbuttons;
	vector<ChestButton> chestobjects;
	//GameState
	GameState state = GameState::start;
	bool shouldupdate = 1;
	//dungeon constructor
	species herorace = species::human;
	string heroname = "Petuha";
	Dungeon dungeon(herorace, heroname, {});
	//main loop
	while (window.isOpen()) {
		//events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		//state
		if (state == GameState::start) {
			if (shouldupdate) {
				startbuttons = getstartbuttons(w, h, menubtn_w, menubtn_h, menuspacing, &font, charactersize);
				shouldupdate = 0;
			}
			//clear
			window.clear(Color(224, 224, 224));
			//updates
			for (auto& now : startbuttons) now.first.update(window);
			//renders
			for (auto& now : startbuttons) now.first.render(window);
			//logic
			for (auto& now : startbuttons) {
				if (now.first.is_pressed()) {
					now.second(state);
					shouldupdate = 1;
				}
			}
		}
		else if (state == GameState::newgame) {
			//clear
			window.clear();
			//updates
			changerace.update(window);
			startgame.update(window);
			newgameescape.update(window);
			//renders
			changerace.render(window);
			startgame.render(window);
			newgameescape.render(window);
			Picture(2 * menuspacing + racebtnwidth, menuspacing, racebtnwidth, racebtnheight,
				files.textures.getenemy(herorace, direction::down)).render(window);
			//logic
			if (changerace.is_pressed()) getnextrace(herorace);
			if (startgame.is_pressed()) {
				shouldupdate = 1;
				state = GameState::game;
				dungeon = generatedungeon(herorace, heroname, files);
			}
			if (newgameescape.is_pressed()) {
				shouldupdate = 1;
				state = GameState::start;
			}
		}
		else if (state == GameState::game) {
			if (shouldupdate) {
				gamebuttons = getgamebuttons(w, h, gamebtn_w, gamebtn_h, gamespacing, &font, btncharactersize, dungeon);
				shouldupdate = 0;
			}
			//clear
			window.clear();
			//updates
			for (auto& now : gamebuttons) now.first.update(window);
			//renders
			renderdungeon(w, h, files, window, dungeon);
			for (auto& now : gamebuttons) now.first.render(window);
			//logic
			for (auto& now : gamebuttons) {
				if (now.first.is_pressed()) {
					//action
					now.second(dungeon, state, files);
					shouldupdate = 1;
				}
			}
		}
		else if (state == GameState::pause) {
			if (shouldupdate) {
				pausebuttons = getpausebuttons(w, h, menubtn_w, menubtn_h, menuspacing, &font, charactersize);
				shouldupdate = 0;
			}
			//clear
			window.clear();
			//updates
			for (auto& now : pausebuttons) now.first.update(window);
			//renders
			for (auto& now : pausebuttons) now.first.render(window);
			//logic
			for (auto& now : pausebuttons) {
				if (now.first.is_pressed()) {
					now.second(dungeon, state);
					shouldupdate = 1;
				}
			}
		}
		else if (state == GameState::inventory) {
			if (shouldupdate) {
				inventoryobjects =
					getinventoryobjects(w, h, gamebtn_w, gamebtn_h, gamespacing, &font, btncharactersize,
						dungeon, inventorypage, files);
				inventorybuttons =
					getinventorybuttons(w, h, gamebtn_w, gamebtn_h, gamespacing, &font, btncharactersize, dungeon);
				shouldupdate = 0;
			}
			//clear
			window.clear();
			//updates
			for (auto& now : inventoryobjects) now.update(window, shouldupdate);
			for (auto& now : inventorybuttons) now.first.update(window);
			//renders
			for (auto& now : inventoryobjects) now.render(window);
			for (auto& now : inventorybuttons) now.first.render(window);
			//logic
			for (auto& now : inventorybuttons) {
				if (now.first.is_pressed()) {
					now.second(dungeon, state, inventorypage);
					shouldupdate = 1;
				}
			}
		}
		else if (state == GameState::chestinventory) {
		if (shouldupdate) {
			chestobjects =
				getchestobjects(w, h, gamebtn_w, gamebtn_h, gamespacing, &font, btncharactersize,
					dungeon, chestpage, files);
			chestbuttons =
				getchestbuttons(w, h, gamebtn_w, gamebtn_h, gamespacing, &font, btncharactersize, dungeon);
			shouldupdate = 0;
		}
		//clear
		window.clear();
		//updates
		for (auto& now : chestobjects) now.update(window, shouldupdate);
		for (auto& now : chestbuttons) now.first.update(window);
		//renders
		for (auto& now : chestobjects) now.render(window);
		for (auto& now : chestbuttons) now.first.render(window);
		//logic
		for (auto& now : chestbuttons) {
			if (now.first.is_pressed()) {
				now.second(dungeon, state, chestpage);
				shouldupdate = 1;
			}
		}
		}
		else if (state == GameState::loadgame) {
			if (shouldupdate) {
				loadgamebuttons = getloadgamebuttons(w, h, menubtn_w, menubtn_h, menuspacing, &font, charactersize);
				shouldupdate = 0;
			}
			//clear
			window.clear();
			//updates
			for (auto& now : loadgamebuttons) now.first.update(window);
			//renders
			for (auto& now : loadgamebuttons) now.first.render(window);
			//logic
			for (auto& now : loadgamebuttons) {
				if (now.first.is_pressed()) {
					now.second(state);
					shouldupdate = 1;
				}
			}
		}
		else if (state == GameState::exit) window.close();
		//display
		window.display();
		sleep(milliseconds(1)); //lower cpu usage!!!
	}
	return 0;
}