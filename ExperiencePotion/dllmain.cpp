#include "../Dungeon/Dungeon.h"
#include <nlohmann/json.hpp>
using namespace nlohmann;
using namespace std;
extern "C" __declspec(dllexport) void use(json & data, Enemy * enemy) {
	int exp = data["experience"];
	enemy->receiveexperience(exp);
}

extern "C" __declspec(dllexport) string getid() {
	return "ExperiencePotion";
}

extern "C" __declspec(dllexport) void CTR(json data, Potion * ptr) {
	ptr->Use = use;
	ptr->Getid = getid;
	if (!data.contains("experience")) data["experience"] = 0;
	ptr->data = std::move(data);
}