#include "cSong.h"

cSong::cSong()
{
	this->rating = 0;
	this->numberOfTimesPlayed = 0;

	// Generate unique Song ID
	this->uniqueID = cSong::m_NEXT_uniqueID;
	// Increment for next created song by a small random amount 
	const unsigned int MAX_ID_INCREMENT = 11;
	cSong::m_NEXT_uniqueID += (rand() % MAX_ID_INCREMENT) + 1;
}


unsigned int cSong::m_NEXT_uniqueID = 10000000;

cSong::~cSong() {}

unsigned int cSong::getUniqueID(void)
{ 
	return this->uniqueID; 
}