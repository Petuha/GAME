#pragma once
#include <string>
class Sounds
{
private:
	std::wstring path;
public:
	Sounds(const std::string& path);
	void playsound(const std::wstring& name);
};