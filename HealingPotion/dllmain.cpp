#include "../Dungeon/Dungeon.h"
#include <nlohmann/json.hpp>
using namespace nlohmann;
using namespace std;
/*
����� ������ �����
�� ���� ��������� ����, ������� ��� ������� ����� ����������� � ��������� �� �����
*/
extern "C" __declspec(dllexport) void use(json & data, Enemy * enemy) {
	int hp = data["hptoheal"];
	enemy->hp += hp;
	enemy->hp = max(enemy->hp, 0);
	enemy->hp = min(enemy->hp, enemy->getatribute(atribute::maxhp));
}

extern "C" __declspec(dllexport) string getid() {
	return "HealingPotion"; //��������� � ��������� dll-��
}
/*
�����������. �������� ������������� CTR
��� ���� ���������������� ���� � ��������� �� �������
*/
extern "C" __declspec(dllexport) void CTR(json data, Potion * ptr) {
	ptr->Use = use;
	ptr->Getid = getid;
	if (!data.contains("hptoheal")) data["hptoheal"] = 0;
	ptr->data = std::move(data);
}