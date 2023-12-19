#include "HeavyObject.h"
using namespace std;
using namespace sf;
ContRuctor HeavyObject::getpotion(const string& id)
{
	return potionsconstructors[id];
}

HeavyObject::HeavyObject(string path, Font* font) : textures(path), sounds(path)
{
	this->font = font;
	wstring pth(path.begin(), path.end());
	pth += L"plugin/";
#ifdef NDEBUG
	loadnextstep = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Release\\DungeonNextStep.dll");
#else
	loadnextstep = LoadLibrary(L"C:\\Users\\12345\\source\\repos\\GAME\\x64\\Debug\\DungeonNextStep.dll");
#endif
	if (!loadnextstep) {
		throw runtime_error("could not load the dynamic library\n");
	}
	makenextstep = (MakeNextStep)GetProcAddress(loadnextstep, "Makenextstep");
	if (!makenextstep) {
		throw runtime_error("could not locate the function\n");
	}
	// load potions ctrs here
#ifdef NDEBUG
	pth += L"Release/";
#else
	pth += L"Debug/";
#endif
	for (auto& file : 
		std::filesystem::recursive_directory_iterator(pth)) {
		if (file.is_directory()) continue;
		loads.push_back(LoadLibrary(file.path().filename().c_str()));
		if (!loads.back()) {
			throw runtime_error("could not load the dynamic library\n");
		}
		string name = file.path().filename().string();
		for (int i = 0; i < 4 && name.size(); i++) name.pop_back();
		potionsconstructors[name] = (ContRuctor)GetProcAddress(loads.back(), "CTR");
		if (!potionsconstructors[name]) {
			throw runtime_error("could not locate the function\n");
			potionsconstructors.erase(name);
		}
	}
}

HeavyObject::~HeavyObject()
{
	if (loadnextstep) FreeLibrary(loadnextstep);
	for (auto& now : loads) FreeLibrary(now);
}
