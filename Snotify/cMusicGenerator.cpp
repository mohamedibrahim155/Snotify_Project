#include "cMusicGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include <random>
cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{
}

bool cMusicGenerator::IsUniqueValueGreater(const cSong* valueA, const cSong* valueB)
{
	return valueA->uniqueID > valueB->uniqueID;
}




bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	if (LoadMusicFile(musicFileName))
	{
		//BubbleSortSongList();

		
		return true;
	}
	return false ;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	int randomIndex = GetRandomNumber(0, ListOfSongs.GetLength());

	return ListOfSongs.GetAt(randomIndex);
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	unsigned int hashvalue = CreateSongHash(songName, artist);

	try
	{
		for (int i = 0; i < ListOfSongs.GetLength(); i++)
		{
			if (ListOfSongs[i]->uniqueID == hashvalue)
			{
				std::cout << "Found song index = " << i << std::endl;
				return ListOfSongs[i];
			}
		}
		std::cerr << "Song not found - " << songName << " by " << artist << std::endl;
		return nullptr;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: Song not found - " << songName << " by " << artist << std::endl;
	}
	
}

bool cMusicGenerator::LoadMusicFile(std::string musicFileName)
{

	std::ifstream file(musicFileName);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << musicFileName << std::endl;
		return false;
	}


	std::string line;
	int lineCount = 0;

	while (std::getline(file, line))
	{
		//if (lincount > 50) break;
		std::istringstream iss(line);
		lineCount++;

		if (lineCount == 1)
		{
			continue;
		}

		std::string songName;
		std::string artist;
		std::string token;
		unsigned int tokenCount = 0;

		while (std::getline(iss, token, ','))
		{
			
			if (tokenCount == 3)
			{
				songName = token;
			}
			else if (tokenCount == 4)
			{
				artist = token;
				break;
			}

			tokenCount++;
		}
		AddSong(songName, artist);
	}
}

void cMusicGenerator::AddSong(std::string& songName, std::string artistName)
{
	cSong* newSong = new cSong();

	newSong->name = songName;
	newSong->artist = artistName;

	int hashID = CreateSongHash(songName, artistName);
//	newSong->uniqueID = CreateSongHash(songName, artistName);
	newSong->uniqueID = hashID;

	if (!IsHashAlreadyGenerated(hashID))
	{
		SongID++;
		//newSong->uniqueID = SongID;
		ListOfGeneratedHash.Add(hashID);
		ListOfSongs.Add(newSong);

		
	}


}

unsigned int cMusicGenerator::CreateSongHash(std::string& songName, std::string &artistName)
{
	unsigned int songHash = 0;

	std::string combinedValue = songName + artistName;

	songHash = CustomHash(combinedValue);



	return songHash;
}

unsigned int cMusicGenerator::CustomHash(const std::string& input)
{
	unsigned int  hash = 0;

	for (char c : input) 
	{
		hash = hash * 31 + static_cast<unsigned char>(c);
	}

	return hash;
}

int cMusicGenerator::GetRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);
}

bool cMusicGenerator::IsHashAlreadyGenerated(unsigned int songHash)
{
	if (ListOfGeneratedHash.IsEmpty())
	{
		return false;
	}
	for (size_t i = 0; i < ListOfGeneratedHash.GetLength(); i++)
	{
		if (ListOfGeneratedHash[i] == songHash)
		{
			return true;
		}
	}
	return false;
}

