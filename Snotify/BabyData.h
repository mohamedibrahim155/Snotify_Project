#pragma once
#include <iostream>
#include <string>

struct BabyData
{
	BabyData() {};
	BabyData(std::string _name, std::string _gender, int _count) :
		name(_name), gender(_gender), count(_count)
	{};
	std::string name;
	std::string gender;
	int count;
};

struct StreetData
{

	std::string fullStreetName;
	std::string streetName;
	std::string streetType;
	std::string postDirection;
};

struct Surname
{
	std::string surname;
	std::string rank;
};