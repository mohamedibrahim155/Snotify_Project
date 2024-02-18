
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

	//std::cout << "Last data : " << personGenerator.babyDataList.GetLast().name << std::endl;


	return 0;
}