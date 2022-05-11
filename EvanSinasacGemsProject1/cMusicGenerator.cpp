#include "cMusicGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

//void MergeSort_MergeSongByName(cSmartArray_Template<cSong*> songs, int const left, int const mid, int const right);
void MergeSort_SongByName(cSmartArray_Template<cSong*> songs, int const begin, int const end);
//void MergeSort_SongByID(cSmartArray_Template<cSong*> songs, int const begin, int const end);

//void SelectionSort_SongsByName(cSmartArray_Template<cSong*> songs, int n);

//void HeapSort_SongsByName(cSmartArray_Template<cSong*> songs, int n);

void InsertionSort_SongsByName(cSmartArray_Template<cSong*> songs, int n);

//int BinarySearch_SongByID(cSmartArray_Template<cSong*> songs, int left, int right, unsigned int ID);
//int BinarySearch_SongByName(cSmartArray_Template<cSong*> songs, int left, int right, std::string NAME);
int BinarySearch_SongByNameANDArtist(cSmartArray_Template<cSong*> songs, int left, int right, std::string NAME, std::string ARTIST);

// TODO:

cMusicGenerator::cMusicGenerator()
{

}
cMusicGenerator::~cMusicGenerator()
{

}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	std::ifstream songFile(musicFileName);
	if (!songFile.is_open())
	{
		errorString = "Didn't open music file!";
		std::cout << errorString << std::endl;	// probably remove this since we do the errorString
		return false;
	}

	// url,weekid,week_position,song,performer,songid,instance,previous_week_position,peak_position,weeks_on_chart
	// We only need song and performer, 4 and 5, but there are a number of identical records since songs are often in the top 100 for more than 1 week
	// We will need to handle this by either loading duplicates or checking to see if the song has already been loaded
	// one makes the list of songs larger (and by proxy harder to sort and search through)
	// while the other will make it take longer to load the file
	// ...
	// yeah, I'll check for duplicates as we go, save space and keep it easier to sort/search later

	std::string theLine;

	unsigned int lineCount = 0;

	// there are way to many, it takes almost 10 minutes for my computer to load them all
	// for testing purposes, restricting this to 10,000 lines (there's 320,496 total lines)
	// this should theoretically work for any size given enough time, 10'000 is just how long I have patience for
	//while (std::getline(songFile, theLine) && lineCount < 10'000)
	//while (std::getline(songFile, theLine) && lineCount < 1'000)
	while (std::getline(songFile, theLine))
	{
		cSong* tempSong = new cSong();
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 3)	// song name
			{
				tempSong->name = token;
			}
			if (tokenCount == 4)
			{
				tempSong->artist = token;
			}
			// ignore everything else
			tokenCount++;
		}

		// So doing this causes my PC to crash at about 5'000 entries...
		//MergeSort_SongByName(this->saAllSongs, 0, this->saAllSongs.getSize() - 1);
		// So let's try something a little more memory friendly... but this makes it take too long
		//SelectionSort_SongsByName(this->saAllSongs, this->saAllSongs.getSize() - 1);
		// still takes too long
		//HeapSort_SongsByName(this->saAllSongs, this->saAllSongs.getSize() - 1);
		// best case on a sorted list is O(n) time, so anything larger than 10'000 for any of the in place sorts take too long
		// Insertion is still the best of them all tho
		//InsertionSort_SongsByName(this->saAllSongs, this->saAllSongs.getSize());
		//// This is good if we find it, but towards the end the list gets too large and starts causing my PC to crash
		//if (BinarySearch_SongByNameANDArtist(this->saAllSongs, 0, this->saAllSongs.getSize() - 1, tempSong->name, tempSong->artist) < 0)	// can't check by ID since a new ID is made with every tempSong
		//{
		//	// Binary search didn't find the song so we can add it
		//	this->saAllSongs.insertAtEnd(tempSong);
		//	//std::cout << "Adding " << tempSong->name << " by " << tempSong->artist << std::endl;
		//}
		
		// This linear stuff when using the entire list takes 10 minutes to load the file
		// before adding the song to the list of songs, check if it's already in it
		 // hmm, going through the list every time makes this takes almost 10 minutes, which is unacceptable
		//unsigned int index;
		//for (index = 0; index != this->saAllSongs.getSize(); index++)
		//{
		//	if (tempSong->name == this->saAllSongs.getAtIndex(index)->name
		//		&& tempSong->artist == this->saAllSongs.getAtIndex(index)->artist)
		//	{
		//		// For some reason if I don't have anything in here then the program freezes when it exits the while loop
		//		// I was freezing it by clicking on the console...
		//		//std::cout << "Found song: " << tempSong->name << " by " << tempSong->artist << std::endl;
		//		break;
		//	}
		//}
		//if (index == this->saAllSongs.getSize())	// if index != the size, then we found the song
		//{
			saAllSongs.insertAtEnd(tempSong);
		//}
	}

	std::cout << "Song Data Lines read = " << lineCount << std::endl;

	// and doing this causes a read access violation eventually
	//for (unsigned int indexA = 0; indexA != saAllSongs.getSize() - 1; indexA++)
	//{
	//	for (unsigned int indexB = indexA + 1; indexB != saAllSongs.getSize(); indexB++)
	//	{
	//		if (saAllSongs.getAtIndex(indexA)->name == saAllSongs.getAtIndex(indexB)->name
	//			&& saAllSongs.getAtIndex(indexA)->artist == saAllSongs.getAtIndex(indexB)->artist)
	//		{
	//			saAllSongs.removeAtIndex(indexB);
	//			indexB--;
	//		}
	//	}
	//}

	// new idea, read the entire file of songs, THEN go through and remove any duplicates
	MergeSort_SongByName(this->saAllSongs, 0, this->saAllSongs.getSize() - 1);
	for (unsigned int index = 0; index != saAllSongs.getSize() - 1; index++)
	{
		if (saAllSongs.getAtIndex(index)->name.compare(saAllSongs.getAtIndex(index + 1)->name) == 0
			&& saAllSongs.getAtIndex(index)->artist.compare(saAllSongs.getAtIndex(index + 1)->artist) == 0)
		{
			saAllSongs.removeAtIndex(index);
			index--;
		}
	}

	std::cout << "saAllSongs size: " << this->saAllSongs.getSize() << std::endl;

	songFile.close();

	// was using this to test, shouldn't need it since I'm Insertion sorting as we go
	//MergeSort_SongByName(this->saAllSongs, 0, this->saAllSongs.getSize() -1);

	return true;
}



cSong* cMusicGenerator::getRandomSong(void)
{
	unsigned int index = rand() % this->saAllSongs.getSize();
	return this->saAllSongs.getAtIndex(index);
}

// Returns 0, NULL, or nullptr if no song is found
// This must be an EXACT MATCH for what's in the billboard100 file. 
// So case sensitive, etc. 
cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	//cSong* tempSong = nullptr;
	// If the list is sorted by a different way Merge is better than Insertion
	MergeSort_SongByName(this->saAllSongs, 0, this->saAllSongs.getSize() - 1);
	// Insertion is only better than Merge if the list is already sorted by Name
	//InsertionSort_SongsByName(this->saAllSongs, this->saAllSongs.getSize());
	// tested to make sure Insertion also sorts by ascending order
	int loc = BinarySearch_SongByNameANDArtist(this->saAllSongs, 0, this->saAllSongs.getSize() - 1, songName, artist);
	if ( loc >= 0)
	{
		return this->saAllSongs.getAtIndex(loc);
	}
	return nullptr;

	//unsigned int index;
	//for (index = 0; index != this->saAllSongs.getSize(); index++)
	//{
	//	if (songName == this->saAllSongs.getAtIndex(index)->name
	//		&& artist == this->saAllSongs.getAtIndex(index)->artist)
	//	{
	//		tempSong = saAllSongs.getAtIndex(index);
	//		break;
	//	}
	//}
	//if (index == this->saAllSongs.getSize())	// if index != the size, then we found the song
	//{
	//	return nullptr;
	//}
	//return tempSong;
}