#pragma once

#include "../Utils/List.h"
#include "../Snotify/cPerson.h"
#include "../Snotify/cSong.h"
using namespace RIO_UTILS;


class SnotifyUser
{
public:
	SnotifyUser() = default;
	//~SnotifyUser();

	cPerson* person = nullptr;
	List<cSong*> listOfSongs;

private:

};

