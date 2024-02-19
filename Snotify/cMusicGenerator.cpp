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

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	return LoadMusicFile(musicFileName);
}

cSong* cMusicGenerator::getRandomSong(void)
{
	int randomIndex = GetRandomNumber(0, ListOfSongs.GetLength());

	return ListOfSongs.GetAt(randomIndex);
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
	int lincount = 0;

	while (std::getline(file, line))
	{
		//if (lincount > 50) break;
		std::istringstream iss(line);
		lincount++;

		if (lincount == 1)
		{
			continue;
		}

		std::string songName;
		std::string artist;
		std::string token;
		unsigned int tokenCount = 0;

		while (std::getline(iss, token, ','))
		{
			if (tokenCount == 0)
			{
				//	data.fullStreetName = token;
			}
			else if (tokenCount == 1)
			{
				//	data.streetName = token;
			}
			else if (tokenCount == 2)
			{
				//	data.streetType = token;

			}
			else if (tokenCount == 3)
			{
				songName = token;
			}
			else if (tokenCount == 4)
			{
				artist = token;
			}
			else if (tokenCount > 4)
			{
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
	newSong->uniqueID = CreateSongHash(songName, artistName);

	ListOfSongs.Add(newSong);
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
