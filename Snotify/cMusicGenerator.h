#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cSong.h"
#include "../Utils/List.h"
using namespace RIO_UTILS;
class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);
	List<cSong*> ListOfSongs;
	List<unsigned int> ListOfGeneratedHash;

	void BubbleSortSongList();
private:

	bool LoadMusicFile(std::string musicFileName);
	void AddSong(std::string& songName, std::string artistName);
	unsigned int CreateSongHash(std::string& songName, std::string& artistName);

	unsigned int CustomHash(const std::string& input);
	int GetRandomNumber(int min, int max);

	bool IsHashAlreadyGenerated(unsigned int songHash);

	bool IsUniqueValueGreater(const cSong* valueA, const cSong* valueB);

	unsigned int SongID = 10;

	void QuickSortSongList(int low, int high);

	int Partition(int low, int high);

	void Swap(cSong*& a, cSong*& b);
};

#endif
