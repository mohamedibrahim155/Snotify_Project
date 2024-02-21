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


bool IsAscendingOrderUniqueID(cPerson& aID, cPerson& bID)
{
	return aID.getSnotifyUniqueUserID() < bID.getSnotifyUniqueUserID();
}

bool IsAscendingOrderString(const char* a, const char* b)
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

bool IsAscendingOrderBySongTitle(cSong& songA, cSong& songB)
{
	std::string songValueA = songA.name;
	std::string songValueB = songB.name;

	return IsAscendingOrderString(songValueA.c_str(), songValueB.c_str());
}

bool IsAscendingOrderByArtist(cSong& songA, cSong& songB)
{
	std::string artistA = songA.artist;
	std::string artistB = songB.artist;

	return IsAscendingOrderString(artistA.c_str(), artistB.c_str());
}

bool IsAscendingbyFirstname(cPerson& aID, cPerson& bID)
{
	std::string firstNameA = (aID.first + aID.middle+aID.last);
	std::string firstNameB = (bID.first + bID.middle + bID.last);

	return IsAscendingOrderString(firstNameA.c_str(), firstNameB.c_str());
}

bool IsAscendingbyLastname(cPerson& aID, cPerson& bID)
{
	std::string lastNameA = (aID.last + aID.middle + aID.first);
	std::string lastNameB = (bID.last + bID.middle + bID.first);

	return IsAscendingOrderString(lastNameA.c_str(), lastNameB.c_str());
}

bool IsAscendingbyFirstAndLastname(cPerson& aID, cPerson& bID)
{
	std::string lastNameA = (aID.last + aID.first + aID.middle);
	std::string lastNameB = (bID.last + bID.first + bID.middle);

	return IsAscendingOrderString(lastNameA.c_str(), lastNameB.c_str());
}

//bool IsAscendingbyLastname(cPerson& aID, cPerson& bID)
//{
//	std::string lastNameA = aID.last;
//	std::string lastNameB = bID.last;
//
//	return IsAscendingOrderString(lastNameA.c_str(), lastNameB.c_str());
//}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	SnotifyUser* newSnotifyUser = new SnotifyUser();

	newSnotifyUser->person = pPerson;

	ListOfSnotifyUsers.InsertBeforeCurrent(newSnotifyUser);

	errorString = "Added user to Snotify";

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	SnotifyUser* UpdatedUser = nullptr;

	if (GetUserWithSnotifyIdAndSIN(pPerson->getSnotifyUniqueUserID(), pPerson->SIN, UpdatedUser))
	{
		UpdatedUser->person = nullptr;

		UpdatedUser->person = pPerson;

		errorString = "User ID : " + std::to_string(pPerson->getSnotifyUniqueUserID()) + " Updated user!";

		return true;
	}

	errorString = "User ID : " + std::to_string(pPerson->getSnotifyUniqueUserID()) + " not found with SIN - " + std::to_string(pPerson->SIN);

	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	
	SnotifyUser* snotifyUser = nullptr;

	if (GetUserWithSnotifyId(SnotifyUserID, snotifyUser))
	{
		ListOfSnotifyUsers.DeleteAtCurrent();

		errorString = "Deleted  User ID : " + std::to_string(SnotifyUserID);

		return true;
	}

	errorString = "Cannot find User ID : " + std::to_string(SnotifyUserID) + " to delete";

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{

	ListOfSongs.InsertBeforeCurrent(pSong);

	errorString = "Successfully added song " + pSong->name + "to snotify";

	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cSong* updatedSong = nullptr;
	if (GetSongWithId(pSong->getUniqueID(), updatedSong))
	{
		updatedSong = pSong;

		errorString = " updated song , Song id :" + std::to_string(pSong->getUniqueID());

		return true;
	}
	
	errorString = "Song not found to update , Song ID - "  + pSong->getUniqueID();
	 
	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{

	cSong* deleteSong = nullptr;

	if (GetSongWithId(UniqueSongID, deleteSong))
	{
		ListOfSongs.DeleteAtCurrent();

		errorString = " deleted song , Song id :" + std::to_string(UniqueSongID);

		return true;
	}

	errorString = "Song not found to delete, Song ID - " + UniqueSongID;

	return false;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(snotifyUserID, user))
	{
		if (user)
		{
			cSong* SongInSnotify = FindSong(pNewSong->getUniqueID());


			if (SongInSnotify!=nullptr)
			{
				if (user->FindSong(pNewSong->getUniqueID()) == nullptr)
				{
					user->AddSong(pNewSong);

					errorString = " Added song : " + pNewSong->name + ", to User id : " + std::to_string(snotifyUserID);

					return true;
				}
				else
				{
					errorString = "Song existed in user library!,  Cannot add song : " + pNewSong->name;

					return true;
				}
			}
			else
			{
				///  If the song is deleted from the snotify but its in the user library, removeing that element
				if (user->IsSongAvailableInSnotify(pNewSong->getUniqueID()))
				{
					 int removeIndex = 0;
					if (user->FindSongByIndex(pNewSong->getUniqueID(), removeIndex))
					{
						user->listOfSongs.RemoveAt(removeIndex);

						errorString = "Deleted song from library!,  Cannot add song : " + pNewSong->name + "\n";
						return false;

					}
				}

				errorString = "Song Not found in snotify!,  Cannot add song : " + pNewSong->name;
				return false;
			}
			
			
		}
		else
		{
			errorString = "User id :" + std::to_string( snotifyUserID) + " Not found to add song";

			return false;
		}
	}

	return false;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	SnotifyUser* user = nullptr;
	if (GetUserWithSnotifyId(snotifyUserID, user))
	{
		if (user)
		{
		
			cSong* foundSong = user->FindSong(SnotifySongID);

			if (foundSong)
			{ 
				user->listOfSongs.Remove(foundSong);    ///removing by value

				errorString = "Song Removed from library in User id : " + std::to_string(snotifyUserID);
				return true;
			}
			else
			{
				errorString = "Song Not found from library in User id : " + std::to_string(snotifyUserID);
				return false;
			}

		}
	}

	errorString = "Song cannot be found to remove from library in the User id : " + std::to_string(snotifyUserID);

	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	SnotifyUser* user = nullptr;
	if (GetUserWithSnotifyId(SnotifyUserID, user))
	{
		if (user)
		{
		
			cSong* foundSong = user->FindSong(songUniqueID);

			if (foundSong)
			{
				foundSong->rating = newRating;

				return true;
			}

		}
	}

	return false;
}


bool cSnotify::GetUserWithSnotifyId(unsigned int snotifyId, SnotifyUser*& snotifyUser)
{

	if (ListOfSnotifyUsers.IsEmpty())
	{

		return false;
	}

	ListOfSnotifyUsers.MoveToFirst();

	SnotifyUser* findUser = nullptr;

	do
	{
		findUser = ListOfSnotifyUsers.GetCurrentNode()->data;

		if (findUser->person->getSnotifyUniqueUserID() == snotifyId)
		{
			snotifyUser = findUser;
			return true;
		}
		/*else
		{*/
			ListOfSnotifyUsers.MoveNext();

			//findUser = ListOfSnotifyUsers.GetCurrentNode()->data;

		/*}*/
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

	SnotifyUser* findUserWithSIN = nullptr;

	do
	{
		findUserWithSIN = ListOfSnotifyUsers.GetCurrentNode()->data;

		if (findUserWithSIN->person->getSnotifyUniqueUserID() == snotifyId && findUserWithSIN->person->SIN == SIN )
		{

			//std::cout << "User found" << std::endl;
			snotifyUser = findUserWithSIN;
			return true;
		}

			ListOfSnotifyUsers.MoveNext();


	} while (ListOfSnotifyUsers.GetCurrentNode());


	//std::cout << "User Not found" << std::endl;
	return false;
}

bool cSnotify::GetSongWithId(unsigned int songId, cSong*& song)
{



	if (ListOfSongs.IsEmpty())
	{

		return false;
	}

	ListOfSongs.MoveToFirst();

	cSong* findSong = nullptr;

	do
	{
		findSong = ListOfSongs.GetCurrentNode()->data;

		if (findSong->getUniqueID() == songId)
		{

			//std::cout << "Found Song" << std::endl;
			song = findSong;
			return true;
		}
		//else
		//{
			ListOfSongs.MoveNext();

		//	findSong = ListOfSongs.GetCurrentNode()->data;

		//}
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





cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(SnotifyUserID,user))
	{
		cSong* findSong = user->FindSong(songUniqueID);

		if (findSong)
		{
			findSong->numberOfTimesPlayed++;  // updating Number of times played
			errorString = "Successfuly got the song : " + findSong->name;
			return findSong;
		}
		
	}

	errorString = "Song cannot be found in User id :" + SnotifyUserID;

	return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(snotifyUserID,user))
	{
		cSong* findsong = user->FindSong(songUniqueID);

		if (findsong)
		{
			songRating = findsong->rating;

			return true;
		}
	}

	return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(snotifyUserID, user))
	{
		cSong* findsong = user->FindSong(songUniqueID);

		if (findsong)
		{
			numberOfPlays = findsong->numberOfTimesPlayed;

			return true;
		}
	}

	return false;
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

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(snotifyUserID, user))
	{
		sizeOfLibary = user->listOfSongs.GetLength();

		pLibraryArray = new cSong[sizeOfLibary];

		for (size_t i = 0; i < sizeOfLibary; i++)
		{
			pLibraryArray[i] = *(user->listOfSongs[i]);
		}

		return true;
	}

	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{

	/*SnotifyUser* user = nullptr;

	if (GetUserWithSnotifyId(snotifyUserID, user))
	{
		sizeOfLibary = user->listOfSongs.GetLength();

		pLibraryArray = new cSong[sizeOfLibary];

		for (size_t i = 0; i < sizeOfLibary; i++)
		{
			pLibraryArray[i] = *(user->listOfSongs[i]);
		}

		SORT::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, IsAscendingOrderBySongTitle);

		return true;
	}*/

	if (GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary))
	{
		SORT::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, IsAscendingOrderBySongTitle);
	}

	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	SnotifyUser* user = nullptr;

	//if (GetUserWithSnotifyId(snotifyUserID, user))
	//{
	//	sizeOfLibary = user->listOfSongs.GetLength();

	//	pLibraryArray = new cSong[sizeOfLibary];

	//	for (size_t i = 0; i < sizeOfLibary; i++)
	//	{
	//		pLibraryArray[i] = *(user->listOfSongs[i]);
	//	}

	//	SORT::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, IsAscendingOrderByArtist);

	//	return true;
	//}
	if (GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary))
	{
		SORT::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, IsAscendingOrderByArtist);
	}


	return false;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		pAllTheUsers = nullptr;

		sizeOfUserArray = 0;

		return false;
	}

	sizeOfUserArray  = ListOfSnotifyUsers.GetSize();

	pAllTheUsers = new cPerson[sizeOfUserArray];
		
	ListOfSnotifyUsers.MoveToFirst();

	for (size_t i = 0; i < sizeOfUserArray; i++)
	{
		
		pAllTheUsers[i] = *(ListOfSnotifyUsers.GetCurrentNode()->data->person);

		ListOfSnotifyUsers.MoveNext();
	}

	//pAllTheUsers = personsInList;
	//sizeOfUserArray = size;

	return true;
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{

	if (GetUsers(pAllTheUsers, sizeOfUserArray))
	{
	
		SORT::QuickSort<cPerson>(&pAllTheUsers[0], 0, sizeOfUserArray - 1, IsAscendingOrderUniqueID);
		//SORT::BubbleSort<cPerson>(&pAllTheUsers[0],  sizeOfUserArray - 1, IsAscendingOrderUniqueID);

		return true;
	}

	return false;
	
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		return false;
	}

	sizeOfUserArray = ListOfSnotifyUsers.GetSize();

	pAllTheUsers = new cPerson[sizeOfUserArray];

	unsigned int index = 0;
	unsigned int userFirstNameFound = 0;

	ListOfSnotifyUsers.MoveToFirst();

	

	do
	{
		SnotifyUser* findUser = ListOfSnotifyUsers.GetCurrentNode()->data;
		if (findUser->person->first == firstName)
		{
			pAllTheUsers[userFirstNameFound] = *findUser->person;

			userFirstNameFound++;
		}

		ListOfSnotifyUsers.MoveNext();

		index++; // not used

	} while (ListOfSnotifyUsers.GetCurrentNode());


	sizeOfUserArray = userFirstNameFound;

	if (userFirstNameFound>0)
	{
		SORT::QuickSort<cPerson>(&pAllTheUsers[0], 0, sizeOfUserArray - 1, IsAscendingbyFirstname);
		return true;
	}
	else
	{
		std::cout << "Cant find user first name : " << firstName << std::endl;
		return false;
	}



	return false;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		return false;
	}

	sizeOfUserArray = ListOfSnotifyUsers.GetSize();

	pAllTheUsers = new cPerson[sizeOfUserArray];

	unsigned int index = 0;
	unsigned int userLastNameFound = 0;

	ListOfSnotifyUsers.MoveToFirst();



	do
	{
		SnotifyUser* findUser = ListOfSnotifyUsers.GetCurrentNode()->data;
		if (findUser->person->last == lastName)
		{
			pAllTheUsers[userLastNameFound] = *findUser->person;

			userLastNameFound++;
		}

		ListOfSnotifyUsers.MoveNext();

		index++; // not used

	} while (ListOfSnotifyUsers.GetCurrentNode());


	sizeOfUserArray = userLastNameFound;

	if (userLastNameFound > 0)
	{
		SORT::QuickSort<cPerson>(&pAllTheUsers[0], 0, sizeOfUserArray - 1, IsAscendingbyLastname);
		return true;
	}
	else
	{
		std::cout << "Cant find user last name : " << lastName << std::endl;
		return false;
	}

	

	return false;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (ListOfSnotifyUsers.IsEmpty())
	{
		return false;
	}

	sizeOfUserArray = ListOfSnotifyUsers.GetSize();

	pAllTheUsers = new cPerson[sizeOfUserArray];

	unsigned int index = 0;
	unsigned int userLastAndFirstNameFound = 0;

	ListOfSnotifyUsers.MoveToFirst();



	do
	{
		SnotifyUser* findUser = ListOfSnotifyUsers.GetCurrentNode()->data;
		if (findUser->person->first == firstName && findUser->person->first == lastName)
		{
			pAllTheUsers[userLastAndFirstNameFound] = *findUser->person;

			userLastAndFirstNameFound++;
		}

		ListOfSnotifyUsers.MoveNext();

		index++; // not used

	} while (ListOfSnotifyUsers.GetCurrentNode());


	sizeOfUserArray = userLastAndFirstNameFound;

	if (userLastAndFirstNameFound > 0)
	{
		SORT::QuickSort<cPerson>(&pAllTheUsers[0], 0, sizeOfUserArray - 1, IsAscendingbyFirstAndLastname);
		return true;
	}
	else
	{
		std::cout << "Cant find user first name : " << firstName << " Last name : " << lastName << std::endl;
		return false;
	}



	return false;
}
