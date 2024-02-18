#pragma once
#include <iostream>
#include <string>

struct BabyData
{
	BabyData() {};
	BabyData(std::string _name, char _gender, int _count) :
		name(_name), gender(_gender), count(_count)
	{};
	std::string name;
	char gender;
	int count;
};