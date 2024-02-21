#pragma once

#include "../Utils/List.h"
#include "../Snotify/cPerson.h"
#include "../Snotify/cSong.h"
using namespace CONTAINERS;


class SnotifyUser
{
public:
	SnotifyUser() = default;
	//~SnotifyUser();

	 void AddSong(cSong* song);
	 bool FindSongByIndex(unsigned int songID, int& outIndex);
	 cSong* FindSong(unsigned int songID);
	 bool IsSongAvailableInSnotify(cSong* songfromSnotify);
	 bool IsSongAvailableInSnotify(unsigned int songId);

	cPerson* person = nullptr;
	List<cSong*> listOfSongs;

private:

};

