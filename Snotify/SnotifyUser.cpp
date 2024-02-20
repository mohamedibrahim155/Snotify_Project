#include "SnotifyUser.h"

void SnotifyUser::AddSong(cSong* song)
{
	listOfSongs.Add(song);
}

bool SnotifyUser::FindSongByIndex(unsigned int songID, int& outIndex)
{
	
	for (size_t i = 0; i < listOfSongs.GetLength(); i++)
	{
		if (listOfSongs[i]->getUniqueID() == songID)
		{
			outIndex = i;
			return true;
		}
	}

	return false;
}

cSong* SnotifyUser::FindSong(unsigned int songID)
{
	for (size_t i = 0; i < listOfSongs.GetLength(); i++)
	{
		if (listOfSongs[i]->getUniqueID() == songID)
		{
			
			return listOfSongs[i];
		}
	}

	return nullptr;
}
