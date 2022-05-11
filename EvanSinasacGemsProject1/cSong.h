#ifndef _cSong_HG_
#define _cSong_HG_

#include <string>

// This represents a song in the Snotify class

class cSong
{
public:
	cSong();
	~cSong();
	//{
	//	this->rating = 0;
	//	this->numberOfTimesPlayed = 0;

	//	// Generate unique Song DI
	//	this->uniqueID = cSong::m_NEXT_uniueID;
	//	// Increment for next created song by a small random amount 
	//	const unsigned int MAX_ID_INCREEMNT = 11;
	//	cSong::m_NEXT_uniueID += (rand() % MAX_ID_INCREEMNT);
	//}
	std::string name;
	std::string artist;
	// These are used for user play statistics
	int rating;					// rating, by the user, from 0 to 5 (5 is best)
	int numberOfTimesPlayed;	// number of times the user has listened to this song

	// You can implement this any way you'd like, but I will be using 
	//	this method rather than the public variable. 
	// The cPerson has a common method for generating unique IDs, if you 
	//	want to use that. 
	unsigned int getUniqueID(void);// { return this->uniqueID; }

private:
	unsigned int uniqueID;
	static unsigned int m_NEXT_uniqueID;
}; 


#endif

