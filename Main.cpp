
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
#include "Snotify/cPersonGenerator.h"

std::string babyFileName = "Config/BabyName/yob2000.txt";
std::string streetFileName = "Config/StreetName/Street_Names.csv";
std::string surnameFileName = "Config/Surname/Names_2010Census.csv";
//std::string musicFileName = "Config/Music/hot_stuff_2.csv";
std::string musicFileName = "Config/Music/hot_stuff_2.csv";  // test 
std::string errorMessage;

int main()
{

	cPersonGenerator personGenerator;
	cMusicGenerator musicGenerator;


	personGenerator.LoadCensusFiles(babyFileName, surnameFileName, streetFileName, errorMessage);


	musicGenerator.LoadMusicInformation(musicFileName, errorMessage);


	for (size_t i = 0; i < musicGenerator.ListOfSongs.GetLength(); i++)
	{
		/*cPerson* person = personGenerator.generateRandomPerson();
		std::cout << "Name : " << person->first << std::endl;
		std::cout << "surname : " << person->last << std::endl;
		std::cout << "Age :" << person->age << std::endl;
		std::cout << "Gender :" << person->getGenderAsString() << std::endl;
		std::cout << "SIN :" << person->SIN << std::endl;
		std::cout << "Snotify UID :" << person->getSnotifyUniqueUserID() << std::endl;
		std::cout << std::endl;*/


		std::cout << "Name : " << musicGenerator.ListOfSongs[i]->name << std::endl;
		std::cout << "Artist : " << musicGenerator.ListOfSongs[i]->artist << std::endl;
		std::cout << "Song UID : " << musicGenerator.ListOfSongs[i]->uniqueID << std::endl;
		std::cout << std::endl; 
		
	}
	std::cout << " Total songs : " << musicGenerator.ListOfSongs.GetLength() << std::endl;


	//cSong* findSong = musicGenerator.findSong("Poor Little Fool", "Ricky Nelson");
	
	cSong* findSong = musicGenerator.findSong("Broomstick Cowboy", "Bobby Goldsboro");

	if (findSong)
	{
		std::cout << "Found name " << findSong->name << std::endl;
		std::cout << " Found Artist name : " << findSong->artist << std::endl;
		std::cout << " UID : " << findSong->getUniqueID() << std::endl;
	}
	else
	{
		std::cout << "Song not existed" << std::endl;
	}




	
	return 0;
}