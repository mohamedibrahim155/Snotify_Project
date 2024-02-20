#include "cSnotify.h"


// This returns a COPY of the users library, in the form of a regular dynamic array.
//bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);
//{
	// The caller would do something like this (assume the user ID = 28472382)
	//
	//	cSong* pTheSongs = 0;
	//	unsigned int arraySize = 0;
	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
	// 
	// Inside this method, you'd do something like this:

	// TODO: Find that user... 

	// Alloate a heap based array to hold all the songs...

//	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
//	pCopyOfLibrary = new cSong[sizeOfLibary];

	// The array and the size of the array are "returned" by reference to the caller. 

	// TODO: Copy all the songs over

//	return true;
//}

cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	SnotifyUser* newSnotifyUser = new SnotifyUser();

	newSnotifyUser->person = pPerson;

	ListOfSnotifyUsers.InsertBeforeCurrent(newSnotifyUser);

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	SnotifyUser* UpdatedUser = nullptr;

	if (GetUserWithSnotifyIdAndSIN(pPerson->getSnotifyUniqueUserID(), pPerson->SIN, UpdatedUser))
	{
		UpdatedUser->person = pPerson;

		return true;
	}


	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	
	SnotifyUser* snotifyUser = nullptr;

	if (GetUserWithSnotifyId(SnotifyUserID, snotifyUser))
	{
		ListOfSnotifyUsers.DeleteAtCurrent();

		return true;
	}

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{

	ListOfSongs.InsertBeforeCurrent(pSong);
	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cSong* updatedSong = nullptr;
	if (GetSongWithId(pSong->getUniqueID(), updatedSong))
	{
		updatedSong = pSong;
		return true;
	}
	
	 
	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{

	cSong* deleteSong = nullptr;

	if (GetSongWithId(UniqueSongID, deleteSong))
	{
		ListOfSnotifyUsers.DeleteAtCurrent();

		return true;
	}

	return false;
}


bool cSnotify::CheckString(std::string fistname, std::string lastname)
{
	return IsAscendingOrderString(fistname.c_str(), lastname.c_str());
}

bool cSnotify::GetUserWithSnotifyId(unsigned int snotifyId, SnotifyUser*& snotifyUser)
{

	if (ListOfSnotifyUsers.IsEmpty())
	{

		return false;
	}

	ListOfSnotifyUsers.MoveToFirst();

	SnotifyUser* findUser = ListOfSnotifyUsers.GetCurrentNode()->data;

	do
	{
		if (findUser->person->getSnotifyUniqueUserID() == snotifyId)
		{
			snotifyUser = findUser;
			return true;
		}
		else
		{
			ListOfSnotifyUsers.MoveNext();

			findUser = ListOfSnotifyUsers.GetCurrentNode()->data;

		}
	} while (ListOfSnotifyUsers.GetCurrentNode());
	

	return false;
}

bool cSnotify::GetUserWithSnotifyIdAndSIN(unsigned int snotifyId, unsigned int SIN, SnotifyUser*& snotifyUser)
{

	if (ListOfSnotifyUsers.IsEmpty())
	{

		return false;
	}

	ListOfSnotifyUsers.MoveToFirst();

	SnotifyUser* findUserWithSIN = ListOfSnotifyUsers.GetCurrentNode()->data;

	do
	{
		if (findUserWithSIN->person->getSnotifyUniqueUserID() == snotifyId && findUserWithSIN->person->SIN == SIN )
		{

			std::cout << "User found" << std::endl;
			snotifyUser = findUserWithSIN;
			return true;
		}
		else
		{
			ListOfSnotifyUsers.MoveNext();

			findUserWithSIN = ListOfSnotifyUsers.GetCurrentNode()->data;

		}
	} while (ListOfSnotifyUsers.GetCurrentNode());


	std::cout << "User Not found" << std::endl;
	return false;
}

bool cSnotify::GetSongWithId(unsigned int songId, cSong*& song)
{



	if (ListOfSongs.IsEmpty())
	{

		return false;
	}

	ListOfSongs.MoveToFirst();

	cSong* findSong = ListOfSongs.GetCurrentNode()->data;

	do
	{
		if (findSong->getUniqueID() == songId)
		{

			std::cout << "Found Song" << std::endl;
			song = findSong;
			return true;
		}
		else
		{
			ListOfSongs.MoveNext();

			findSong = ListOfSongs.GetCurrentNode()->data;

		}
	} while (ListOfSongs.GetCurrentNode());


	return false;
}

unsigned int cSnotify::CreateSongHash(std::string& songName, std::string& artistName)
{
	unsigned int songHash = 0;

	std::string combinedValue = songName + artistName;

	songHash = CustomHash(combinedValue);



	return songHash;
}

unsigned int cSnotify::CustomHash(const std::string& input)
{
	unsigned int  hash = 0;

	for (char c : input)
	{
		hash = hash * 31 + static_cast<unsigned char>(c);
	}

	return hash;
}

bool cSnotify::IsAscendingOrderString(const char* a, const char* b)
{
	
	while (*a != '\0' && *b != '\0')
	{
		if (*a < *b)
		{
			return true;  
		}
		else if (*a > *b)
		{
			return false; 
		}
	
		++a;
		++b;
	}

	return (*a == '\0' && *b != '\0');
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		std::cout << "No snotify users found" <<  __FILE__ << std::endl;
		return nullptr;
	}

	cPerson* userWithSIN = ListOfSnotifyUsers.GetCurrentNode()->data->person;

	ListOfSnotifyUsers.MoveToFirst();

	do
	{
		if (userWithSIN->SIN == SIN)
		{
			return userWithSIN;
		}
		else
		{

			ListOfSnotifyUsers.MoveNext();

			userWithSIN = ListOfSnotifyUsers.GetCurrentNode()->data->person;
		}

	} while (ListOfSnotifyUsers.GetCurrentNode());


	return nullptr;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		std::cout << "No snotify users found" << __FILE__ << std::endl;
		return nullptr;
	}

	cPerson* userWithSpotifyID = ListOfSnotifyUsers.GetCurrentNode()->data->person;

	ListOfSnotifyUsers.MoveToFirst();

	do
	{
		if (userWithSpotifyID->getSnotifyUniqueUserID() == SnotifyID)
		{
			return userWithSpotifyID;
		}
		else
		{

			ListOfSnotifyUsers.MoveNext();

			userWithSpotifyID = ListOfSnotifyUsers.GetCurrentNode()->data->person;
		}

	} while (ListOfSnotifyUsers.GetCurrentNode());


	return nullptr;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	unsigned int hash = CreateSongHash(title, artist);

	cSong* song = nullptr;

	if (GetSongWithId(hash, song))
	{
		return song;
	}
	else
	{
		return nullptr;
	}
	

	
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{

	cSong* song = nullptr;

	if (GetSongWithId(uniqueID, song))
	{
		return song;
	}


	return nullptr;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		pAllTheUsers = nullptr;

		sizeOfUserArray = 0;

		return false;
	}

	unsigned int size = ListOfSnotifyUsers.GetSize();

	cPerson* personsInList = new cPerson[size];
		
	ListOfSnotifyUsers.MoveToFirst();

	for (size_t i = 0; i < size; i++)
	{
		
		personsInList[i] = *(ListOfSnotifyUsers.GetCurrentNode()->data->person);

		ListOfSnotifyUsers.MoveNext();
	}

	pAllTheUsers = personsInList;
	sizeOfUserArray = size;

	return true;
}
