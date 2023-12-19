// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "nextstep.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#include <queue>
Matrix<direction> directions(LVL& lvl, int xs, int ys) {
	using namespace std;
	Matrix<direction> ret(lvl.getfield().height(), lvl.getfield().width());
	for (auto& now : ret) now = direction::LAST_ITEM;
	ret[xs][ys] = direction::down;
	queue<tuple<int, int, direction>> q;
	q.push({ xs, ys, direction::down });
	int x, y;
	direction dir;
	while (q.size()) {
		tie(xs, ys, dir) = q.front();
		q.pop();
		x = xs + 1, y = ys;
		if (lvl.possiblestandon(x, y) && ret[x][y] == direction::LAST_ITEM) {
			ret[x][y] = direction::up;
			q.push({ x, y, direction::up });
		}
		x = xs - 1, y = ys;
		if (lvl.possiblestandon(x, y) && ret[x][y] == direction::LAST_ITEM) {
			ret[x][y] = direction::down;
			q.push({ x, y, direction::down });
		}
		x = xs, y = ys + 1;
		if (lvl.possiblestandon(x, y) && ret[x][y] == direction::LAST_ITEM) {
			ret[x][y] = direction::left;
			q.push({ x, y, direction::left });
		}
		x = xs, y = ys - 1;
		if (lvl.possiblestandon(x, y) && ret[x][y] == direction::LAST_ITEM) {
			ret[x][y] = direction::right;
			q.push({ x, y, direction::right });
		}
	}
	return ret;
}
#include <iostream>
extern "C" __declspec(dllexport) void Makenextstep(Dungeon& dungeon) {
	LVL& lvl = dungeon.herolvl();
	Matrix<direction> m = directions(lvl, dungeon.hero.xpos, dungeon.hero.ypos);
	for (Enemy& now : lvl.getenemies()) {
		if (now.xpos == dungeon.hero.xpos && now.ypos == dungeon.hero.ypos) {
			dungeon.attack(now, dungeon.hero);
		}
		else if (m[now.xpos][now.ypos] != direction::LAST_ITEM) dungeon.bodymove(now, m[now.xpos][now.ypos]);
	}
}