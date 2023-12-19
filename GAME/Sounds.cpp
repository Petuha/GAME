#include "Sounds.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
Sounds::Sounds(const string& path)
{
	this->path = wstring(path.begin(), path.end());
	this->path += L"Sounds/";
}

void Sounds::playsound(const wstring& name)
{
#ifdef NDEBUG
	PlaySound((path + name + L".wav").c_str(), nullptr, SND_ASYNC);
	/*thread th(PlaySound, (path + name + L".wav").c_str(), nullptr, SND_ASYNC); //awful idea
	th.detach();*/
#endif
}