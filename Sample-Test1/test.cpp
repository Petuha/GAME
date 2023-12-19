#include "pch.h"

long long sum(long long a, int b) {
	return a + b;
}

TEST(Matrix, calc) {
	MemoryLeakDetector meamleak;
	int n = 5, m = 6;
	Matrix<int> mat(n, m);
	int x = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mat[i][j] = x;
			x++;
		}
	}
	std::vector<long long> arr = mat.calc<long long>(0, sum);
	for (int i = 0; i < n; i++) {
		EXPECT_EQ(arr[i], 1LL * (1LL * m * (2 * i + 1) + 1) * m / 2);
	}
}

TEST(Matrix, iterators1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 1);
	for (auto& now : m) {
		EXPECT_NO_THROW(now = 1);
		now = 1;
	}
	for (int i = 0; i < 10; i++) {
		EXPECT_NO_THROW(m[i][0]);
		EXPECT_EQ(m[i][0], 1);
	}
}

TEST(Matrix, iterators2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(1, 10);
	for (auto& now : m) {
		EXPECT_NO_THROW(now = 1);
	}
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(m[0][i], 1);
	}
}

TEST(Matrix, iterators_plusplus1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	auto now = m.begin();
	int x = 1;
	while (now != m.end()) {
		EXPECT_NO_THROW(*now = x);
		x++;
		now++;
	}
	x = 1;
	now = m.begin();
	while (now != m.end()) {
		EXPECT_EQ(*now, x);
		x++;
		now++;
	}
}

TEST(Matrix, iterators_plusplus2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	int x = 1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m[i][j] = x;
			x++;
		}
	}
	x = 1;
	auto now = m.begin();
	while (now != m.end()) {
		EXPECT_EQ(*now, x);
		x++;
		now++;
	}
}

TEST(Matrix, iterators_minusminus1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	auto now = --m.end();
	int x = 1;
	while (now != m.begin()) {
		EXPECT_NO_THROW(*now = x);
		x++;
		now--;
	}
	EXPECT_NO_THROW(*now = x);
	x++;
	x = 1;
	now = --m.end();
	while (now != m.begin()) {
		EXPECT_EQ(*now, x);
		x++;
		now--;
	}
	EXPECT_EQ(*now, x);
	x++;
}

TEST(Matrix, iterators_minusminus2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	int x = 1;
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			m[i][j] = x;
			x++;
		}
	}
	x = 1;
	auto now = --m.end();
	while (now != m.begin()) {
		EXPECT_EQ(*now, x);
		x++;
		now--;
	}
	EXPECT_EQ(*now, x);
	x++;
}

TEST(Matrix, reversed_iterators_plusplus1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	auto now = m.rbegin();
	int x = 1;
	while (now != m.rend()) {
		EXPECT_NO_THROW(*now = x);
		x++;
		now++;
	}
	x = 1;
	now = m.rbegin();
	while (now != m.rend()) {
		EXPECT_EQ(*now, x);
		x++;
		now++;
	}
}

TEST(Matrix, reversed_iterators_plusplus2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	int x = 1;
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			m[i][j] = x;
			x++;
		}
	}
	x = 1;
	auto now = m.rbegin();
	while (now != m.rend()) {
		EXPECT_EQ(*now, x);
		x++;
		now++;
	}
}

TEST(Matrix, reversed_iterators_minusminus1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	auto now = --m.rend();
	int x = 1;
	while (now != m.rbegin()) {
		EXPECT_NO_THROW(*now = x);
		x++;
		now--;
	}
	EXPECT_NO_THROW(*now = x);
	x++;
	x = 1;
	now = --m.rend();
	while (now != m.rbegin()) {
		EXPECT_EQ(*now, x);
		x++;
		now--;
	}
	EXPECT_EQ(*now, x);
	x++;
}

TEST(Matrix, reversed_iterators_minusminus2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	int x = 1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m[i][j] = x;
			x++;
		}
	}
	x = 1;
	auto now = --m.rend();
	while (now != m.rbegin()) {
		EXPECT_EQ(*now, x);
		x++;
		now--;
	}
	EXPECT_EQ(*now, x);
	x++;
}

TEST(Matrix, iterators_for1) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	int x = 1;
	for (auto& now : m) {
		EXPECT_NO_THROW(now = x);
		x++;
	}
	x = 1;
	for (auto now : m) {
		EXPECT_EQ(now, x);
		x++;
	}
}

TEST(Matrix, iterators_for2) {
	MemoryLeakDetector meamleak;
	Matrix<int> m(10, 10);
	for (auto& now : m) {
		EXPECT_NO_THROW(now = -5);
	}
	int x = 1;
	for (auto now : m) {
		EXPECT_NO_THROW(now = x);
		x++;
	}
	for (auto now : m) {
		EXPECT_EQ(now, -5);
	}
}

TEST(Game, EnemyConstructorBase) {
	MemoryLeakDetector meamleak;
	EXPECT_NO_THROW(Enemy e(50, species::demon, "doedala"));
}

TEST(Game, EnemyConstructorCopy1) {
	MemoryLeakDetector meamleak;
	try {
		Enemy e(1, species::demon, "biba");
		Enemy e1(e);
	}
	catch (...) {
		EXPECT_TRUE(0);
	}
}


HINSTANCE loadhealpotion() {
	HINSTANCE load;
#ifdef NDEBUG
	load = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Release\\HealingPotion.dll");
#else
	load = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Debug\\HealingPotion.dll");
#endif
	return load;
}

TEST(Game, EnemyConstructorCopy2) {
	MemoryLeakDetector meamleak;
	HINSTANCE load = loadhealpotion();
	EXPECT_TRUE(load);
	if (!load) return;
	ContRuctor ctr = (ContRuctor)GetProcAddress(load, "CTR");
	EXPECT_TRUE(ctr);
	if (!ctr) return;
	Enemy e(50, species::demon, "doedala");
	EXPECT_NO_THROW(e.equipitem(Weapon(123, "dubina")));
	for (int i = 0; i < 100; i++) {
		EXPECT_NO_THROW(e.equipitem(Potion(ctr, { {"hptoheal", rand() % 100} })));
	}
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::chest, 100, atribute::agility, 113)));
	EXPECT_NO_THROW(e.equipitem(Armor(armortype::head, 100)));
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::legs, 100, atribute::maxhp, 113)));
	EXPECT_NO_THROW(Enemy e1 = e);
	FreeLibrary(load);
}


TEST(Game, EnemyOperatorCopy1) {
	MemoryLeakDetector meamleak;
	Enemy e(1, species::demon, "biba");
	Enemy e1(1, species::human, "bibassss");
	EXPECT_NO_THROW(e1 = e);
}

TEST(Game, EnemyOperatorCopy2) {
	MemoryLeakDetector meamleak;
	HINSTANCE load = loadhealpotion();
	EXPECT_TRUE(load);
	if (!load) return;
	ContRuctor ctr = (ContRuctor)GetProcAddress(load, "CTR");
	EXPECT_TRUE(ctr);
	if (!ctr) return;
	Enemy e(50, species::demon, "doedala");
	EXPECT_NO_THROW(e.equipitem(Weapon(123, "dubina")));
	for (int i = 0; i < 100; i++) {
		EXPECT_NO_THROW(e.equipitem(Potion(ctr, { {"hptoheal", rand() % 100} })));
	}
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::chest, 100, atribute::agility, 113)));
	EXPECT_NO_THROW(e.equipitem(Armor(armortype::head, 100)));
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::legs, 100, atribute::maxhp, 113)));
	Enemy e1(10, species::demon, "123");
	EXPECT_NO_THROW(e1 = e);
	FreeLibrary(load);
}

Enemy renemy() {
	Enemy e(60, species::skeleton, "balda");
	return e;
}

TEST(Game, EnemyConstructorMove1) {
	MemoryLeakDetector meamleak;
	EXPECT_NO_THROW(Enemy e = renemy());
}

TEST(Game, EnemyConstructorMove2) {
	MemoryLeakDetector meamleak;
	HINSTANCE load = loadhealpotion();
	EXPECT_TRUE(load);
	if (!load) return;
	ContRuctor ctr = (ContRuctor)GetProcAddress(load, "CTR");
	EXPECT_TRUE(ctr);
	if (!ctr) return;
	Enemy e(50, species::demon, "doedala");
	EXPECT_NO_THROW(e.equipitem(Weapon(123, "dubina")));
	for (int i = 0; i < 100; i++) {
		EXPECT_NO_THROW(e.equipitem(Potion(ctr, { {"hptoheal", rand() % 100} })));
	}
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::chest, 100, atribute::agility, 113)));
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::head, 100, atribute::force, 113)));
	EXPECT_NO_THROW(e.equipitem(Armor(armortype::legs, 100)));
	Enemy e1 = std::move(e);
	EXPECT_FALSE(e.usepotion(0));
	EXPECT_NO_THROW(e1.usepotion(1));
	FreeLibrary(load);
}

TEST(Game, EnemyOperatorMove1) {
	MemoryLeakDetector meamleak;
	Enemy e(1, species::skeleton, "31298713978128937");
	EXPECT_NO_THROW(e = renemy());
}

TEST(Game, EnemyOperatorMove2) {
	MemoryLeakDetector meamleak;
	HINSTANCE load = loadhealpotion();
	EXPECT_TRUE(load);
	if (!load) return;
	ContRuctor ctr = (ContRuctor)GetProcAddress(load, "CTR");
	EXPECT_TRUE(ctr);
	if (!ctr) return;
	Enemy e(50, species::demon, "doedala");
	EXPECT_NO_THROW(e.equipitem(Weapon(123, "dubina")));
	for (int i = 0; i < 100; i++) {
		EXPECT_NO_THROW(e.equipitem(Potion(ctr, { {"hptoheal", rand() % 100} })));
	}
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::chest, 100, atribute::agility, 113)));
	EXPECT_NO_THROW(e.equipitem(ArtifactArmor(armortype::head, 100, atribute::force, 113)));
	EXPECT_NO_THROW(e.equipitem(Armor(armortype::legs, 100)));
	Enemy e1(1, species::skeleton, "31298713978128937");
	EXPECT_NO_THROW(e1 = std::move(e));
	EXPECT_FALSE(e.usepotion(0));
	EXPECT_NO_THROW(e1.usepotion(1));
	FreeLibrary(load);
}

TEST(Game, HeroConstructor1) {
	MemoryLeakDetector meamleak;
	EXPECT_NO_THROW(Hero h(0, 1, species::human, "AhAhAhA"));
}

TEST(Game, HeroConstructor2) {
	MemoryLeakDetector meamleak;
	Hero h(0, 1, species::human, "AhAhAhA");
	EXPECT_NO_THROW(Hero h1 = h);
}

TEST(Game, HeroConstructor3) {
	MemoryLeakDetector meamleak;
	Hero h(0, 1, species::human, "AhAhAhA");
	Hero h1(1, 1, species::demon, "BGBGBGBGBG");
	EXPECT_NO_THROW(h1 = h);
}

TEST(Game, HPBehavior) {
	MemoryLeakDetector meamleak;
	HINSTANCE load = loadhealpotion();
	EXPECT_TRUE(load);
	if (!load) return;
	ContRuctor ctr = (ContRuctor)GetProcAddress(load, "CTR");
	EXPECT_TRUE(ctr);
	if (!ctr) return;
	Hero h(0, 50, species::human, "Gerich");
	for (int i = 0; i < 100; i++) h.lvlup(atribute::maxhp);
	h.equipitem(Potion(ctr, { {"hptoheal", 100} }));
	EXPECT_TRUE(h.usepotion(0));
	Enemy e(1, species::skeleton, "Loshok");
	e.equipitem(Weapon(10, "ubivatel"));
	int hp = h.hp;
	e.attack(h);
	EXPECT_EQ(h.hp + 10, hp);
	h.equipitem(Potion(ctr, { {"hptoheal", 100} }));
	EXPECT_TRUE(h.usepotion(0));
	EXPECT_EQ(h.hp, hp);
	FreeLibrary(load);
}

TEST(Game, testitemschests1) {
	MemoryLeakDetector meamleak;
	Dungeon dungeon(species::human, "Durak", {
		LVL(6, 6, 0, 0, 5, 5)
		});
	dungeon[0].additem(1, 1, Weapon(100));
}

TEST(Game, testitemsfloor1) {
	Dungeon dungeon(species::human, "heroname", {
			LVL(2, 2, 1, 1, 0, 0),
			LVL(5, 5, 1, 3, 0, 0),
			LVL(6, 6, 3, 3, 5, 5),
			LVL(10, 1, 0, 0, 9, 0)
		});
	for (int i = 0; i < 4; i++) dungeon[1].changesquaretype(i, 1, SquareWall());
	dungeon[0].addenemy(Enemy(100, species::skeleton, "ahah", 1, 1));
	for (int i = 0; i < 100; i++) dungeon[0].getenemies()[0].lvlup(atribute::maxhp);

	dungeon[0].additem(1, 0, Weapon(10, "Dubina"));
	dungeon[0].addchest(0, 1, Chest(10));

	dungeon[1].changesquaretype(3, 2, SquareWall());
	dungeon[1].changesquaretype(3, 3, SquareWall());
	for (int i = 1; i < 6; i++) dungeon[2].changesquaretype(4, i, SquareWall());
	for (int i = 1; i < 4; i++) dungeon[2].changesquaretype(i, 1, SquareWall());
	dungeon[1].addchest(2, 2, Chest(0));
	dungeon[1].additem(0, 2, BunchOfKeys(100));

	dungeon.useladder();
	dungeon.bodymove(dungeon.hero, direction::up);
	dungeon.bodymove(dungeon.hero, direction::left);
	dungeon.pickitem();
	dungeon.bodymove(dungeon.hero, direction::down);
	dungeon.bodymove(dungeon.hero, direction::right);
	dungeon.useladder();
	dungeon.bodymove(dungeon.hero, direction::right);
	EXPECT_NO_THROW(dungeon.tryopenchest());
}

TEST(Game, testitemschests2) {
	MemoryLeakDetector meamleak;
	Dungeon dungeon(species::human, "Durak", {
		LVL(6, 6, 0, 0, 5, 5)
		});
	dungeon[0].additem(1, 1, Weapon(100));
	dungeon[0].additem(2, 1, EnchantedWeapon(100, species::human, 2));
	dungeon[0].additem(3, 1, ArtifactWeapon(60, atribute::agility, 70));
	dungeon[0].additem(4, 1, ArtifactArmor(armortype::head, 10, atribute::force, 10));
	dungeon.bodymove(dungeon.hero, direction::down);
	dungeon.bodymove(dungeon.hero, direction::right);
	EXPECT_TRUE(dungeon.pickitem());
}

TEST(Game, TestNextStep) {
	MemoryLeakDetector meamleak;
	Dungeon dungeon(species::human, "Biba", { LVL(10, 10, 4, 5, 9, 9) });
	for (int i = 1; i < 9; i++) dungeon[0].changesquaretype(i, 1, SquareWall());
	for (int i = 2; i < 9; i++) dungeon[0].changesquaretype(8, i, SquareWall());
	for (int i = 1; i < 8; i++) dungeon[0].changesquaretype(i, 8, SquareWall());
	for (int i = 3; i < 8; i++) dungeon[0].changesquaretype(1, i, SquareWall());
	for (int i = 2; i < 7; i++) dungeon[0].changesquaretype(i, 3, SquareWall());
	for (int i = 4; i < 7; i++) dungeon[0].changesquaretype(6, i, SquareWall());
	for (int i = 3; i < 6; i++) dungeon[0].changesquaretype(i, 6, SquareWall());
	dungeon[0].changesquaretype(3, 5, SquareWall());
	Enemy enemy = Enemy(10, species::demon);
	enemy.xpos = enemy.ypos = 0;
	dungeon[0].addenemy(enemy);
	enemy.xpos = enemy.ypos = 9;
	dungeon[0].addenemy(enemy);
	enemy.xpos = 0, enemy.ypos = 9;
	dungeon[0].addenemy(enemy);
	enemy.xpos = 9, enemy.ypos = 1;
	dungeon[0].addenemy(enemy);

	HINSTANCE load;
#ifdef NDEBUG
	load = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Release\\DungeonNextStep.dll");
#else
	load = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Debug\\DungeonNextStep.dll");
#endif
	EXPECT_TRUE(load);
	if (!load) return;
	typedef void(*MakeNextStep)(Dungeon&);
	MakeNextStep makenextstep = (MakeNextStep)GetProcAddress(load, "Makenextstep");
	EXPECT_TRUE(makenextstep);
	if (!makenextstep) return;
	Matrix<int> dists;
	using namespace std;
	LVL& lvl = dungeon[0];
	Hero& hero = dungeon.hero;
	auto getdists = [&]() {
		Matrix<int> dst(10, 10);
		for (auto& now : dst) now = INT_MAX;
		queue<tuple<int, int, int>> q;
		dst[hero.xpos][hero.ypos] = 0;
		q.push({ hero.xpos, hero.ypos, 0 });
		int xs, ys, d, x, y;
		while (q.size()) {
			tie(xs, ys, d) = q.front();
			q.pop();
			x = xs + 1, y = ys;
			if (lvl.possiblestandon(x, y) && dst[x][y] == INT_MAX) {
				dst[x][y] = d + 1;
				q.push({ x, y, dst[x][y] });
			}
			x = xs, y = ys + 1;
			if (lvl.possiblestandon(x, y) && dst[x][y] == INT_MAX) {
				dst[x][y] = d + 1;
				q.push({ x, y, dst[x][y] });
			}
			x = xs - 1, y = ys;
			if (lvl.possiblestandon(x, y) && dst[x][y] == INT_MAX) {
				dst[x][y] = d + 1;
				q.push({ x, y, dst[x][y] });
			}
			x = xs, y = ys - 1;
			if (lvl.possiblestandon(x, y) && dst[x][y] == INT_MAX) {
				dst[x][y] = d + 1;
				q.push({ x, y, dst[x][y] });
			}
		}
		return dst;
		};
	dists = getdists();
	vector<int> prevdists(lvl.getenemies().size());
	auto now = prevdists.begin();
	for (Enemy& enemy : lvl.getenemies()) {
		*now = dists[enemy.xpos][enemy.ypos];
		EXPECT_TRUE(*now != INT_MAX);
		now++;
	}
	bool flag = 1;
	while (flag) {
		flag = 0;
		makenextstep(dungeon);
		dists = getdists();
		now = prevdists.begin();
		for (Enemy& enemy : lvl.getenemies()) {
			if (enemy.xpos == hero.xpos && enemy.ypos == hero.ypos) {
				now++;
				continue;
			}
			flag = 1;
			EXPECT_EQ(dists[enemy.xpos][enemy.ypos] + 1, *now);
			*now = dists[enemy.xpos][enemy.ypos];
			now++;
		}
	}
	FreeLibrary(load);
}