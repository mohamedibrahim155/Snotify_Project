
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
#include "Snotify/cPersonGenerator.h"
#include <chrono>
#include<random>
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

	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

	musicGenerator.LoadMusicInformation(musicFileName, errorMessage);

	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

	std::cout << "Time Elapsed: " << elapsed_time.count() << " Seconds" << std::endl;



	//for (size_t i = 0; i < musicGenerator.ListOfSongs.GetLength(); i++)
	//{
	//	/*cPerson* person = personGenerator.generateRandomPerson();
	//	std::cout << "Name : " << person->first << std::endl;
	//	std::cout << "surname : " << person->last << std::endl;
	//	std::cout << "Age :" << person->age << std::endl;
	//	std::cout << "Gender :" << person->getGenderAsString() << std::endl;
	//	std::cout << "SIN :" << person->SIN << std::endl;
	//	std::cout << "Snotify UID :" << person->getSnotifyUniqueUserID() << std::endl;
	//	std::cout << std::endl;*/


	//	std::cout << "Name : " << musicGenerator.ListOfSongs[i]->name << std::endl;
	//	std::cout << "Artist : " << musicGenerator.ListOfSongs[i]->artist << std::endl;
	//	std::cout << "Song UID : " << musicGenerator.ListOfSongs[i]->uniqueID << std::endl;
	//	std::cout << std::endl; 
	//	
	//}

	//std::cout << "BEFORE BUBBLE SORT ############" << std::endl;

	//musicGenerator.BubbleSortSongList();

	//for (size_t i = 0; i < 50; i++)
	//{
	//	/*cPerson* person = personGenerator.generateRandomPerson();
	//	std::cout << "Name : " << person->first << std::endl;
	//	std::cout << "surname : " << person->last << std::endl;
	//	std::cout << "Age :" << person->age << std::endl;
	//	std::cout << "Gender :" << person->getGenderAsString() << std::endl;
	//	std::cout << "SIN :" << person->SIN << std::endl;
	//	std::cout << "Snotify UID :" << person->getSnotifyUniqueUserID() << std::endl;
	//	std::cout << std::endl;*/


	//	std::cout << "Name : " << musicGenerator.ListOfSongs[i]->name << std::endl;
	//	std::cout << "Artist : " << musicGenerator.ListOfSongs[i]->artist << std::endl;
	//	std::cout << "Song UID : " << musicGenerator.ListOfSongs[i]->uniqueID << std::endl;
	//	std::cout << std::endl;

	//}

	std::cout << "AFTER BUBBLE SORT ############" << std::endl;

	//std::cout << " Total songs : " << musicGenerator.ListOfSongs.GetLength() << std::endl;


	////cSong* findSong = musicGenerator.findSong("Poor Little Fool", "Ricky Nelson");
	//
	//cSong* findSong = musicGenerator.findSong("Broomstick Cowboy", "Bobby Goldsboro");

	//if (findSong)
	//{
	//	std::cout << "Found name " << findSong->name << std::endl;
	//	std::cout << " Found Artist name : " << findSong->artist << std::endl;
	//	std::cout << " UID : " << findSong->getUniqueID() << std::endl;
	//}
	//else
	//{
	//	std::cout << "Song not existed" << std::endl;
	//}




	
	return 0;
}