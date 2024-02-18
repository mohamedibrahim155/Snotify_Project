#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>


cPersonGenerator::cPersonGenerator()
{
}

cPersonGenerator::~cPersonGenerator()
{
}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	// TODO: Put YOUR amazing code here!

	return ReadSurnameFromFile(surnameFile);
	
	return ReadStreetNameFromFile(streetNameFile);

	return LoadBabyNames(babyNameFile);
}

bool cPersonGenerator::LoadBabyNames(std::string babyfile)
{

	return ReadBabydataFromFile(babyfile);
}

bool cPersonGenerator::ReadBabydataFromFile(const std::string& babyfile)
{
	std::ifstream file(babyfile);

	if (!file.is_open()) 
	{
		std::cerr << "Error opening file: " << babyfile << std::endl;
		return false;
	}

	std::string line;
	int lincount = 0;
	while (std::getline(file, line))
	{
		//if (lincount > 50) break;
		std::istringstream iss(line);
		std::string name, gender, count;
		
		if (std::getline(iss, name, ',') &&
			std::getline(iss, gender, ',') &&
			std::getline(iss, count, ','))
		{
			 int countValue;
            std::stringstream(count) >> countValue;
			BabyData babyData(name, gender[0], std::stoi(count));
			babyDataList.Add(babyData);
		}

		lincount++;
	}

	std::cout << "Total Lines : " << lincount<< std::endl;
	file.close();
	 return true;
}

bool cPersonGenerator::ReadStreetNameFromFile(const std::string& streetNameFile)
{

	std::ifstream file(streetNameFile);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << streetNameFile << std::endl;
		return false;
	}


	std::string line;
	int lincount = 0;
	while (std::getline(file, line))
	{
		//if (lincount > 50) break;
		std::istringstream iss(line);
		std::string fullStName, StName, StType, postDir;

		if (std::getline(iss, fullStName, ',') &&
			std::getline(iss, StName, ',') &&
			std::getline(iss, StType, ',') && std::getline(iss, postDir, ','))
		{
			std::cout << "Full Street Name: " << fullStName << std::endl;
			std::cout << "Street Name: " << StName << std::endl;
			std::cout << "Street Type: " << StType << std::endl;
			std::cout << "Post direction : " << postDir << std::endl;

		}

		lincount++;
	}

	std::cout << "Total Lines : " << lincount << std::endl;
	file.close();

	return true;
}

bool cPersonGenerator::ReadSurnameFromFile(const std::string& surname)
{
	std::ifstream file(surname);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << surname << std::endl;
		return false;
	}


	std::string line;
	int lincount = 0;
	while (std::getline(file, line))
	{
		//if (lincount > 50) break;
		std::istringstream iss(line);
		std::string name, rank;

		if (std::getline(iss, name, ',') &&
			std::getline(iss, rank, ','))
		{
			std::cout << "Name: " << name << std::endl;
			std::cout << "Rank : " << rank << std::endl;
		}

		lincount++;
	}

	std::cout << "Total Lines : " << lincount << std::endl;
	file.close();

	return true;
}



// Here's a simple way to load the comma delimited files:
bool readCSVFile(void)
{
	// Open the file
	std::ifstream namesFile("Names_2010Census.csv");
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				std::cout << token << std::endl;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}