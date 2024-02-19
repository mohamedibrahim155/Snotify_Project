#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include <random>

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

	if (!ReadSurnameFromFile(surnameFile))
	{
		errorString = "Error in loading Surname file ";

		std::cout << errorString << std::endl;

		return false;
	}
	if (!ReadBabydataFromFile(babyNameFile))
	{
		errorString = "Error in loading Baby file ";

		std::cout << errorString << std::endl;

		return false;
	}
	if (!ReadStreetNameFromFile(streetNameFile))
	{
		errorString = "Error in loading Street name file ";

		std::cout << errorString << std::endl;

		return false;
	}


	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return listOfBabynames.GetLength();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return listOfSurnames.GetLength();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return listOfStreetnames.GetLength();
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cPerson* newPerson = new cPerson();

	BabyData randomBabyName = listOfBabynames.GetAt(GetRandomNumber(0, listOfBabynames.GetLength()));

	Surname randomSurname = listOfSurnames.GetAt(GetRandomNumber(0, listOfSurnames.GetLength()));

	StreetData randomStreetname = listOfStreetnames.GetAt(GetRandomNumber(0, listOfStreetnames.GetLength()));

	newPerson->first = randomBabyName.name;  // name
	

	if (randomBabyName.gender == "F")      newPerson->gender = cPerson::FEMALE;
	else if (randomBabyName.gender == "M") newPerson->gender = cPerson::MALE;

	randomBabyName = listOfBabynames.GetAt(GetRandomNumber(0, listOfBabynames.GetLength())); // generating new name for middle name
	newPerson->middle = randomBabyName.name;  // Mid name

	newPerson->last = randomSurname.surname; // last name

	newPerson->age = GetRandomNumber(10, 80);

	newPerson->streetNumber = GetRandomNumber(1, 1000);
	newPerson->streetName = randomStreetname.streetName;  // Street name
	newPerson->streetType = randomStreetname.streetType;  // Street type
	newPerson->streetDirection = randomStreetname.postDirection; //  street Direction

	newPerson->SIN = GenerateRandomSIN();
		

	return newPerson;
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

		lincount++;

		BabyData babyData;

		if (std::getline(iss, name, ',') &&
			std::getline(iss, gender, ',') &&
			std::getline(iss, count, ','))
		{
			 int countValue;
            std::stringstream(count) >> countValue;
			babyData.name = name;
			babyData.gender = gender;
			babyData.count = countValue;

			listOfBabynames.Add(babyData);
		}

		
	}
	std::cout << "Total Lines  : " << lincount << " in " << babyfile << std::endl;
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
		lincount++;

		if (lincount == 1)
		{
			continue;
		}

		StreetData data;
		std::string token;
		unsigned int tokenCount = 0;

		while (std::getline(iss, token, ','))
		{
			if (tokenCount == 0)
			{
				data.fullStreetName = token;
			}
			else if (tokenCount == 1)
			{
				data.streetName = token;
			}
			else if (tokenCount == 2)
			{
				data.streetType = token;

			}
			else if (tokenCount == 3)
			{
				data.postDirection = token;

			}
			if (tokenCount > 4)
			{
				continue;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}

		listOfStreetnames.Add(data);

	}

	std::cout << "Total Lines  : " << lincount << " in " << streetNameFile << std::endl;

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

		lincount++;

		if (lincount == 1)
		{
			continue;
		}
		Surname data;

		if (std::getline(iss, name, ',') &&
			std::getline(iss, rank, ','))
		{
		//std::cout << "Name: " << name << std::endl;
		//std::cout << "Rank : " << rank << std::endl;

			data.surname = name;
			data.rank = rank;

			listOfSurnames.Add(data);
		}

		
	}

	std::cout << "Total Lines  : " << lincount << " in " << surname << std::endl;
	file.close();

	return true;
}

int cPersonGenerator::GetRandomNumber(int min, int max)
{
	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);
}

int cPersonGenerator::GenerateRandomSIN()
{
	int randomSIN = GetRandomNumber(100000000, 999999999);


	if (IsSINNumberFound(randomSIN))
	{
		randomSIN = GetRandomNumber(100000, 900000);
	}

	listOfSIN.Add(randomSIN);

	return randomSIN;
}

bool cPersonGenerator::IsSINNumberFound(int SIN)
{
	for (size_t i = 0; i < listOfSIN.GetLength(); i++)
	{
		if (listOfSIN[i] == SIN) true;
	}

	return false;
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