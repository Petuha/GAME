#pragma once
#pragma warning(disable : 26495)
#pragma warning(disable : 4267)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)





#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "../Dungeon/Dungeon.h"
#include "Button.h"
#include "Picture.h"
#include <functional>
#include "GameState.h"
#include <iostream>
#include "InventoryButton.h"
#include "ChestButton.h"
#include "HeavyObject.h"
#include <nlohmann/json.hpp>
#define byte win_byte_override
#include <Windows.h>