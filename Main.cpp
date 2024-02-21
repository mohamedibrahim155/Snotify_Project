
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
#include "Snotify/cPersonGenerator.h"
#include "Snotify/cSnotify.h"
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
	cSnotify snotify;

	


	personGenerator.LoadCensusFiles(babyFileName, surnameFileName, streetFileName, errorMessage);

	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

	musicGenerator.LoadMusicInformation(musicFileName, errorMessage);

	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

	std::cout << "Time Elapsed: " << elapsed_time.count() << " Seconds" << std::endl;


	List<cSong*> songlist;

	for (size_t i = 0; i < 15; i++)
	{
		cSong* randomSong = musicGenerator.getRandomSong();


		snotify.AddSong(randomSong, errorMessage);
		songlist.Add(randomSong);

		std::cout << "Added Song : " << randomSong->name << std::endl;

		
	}


	
	cPerson*  updateUser = new cPerson();
	
	List<SnotifyUser*> snotifyUsers;

	for (size_t i = 0; i < 10; i++)
	{
		cPerson* randomperson = personGenerator.generateRandomPerson();

	
		snotify.AddUser(randomperson, errorMessage);
		
		SnotifyUser* testUser = new SnotifyUser();

		testUser->person = randomperson;

		snotifyUsers.Add(testUser);


		if (i == 0)
		{
			updateUser = randomperson;   // for test taking one person
		}
		if (i == 2)
		{
			randomperson->first = "MOHAMED";
			randomperson->middle = "AHAMED";
		}
		//std::cout << "Added person : " << randomperson->first << std::endl;
		//std::cout << "UID : " << randomperson->getSnotifyUniqueUserID() << std::endl;

		
	}


	std::cout << std::endl;

	updateUser->first = "MOHAMED";
	updateUser->middle = "IBRAHIM";
	updateUser->last = "DAWOOD";
	updateUser->age = 23;

	snotify.UpdateUser(updateUser, errorMessage);



	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2), errorMessage);
	std::cout << errorMessage << std::endl;

	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(3), errorMessage);
	std::cout << errorMessage << std::endl;
	
	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(3), errorMessage);
	std::cout << errorMessage << std::endl;

	snotify.RemoveSongFromUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(3)->getUniqueID(), errorMessage);
	std::cout << errorMessage << std::endl;

	unsigned int rating = 5;
	snotify.UpdateRatingOnSong(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), rating);

	cSong* updatedSongcheck = snotify.GetSong(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), errorMessage);
        
	std::cout << "updated song rating : " << updatedSongcheck->rating << std::endl;
	std::cout << "updated number of Plays : " << updatedSongcheck->numberOfTimesPlayed << std::endl;

	//cPerson* users;
	//unsigned int size;

	//snotify.GetUsers(users, size);

	//for (size_t i = 0; i < size; i++)
	//{

	//	std::cout << "Get user name : " << users[i].first << std::endl;
	//	std::cout << "Get user Middle : " << users[i].middle << std::endl;
	//	std::cout << "Get user lasr : " << users[i].last << std::endl;
	//	std::cout << "UID : " << users[i].getSnotifyUniqueUserID() << std::endl;

	//}

	//cPerson* users2;
	//unsigned int size2;
	//snotify.FindUsersFirstName("MOHAMED", users2, size2);

	//for (size_t i = 0; i < size2; i++)
	//{

	//	std::cout << "Found user name : " << users2[i].first << std::endl;
	//	std::cout << "Found user Middle name : " << users2[i].middle << std::endl;
	//	std::cout << "Found user Last name : " << users2[i].last << std::endl;
	//	std::cout << "UID : " << users2[i].getSnotifyUniqueUserID() << std::endl;

	//}


	return 0;
}