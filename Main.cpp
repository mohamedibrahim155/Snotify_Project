
#include "Utils/List.h"
#include "Snotify/cMusicGenerator.h"
#include "Snotify/cPersonGenerator.h"
#include "Snotify/cSnotify.h"
#include <chrono>
#include<random>


std::string babyFileName = "Config/BabyName/yob2000.txt";
std::string streetFileName = "Config/StreetName/Street_Names.csv";
std::string surnameFileName = "Config/Surname/Names_2010Census.csv";
std::string musicFileName = "Config/Music/hot_stuff_2.csv";
//std::string musicFileName = "Config/Music/hot_stuff_3.csv";  // test 
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
#pragma region ADDSONG

	for (size_t i = 0; i < 15; i++)
	{
		
		cSong* randomSong = musicGenerator.getRandomSong();

		snotify.AddSong(randomSong, errorMessage);
		songlist.Add(randomSong);  // adding to a local list so, I can access data

		std::cout << "Added Song : " << randomSong->name << std::endl;

		
	}
#pragma endregion


#pragma region ADDUSER



	List<SnotifyUser*> snotifyUsers;

	for (size_t i = 0; i < 10; i++)
	{
		cPerson* randomperson = personGenerator.generateRandomPerson(); // generating random person from billboard

		snotify.AddUser(randomperson, errorMessage);  // Adding user to Snotify 
		
		SnotifyUser* testUser = new SnotifyUser();

		testUser->person = randomperson;

		snotifyUsers.Add(testUser);  // Adding user  in a local List So, I can access the data  to check other  functions


		
		if (i == 2)
		{
			randomperson->first = "MOHAMED";
			randomperson->middle = "AHAMED";
		}
		//std::cout << "Added person : " << randomperson->first << std::endl;
		//std::cout << "UID : " << randomperson->getSnotifyUniqueUserID() << std::endl;

		
	}

#pragma endregion
	std::cout << std::endl;

#pragma region UPDATEUSER
	cPerson* updateUser = new cPerson();
	updateUser->SetSnotifyUniqueUserID(snotifyUsers[0]->person->getSnotifyUniqueUserID());  // taking the first index of 
	                                                                                        // created user ID to update
	updateUser->SetSIN(snotifyUsers[0]->person->SIN);

	updateUser->first = "MOHAMED";
	updateUser->middle = "IBRAHIM";
	updateUser->last = "DAWOOD";
	updateUser->age = 23;

	snotify.UpdateUser(updateUser, errorMessage);
	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region GETUSERBYID

	cPerson* personList;
	unsigned int size;
	snotify.GetUsersByID(personList, size);

	for (size_t i = 0; i < size; i++)
	{
		std::cout << "USER first name : " << personList[i].first << std::endl;
		std::cout << "Snotify id : " << personList[i].getSnotifyUniqueUserID() << std::endl;
	}
#pragma endregion


#pragma region ADDSONGTOUSERLIBRARY

	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2), errorMessage);
	std::cout << errorMessage << std::endl;

	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(3), errorMessage);
	std::cout << errorMessage << std::endl;
	
	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(4), errorMessage);
	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region REMOVESONGFROMUSERLIBRARY


	snotify.RemoveSongFromUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(3)->getUniqueID(), errorMessage);
	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region UPDATINGRATINGIONSONG



	unsigned int rating = 5;
	snotify.UpdateRatingOnSong(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), rating);
#pragma endregion

#pragma region GETCURRENTSONG_RATING

	snotify.GetCurrentSongRating(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), rating);
	std::cout << "Song rating : " << rating << std::endl;
#pragma endregion

#pragma region GETSONG
	cSong* updatedSongcheck = snotify.GetSong(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), errorMessage);
	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region GETCURRENTSONGNUMBEROFPLAYS

	unsigned int numberOfplay;
	snotify.GetCurrentSongNumberOfPlays(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2)->getUniqueID(), numberOfplay);
	std::cout << "Song number of Plays : " << numberOfplay << std::endl;

#pragma endregion

#pragma region DELETESONG

	snotify.DeleteSong(songlist.GetAt(2)->getUniqueID(), errorMessage);
	std::cout << errorMessage << std::endl;

	//Deleted song cannot be added to user
	snotify.AddSongToUserLibrary(snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID(), songlist.GetAt(2), errorMessage);

	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region FINDUSERBYSIN
	unsigned int SIN = snotifyUsers.GetAt(0)->person->SIN;
	cPerson* userWithSIN = snotify.FindUserBySIN(SIN);
	std::cout << "User SIN : " << userWithSIN->SIN << std::endl;
#pragma endregion


#pragma region GET_USERSONG_LIBRARY_WITH_ASCENDING_ARTIST
	unsigned int userId = snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID();
	cSong* songLibraryWithArtist;
	unsigned int sizeOfSongLibrary;

	snotify.GetUsersSongLibraryAscendingByArtist(userId, songLibraryWithArtist, sizeOfSongLibrary);
	for (size_t i = 0; i < sizeOfSongLibrary; i++)
	{
		std::cout << "Song artist: " << songLibraryWithArtist[i].artist << std::endl;
		std::cout << "Song id: " << songLibraryWithArtist[i].getUniqueID() << std::endl;
	}
#pragma endregion

#pragma region GETUSERS_SONGLIBRARY_ASCENDING_BY_TITLE
	 userId = snotifyUsers.GetAt(0)->person->getSnotifyUniqueUserID();
	cSong* songLibraryWithTitle;

	snotify.GetUsersSongLibraryAscendingByTitle(userId, songLibraryWithTitle, sizeOfSongLibrary);

	for (size_t i = 0; i < sizeOfSongLibrary; i++)
	{
		std::cout << "Song title: " << songLibraryWithTitle[i].name << std::endl;
		std::cout << "Song id: " << songLibraryWithTitle[i].getUniqueID() << std::endl;
	}
#pragma endregion


#pragma region GETUSERS
	cPerson* users;
	//unsigned int size;

	snotify.GetUsers(users, size);

	for (size_t i = 0; i < size; i++)
	{

		std::cout << "user first name: " << users[i].first << std::endl;
		std::cout << "user Middle name: " << users[i].middle << std::endl;
		std::cout << "user last name: " << users[i].last << std::endl;
		std::cout << "Snotify ID : " << users[i].getSnotifyUniqueUserID() << std::endl;
	}
#pragma endregion


#pragma region FINDUSERSFISTNAME
	cPerson* users2;
	unsigned int size2;
	snotify.FindUsersFirstName("MOHAMED", users2, size2);

	for (size_t i = 0; i < size2; i++)
	{

		std::cout << "Found user name : " << users2[i].first << std::endl;
		std::cout << "Found user Middle name : " << users2[i].middle << std::endl;
		std::cout << "Found user Last name : " << users2[i].last << std::endl;
		std::cout << "UID : " << users2[i].getSnotifyUniqueUserID() << std::endl;

	}
#pragma endregion

#pragma region FINDUSERSLASTNAME



	cPerson* users3;
	unsigned int size3;
	snotify.FindUsersLastName("MOHAMED", users3, size3);

	for (size_t i = 0; i < size3; i++)
	{

		std::cout << "user last name: " << users3[i].first << std::endl;
		
		std::cout << "UID : " << users3[i].getSnotifyUniqueUserID() << std::endl;

	}
#pragma endregion

#pragma region FINDUSERS_FIRSTLASTNAMES

	cPerson* users4;
	unsigned int size4;
	snotify.FindUsersFirstLastNames("MOHAMED", "AHAMED", users4,size4);

	for (size_t i = 0; i < size4; i++)
	{

		std::cout << "user last name: " << users4[i].first << std::endl;

		std::cout << "UID : " << users4[i].getSnotifyUniqueUserID() << std::endl;

	}
#pragma endregion

#pragma region DELETEUSER

	unsigned int userID = snotifyUsers[1]->person->getSnotifyUniqueUserID();  // taking index 1 user

	snotify.DeleteUser(userID, errorMessage);

	std::cout << errorMessage << std::endl;
#pragma endregion

#pragma region FINDSONG

	unsigned int findSongID = songlist.GetAt(10)->getUniqueID();

	cSong* foundSong = snotify.FindSong(findSongID);

	std::cout << "Song name: " << foundSong->name << std::endl;
	std::cout << "Song artist: " << foundSong->artist << std::endl;
	std::cout << "Song ID: " << foundSong->getUniqueID() << std::endl;

#pragma endregion

#pragma region UPDATESONG

	unsigned int SongToBeUpdated = songlist.GetAt(0)->getUniqueID();  //I am taking 1st index of songList

	cSong* updateSong = new cSong();

	updateSong->name = "SHOCKWAVE";
	updateSong->artist = "MARSHMELLOW";

	updateSong->SetUniqueID(SongToBeUpdated);

	snotify.UpdateSong(updateSong, errorMessage);
	std::cout << errorMessage << std::endl;
#pragma endregion



	return 0;
}