
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
#include "Snotify/cPersonGenerator.h"

std::string babyFileName = "Config/BabyName/yob2000.txt";
std::string streetFileName = "Config/StreetName/Street_Names.csv";
std::string surnameFileName = "Config/Surname/Names_2010Census.csv";
std::string errorMessage;

int main()
{

	cPersonGenerator personGenerator;



	personGenerator.LoadCensusFiles(babyFileName, surnameFileName, streetFileName, errorMessage);

	cPerson* person = personGenerator.generateRandomPerson();

	std::cout << "Name : " <<person->first<< std::endl;
	std::cout << "surname : " <<person->last<< std::endl;
	std::cout << "Age :" <<person->age<< std::endl;
	std::cout << "Gender :" <<person->getGenderAsString()<< std::endl;
	std::cout << "SIN :" <<person->SIN<< std::endl;
	std::cout << "Snotify UID :" <<person->getSnotifyUniqueUserID()<< std::endl;
	//std::cout << "Last data : " << personGenerator.babyDataList.GetLast().name << std::endl;

	 person = personGenerator.generateRandomPerson();
	 std::cout << std::endl;
	std::cout << "Name : " << person->first << std::endl;
	std::cout << "surname : " << person->last << std::endl;
	std::cout << "Age :" << person->age << std::endl;
	std::cout << "Gender :" << person->getGenderAsString() << std::endl;
	std::cout << "SIN :" << person->SIN << std::endl;
	std::cout << "Snotify UID :" << person->getSnotifyUniqueUserID() << std::endl;
	return 0;
}