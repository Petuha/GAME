#pragma once
#include "Header.h"
std::vector<std::pair<Button, std::function<void(GameState&)>>> getstartbuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float charactersize);
std::vector<std::pair<Button, std::function<void(Dungeon&, GameState&)>>> getpausebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float charactersize);
std::vector<std::pair<Button, std::function<void(GameState&)>>> getloadgamebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float charactersize);
std::vector<std::pair<Button, std::function<void(Dungeon&, GameState&, HeavyObject&)>>> getgamebuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float textsize, Dungeon& dungeon);
std::vector<InventoryButton> getinventoryobjects(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float textsize, Dungeon& dungeon, int& page, HeavyObject& textures);
std::vector<std::pair<Button, std::function<void(Dungeon&, GameState&, int&)>>> getinventorybuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float textsize, Dungeon& dungeon);
std::vector<ChestButton> getchestobjects(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float textsize, Dungeon& dungeon, int& page, HeavyObject& textures);
std::vector<std::pair<Button, std::function<void(Dungeon&, GameState&, int&)>>> getchestbuttons(float w, float h, float btn_w,
	float btn_h, float spacing, sf::Font* btn_font, float textsize, Dungeon& dungeon);