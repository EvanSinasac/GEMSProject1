#include "cSmartArray_Template.h"
#include "cSong.h"
#include "cPerson.h"


// This is mostly for the Music Generator so I might just move it in there, nevermind, using it in Snotify
// https://www.geeksforgeeks.org/binary-search/

int BinarySearch_SongByID(cSmartArray_Template<cSong*> songs, int left, int right, unsigned int ID)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (songs.getAtIndex(mid)->getUniqueID() == ID)
			return mid;

		// If the element is smaller than mid, then it can only be present in left subarray
		if (songs.getAtIndex(mid)->getUniqueID() > ID)
		{
			return BinarySearch_SongByID(songs, left, mid - 1, ID);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_SongByID(songs, mid + 1, right, ID);
	}

	// We reach here when the element is not present in array
	return -1;
}

int BinarySearch_SongByName(cSmartArray_Template<cSong*> songs, int left, int right, std::string NAME)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (songs.getAtIndex(mid)->name.compare(NAME) == 0)
			return mid;

		// If the element is smaller than mid, then it can only be present in left subarray
		if (songs.getAtIndex(mid)->name.compare(NAME) > 0)	// might need to switch this to >
		{
			return BinarySearch_SongByName(songs, left, mid - 1, NAME);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_SongByName(songs, mid + 1, right, NAME);
	}

	// We reach here when the element is not present in array
	return -1;
}

int BinarySearch_SongByNameANDArtist(cSmartArray_Template<cSong*> songs, int left, int right, std::string NAME, std::string ARTIST)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (songs.getAtIndex(mid)->name.compare(NAME) == 0)
		{
			// Have to check artist name as well
			if (songs.getAtIndex(mid)->artist.compare(ARTIST) == 0)
				return mid;
			//otherwise keep searching
		}

		// If the element is smaller than mid, then it can only be present in left subarray
		if (songs.getAtIndex(mid)->name.compare(NAME) > 0)	// might need to switch this to >
		{
			return BinarySearch_SongByName(songs, left, mid - 1, NAME);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_SongByName(songs, mid + 1, right, NAME);
	}

	// We reach here when the element is not present in array
	return -1;
}


// *******************************************************************************************************************

int BinarySearch_UserBySIN(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int SIN)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (people.getAtIndex(mid)->SIN == SIN)
			return mid;

		// If the element is smaller than mid, then it can only be present in left subarray
		if (people.getAtIndex(mid)->SIN > SIN)
		{
			return BinarySearch_UserBySIN(people, left, mid - 1, SIN);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_UserBySIN(people, mid + 1, right, SIN);
	}

	// We reach here when the element is not present in array
	return -1;
}

int BinarySearch_UserBySnotifyID(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int ID)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (people.getAtIndex(mid)->getSnotifyUniqueUserID() == ID)
			return mid;

		// If the element is smaller than mid, then it can only be present in left subarray
		if (people.getAtIndex(mid)->getSnotifyUniqueUserID() > ID)
		{
			return BinarySearch_UserBySnotifyID(people, left, mid - 1, ID);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_UserBySnotifyID(people, mid + 1, right, ID);
	}

	// We reach here when the element is not present in array
	return -1;
}

int BinarySearch_UserBySnotifyIDANDSIN(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int ID, unsigned int SIN)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		// If the element is present at the middle
		if (people.getAtIndex(mid)->getSnotifyUniqueUserID() == ID && people.getAtIndex(mid)->SIN == SIN)
			return mid;

		// If the element is smaller than mid, then it can only be present in left subarray
		// This is for the update user, so it will be sorted by snotify ID
		if (people.getAtIndex(mid)->getSnotifyUniqueUserID() > ID)
		{
			return BinarySearch_UserBySnotifyIDANDSIN(people, left, mid - 1, ID, SIN);
		}

		// Else the element can only be present in the right subarray
		return BinarySearch_UserBySnotifyIDANDSIN(people, mid + 1, right, ID, SIN);
	}

	// We reach here when the element is not present in array
	return -1;
}