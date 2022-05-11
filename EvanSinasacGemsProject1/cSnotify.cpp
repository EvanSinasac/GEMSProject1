#include "cSnotify.h"
#include <iostream>

cSnotify::cSnotify() {}
cSnotify::~cSnotify() {}

void MergeSort_SongByName(cSmartArray_Template<cSong*> songs, int const begin, int const end);
void MergeSort_SongByArtist(cSmartArray_Template<cSong*> songs, int const begin, int const end);
void MergeSort_SongByID(cSmartArray_Template<cSong*> songs, int const begin, int const end);
void InsertionSort_SongsByName(cSmartArray_Template<cSong*> songs, int n);
int BinarySearch_SongByID(cSmartArray_Template<cSong*> songs, int left, int right, unsigned int ID); 
int BinarySearch_SongByNameANDArtist(cSmartArray_Template<cSong*> songs, int left, int right, std::string NAME, std::string ARTIST);


void MergeSort_UsersBySnotifyID(cSmartArray_Template<cPerson*> people, int const begin, int const end);
void MergeSort_UsersBySIN(cSmartArray_Template<cPerson*> people, int const begin, int const end);
void InsertionSort_UsersBySnotifyID(cSmartArray_Template<cPerson*> people, int n);
int BinarySearch_UserBySIN(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int SIN);
int BinarySearch_UserBySnotifyID(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int ID);
int BinarySearch_UserBySnotifyIDANDSIN(cSmartArray_Template<cPerson*> people, int left, int right, unsigned int ID, unsigned int SIN);

void MergeSort_UsersByFirstName(cSmartArray_Template<cPerson*> people, int const begin, int const end);
void MergeSort_UsersByLastName(cSmartArray_Template<cPerson*> people, int const begin, int const end);
void MergeSort_UsersByLastThenFirstName(cSmartArray_Template<cPerson*> people, int const begin, int const end);

// All these return true if they work, false if not (for any reason)
// 
// You can add some error information to the by referenece error string, if you want. 
bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	cPerson* tempPerson = FindUserBySnotifyID(pPerson->getSnotifyUniqueUserID());
	if (tempPerson == nullptr)
	{
		this->m_saUsers.insertAtEnd(pPerson);
		InsertionSort_UsersBySnotifyID(this->m_saUsers, this->m_saUsers.getSize());
		return true;
	}

	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (pPerson->getSnotifyUniqueUserID() == this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID())
	//	{
	//		// we found the user on the array so we're not adding it
	//		errorString = "User already exists, not adding";
	//		return false;
	//	}
	//}

	//this->m_saUsers.insertAtEnd(pPerson);
	//this->m_mUserSongs.insertAtIndex(*(pPerson), new cSong());
	errorString = "User already exists, not adding";
	return false;
}
// This will overwrite the data contained in user 
// NOTE: It "finds" the user by matching BOTH the "unique Snofity ID" AND the "SIN" 
//        (Social Insurance Number)
// So if either of these don't match (or aren't found) then it reutrns false. 
bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	if (this->m_saUsers.getSize() > 0)
	{
		MergeSort_UsersBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
		int index = BinarySearch_UserBySnotifyIDANDSIN(this->m_saUsers, 0, this->m_saUsers.getSize() - 1, pPerson->getSnotifyUniqueUserID(), pPerson->SIN);
		if (index < 0)
		{
			errorString = "No matching user to update.";
			return false;
		}
		else
		{
			this->m_saUsers.setAtIndex(index, pPerson);
			return true;
		}
	}
	
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID()
	//		&& this->m_saUsers.getAtIndex(index)->SIN == pPerson->SIN)
	//	{
	//		// matched the user by Unique ID and SIN so we can update them by replacing the information with the new pointer
	//		this->m_saUsers.setAtIndex(index, pPerson);
	//		return true;
	//	}
	//}
	//errorString = "No matching user to update.";
	return false;
}
bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	if (this->m_saUsers.getSize() > 0)
	{
		MergeSort_UsersBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
		int index = BinarySearch_UserBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1, SnotifyUserID);
		if (index < 0)
		{
			errorString = "No matching user to delete.";
			return false;
		}
		else
		{
			this->m_saUsers.removeAtIndex(index);
			return true;
		}
	}
	

	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == SnotifyUserID)
	//	{
	//		// found the user so we can remove them (which handles fixing the rest of the array) and return
	//		this->m_saUsers.removeAtIndex(index);
	//		return true;
	//	}
	//}
	//errorString = "No matching user to delete.";
	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	cSong* tempSong = FindSong(pSong->getUniqueID());
	if (tempSong == nullptr)
	{
		this->m_saSongs.insertAtEnd(pSong);
		InsertionSort_SongsByName(this->m_saSongs, this->m_saSongs.getSize());
		return true;
	}

	errorString = "Song already exists, not adding";
	return false;

	//for (unsigned int index = 0; index != this->m_saSongs.getSize(); index++)
	//{
	//	if (pSong->getUniqueID() == this->m_saSongs.getAtIndex(index)->getUniqueID())
	//	{
	//		// found the song in the program already, don't need to add it
	//		errorString = "Song already exists, not adding";
	//		return false;
	//	}
	//}

	//this->m_saSongs.insertAtEnd(pSong);
	//return true;
}
// This finds a match, based on the "unique ID", and overwrites the data. 
bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	if (this->m_saSongs.getSize() > 0)
	{
		// this is assuming we're calling it after at least one song has been added
		MergeSort_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1);
		int index = BinarySearch_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1, pSong->getUniqueID());
		if (index < 0)
		{
			errorString = "Could not find song to update.";
			return false;
		}
		else
		{
			// found the song so we can update it
			this->m_saSongs.setAtIndex(index, pSong);
			return true;
		}
	}
	

	//cSong* tempSong = FindSong(pSong->getUniqueID());
	//if (tempSong != nullptr)
	//{
	//	// found the song so we can update it
	//	//this->m_saSongs.setAtIndex(index, pSong);
	//	tempSong = pSong;
	//	return true;
	//}
	//errorString = "Could not find song to update.";
	//return false;

	//for (unsigned int index = 0; index != this->m_saSongs.getSize(); index++)
	//{
	//	if (this->m_saSongs.getAtIndex(index)->getUniqueID() == pSong->getUniqueID())
	//	{
	//		// find the song and update the information
	//		this->m_saSongs.setAtIndex(index, pSong);
	//		return true;
	//	}
	//}
	//errorString = "Could not find song to update.";
	return false;
}
// ************************************************************************
// NOTE: Deleting the song deletes it from ALL users that have this song!!!
// ************************************************************************
bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	// Don't need to sort the users since we have to go through all of them
	for (unsigned int indexA = 0; indexA != this->m_saUsers.getSize(); indexA++)
	{
		// but we can binary search each user's playlist instead of doing this linearly
		MergeSort_SongByID(this->m_saUsers.getAtIndex(indexA)->saMyPlayList, 0, this->m_saUsers.getAtIndex(indexA)->saMyPlayList.getSize() - 1);
		int index = BinarySearch_SongByID(this->m_saUsers.getAtIndex(indexA)->saMyPlayList, 0, this->m_saUsers.getAtIndex(indexA)->saMyPlayList.getSize() - 1, UniqueSongID);
		if (index >= 0)
		{
			// this is wholly unneccessary but this is checking that we did find the song in the user's playlist
			// really should just do >= ...
			// yeah, let's do that
			//std::cout << "removing at index: " << index << std::endl;
			this->m_saUsers.getAtIndex(indexA)->saMyPlayList.removeAtIndex(index);
		}
		else
		{
			errorString = "not on this user";
		}
		// if index < 0 then this user doesn't have the song

		//for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(indexA)->saMyPlayList.getSize(); indexB++)
		//{
		//	if (this->m_saUsers.getAtIndex(indexA)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == UniqueSongID)
		//	{
		//		// find each user who has the song on their playlist and remove it from their playlist
		//		this->m_saUsers.getAtIndex(indexA)->saMyPlayList.removeAtIndex(indexB);
		//		//should be fine to break out of this for loop now since removing it moves everything else in the array up
		//		// and there should never be duplicates in the playlist
		//		break;
		//	}
		//}
	}
	// After removing it from all users we can remove it from the snotify list, actually I should do this first, maybe possibly
	MergeSort_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1);
	int indexB = BinarySearch_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1, UniqueSongID);
	if (indexB < 0)
	{
		errorString = "Unable to find song to remove, reached the end of the function";
		return false;
	}
	else
	{
		this->m_saSongs.removeAtIndex(indexB);
		return true;
	}

	//for (unsigned int index = 0; index != this->m_saSongs.getSize(); index++)
	//{
	//	if (this->m_saSongs.getAtIndex(index)->getUniqueID() == UniqueSongID)
	//	{
	//		// then remove it from the snotify program
	//		this->m_saSongs.removeAtIndex(index);
	//		return true;
	//	}
	//}
	//errorString = "Unable to find song to remove, reached the end of the function";
	//return false;
}

// This associates a particular song with a particular user. 
	// (returns true if the song is already there)
bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, pNewSong->getUniqueID());
			if (index < 0)
			{
				// not on user playlist, we can add
				tempPerson->saMyPlayList.insertAtEnd(pNewSong);
				MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
				return true;
			}
			else
			{
				// on the user playlist, so we're not adding it
				errorString = "Song already on user's playlist";
				return false;
			}
		}
		else
		{
			// playlist is empty, add the song
			tempPerson->saMyPlayList.insertAtEnd(pNewSong);
			return true;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == pNewSong->getUniqueID())
		//	{
		//		// song is on the user's playlist so we can't add it again
		//		errorString = "Song already on user's playlist";
		//		return false;
		//	}
		//}
		//tempPerson->saMyPlayList.insertAtEnd(pNewSong);
		//return true;
	}
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == snotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == pNewSong->getUniqueID())
	//			{
	//				// song is on the user's playlist so we can't add it again
	//				errorString = "Song already on user's playlist";
	//				return false;
	//			}
	//		}
	//		// add the song to the user
	//		this->m_saUsers.getAtIndex(index)->saMyPlayList.insertAtEnd(pNewSong);
	//		return true;
	//	}
	//}
	errorString = "Could not find the user";
	return false;
}
bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, SnotifySongID);
			if (index < 0)
			{
				// not on user playlist, we can't delete add
				errorString = "Unable to find song to remove from user.";
				return false;
			}
			else
			{
				// on the user playlist, so we're deleting
				tempPerson->saMyPlayList.removeAtIndex(index);
				return true;
			}
		}
		else
		{
			errorString = "User has no songs";
			return false;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == SnotifySongID)
		//	{
		//		tempPerson->saMyPlayList.removeAtIndex(index);
		//		return true;
		//	}
		//}
	}
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == snotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == SnotifySongID)
	//			{
	//				// found the song on the user and in their library so we can remove it
	//				this->m_saUsers.getAtIndex(index)->saMyPlayList.removeAtIndex(indexB);
	//				return true;
	//			}
	//		}
	//	}
	//}
	errorString = "Unable to find user to remove song from.";
	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	cPerson* tempPerson = FindUserBySnotifyID(SnotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, songUniqueID);
			if (index < 0)
			{
				// not on user playlist, we can't delete add
				//errorString = "Unable to find song to remove from user.";
				return false;
			}
			else
			{
				// on the user playlist, so we're updating
				tempPerson->saMyPlayList.getAtIndex(index)->rating = newRating;
				return true;
			}
		}
		else
		{
			return false;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == songUniqueID)
		//	{
		//		tempPerson->saMyPlayList.getAtIndex(index)->rating = newRating;
		//		return true;
		//	}
		//}
	}
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == SnotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB = this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == songUniqueID)
	//			{
	//				// Update the rating
	//				this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->rating = newRating;
	//				return true;
	//			}
	//		}
	//	}
	//}
	// no errorstring on this one for some reason
	return false;
}

// Returns 0, NULL, or nullptr if you can't find the song.
// (Can return optional information on errorString)
// 
// ****************************************************************************
// NOTE: This updates the "numberOfTimesPlayed" in THIS USER'S playlist-library
// ****************************************************************************
cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	cPerson* tempPerson = FindUserBySnotifyID(SnotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, songUniqueID);
			if (index < 0)
			{
				// not on user playlist, we can't get the song
				errorString = "Unable to find song on user's playlist.";
				return nullptr;
			}
			else
			{
				// on the user playlist, so we're returning it
				tempPerson->saMyPlayList.getAtIndex(index)->numberOfTimesPlayed++;
				return tempPerson->saMyPlayList.getAtIndex(index);
			}
		}
		else
		{
			errorString = "user playlist empty";
			return nullptr;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == songUniqueID)
		//	{
		//		tempPerson->saMyPlayList.getAtIndex(index)->numberOfTimesPlayed++;
		//		return tempPerson->saMyPlayList.getAtIndex(index);
		//	}
		//}
	}
	
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == SnotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == songUniqueID)
	//			{
	//				// we found the song on the user
	//				return this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB);
	//			}
	//		}
	//	}
	//}

	errorString = "Could not find user.";
	return nullptr;
}

// Note that the songRating is "returned" by reference. 
// If it can't find a match (i.e. returns false), then the rating isn't valid. 
bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, songUniqueID);
			if (index < 0)
			{
				// not on user playlist, we can't get the song's rating
				//errorString = "Unable to find song on user's playlist.";
				return false;
			}
			else
			{
				// on the user playlist, so we're returning it's rating
				songRating = tempPerson->saMyPlayList.getAtIndex(index)->rating;
				return true;
			}
		}
		else
		{
			return false;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == songUniqueID)
		//	{
		//		songRating = tempPerson->saMyPlayList.getAtIndex(index)->rating;
		//		return true;
		//	}
		//}
	}
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == snotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == songUniqueID)
	//			{
	//				// found the song, return by passing by reference
	//				songRating = this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->rating;
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}
bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		if (tempPerson->saMyPlayList.getSize() > 0)
		{
			MergeSort_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
			int index = BinarySearch_SongByID(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1, songUniqueID);
			if (index < 0)
			{
				// not on user playlist, we can't get the song's rating
				//errorString = "Unable to find song on user's playlist.";
				return false;
			}
			else
			{
				// on the user playlist, so we're returning it's rating
				numberOfPlays = tempPerson->saMyPlayList.getAtIndex(index)->numberOfTimesPlayed;
				return true;
			}
		}
		else
		{
			return false;
		}
		
		//for (unsigned int index = 0; index != tempPerson->saMyPlayList.getSize(); index++)
		//{
		//	if (tempPerson->saMyPlayList.getAtIndex(index)->getUniqueID() == songUniqueID)
		//	{
		//		numberOfPlays = tempPerson->saMyPlayList.getAtIndex(index)->numberOfTimesPlayed;
		//		return true;
		//	}
		//}
	}
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == snotifyUserID)
	//	{
	//		for (unsigned int indexB = 0; indexB != this->m_saUsers.getAtIndex(index)->saMyPlayList.getSize(); indexB++)
	//		{
	//			if (this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->getUniqueID() == songUniqueID)
	//			{
	//				// found the song, return by passing by reference
	//				numberOfPlays = this->m_saUsers.getAtIndex(index)->saMyPlayList.getAtIndex(indexB)->numberOfTimesPlayed;
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}

// Returns 0, NULL, or nullptr if these fail
// ...
// these are so I don't have to re-write the search every time...
cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	if (this->m_saUsers.getSize() > 0)
	{
		MergeSort_UsersBySIN(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
		int index = BinarySearch_UserBySIN(this->m_saUsers, 0, this->m_saUsers.getSize() - 1, SIN);
		if (index < 0)
		{
			return nullptr;
		}
		else
		{
			return this->m_saUsers.getAtIndex(index);
		}
	}
	
	// Linear search
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->SIN == SIN)
	//	{
	//		return this->m_saUsers.getAtIndex(index);
	//	}
	//}

	return nullptr;
}
cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	if (this->m_saUsers.getSize() > 0)
	{
		MergeSort_UsersBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
		int index = BinarySearch_UserBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1, SnotifyID);
		if (index < 0)
		{
			return nullptr;
		}
		else
		{
			return this->m_saUsers.getAtIndex(index);
		}
	}
	// linear seach
	//for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	//{
	//	if (this->m_saUsers.getAtIndex(index)->getSnotifyUniqueUserID() == SnotifyID)
	//	{
	//		return this->m_saUsers.getAtIndex(index);
	//	}
	//}
	return nullptr;
}
// See notes about passing by pointer.
// The TLDR is that if I update what this is pointed to, IT'S UPDATED ACROSS THE ENTIRE SYSTEM
// (You can also assume that with duplicates, it will return the 1st one it finds. I don't care which.)
cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	if (this->m_saSongs.getSize() > 0)
	{
		MergeSort_SongByName(this->m_saSongs, 0, this->m_saSongs.getSize() - 1);
		int index = BinarySearch_SongByNameANDArtist(this->m_saSongs, 0, this->m_saSongs.getSize() - 1, title, artist);
		if (index < 0)
		{
			return nullptr;
		}
		else
		{
			return this->m_saSongs.getAtIndex(index);
		}
	}
	// Linear search
	//for (unsigned int index = 0; index != this->m_saSongs.getSize(); index++)
	//{
	//	if (this->m_saSongs.getAtIndex(index)->name == title
	//		&& this->m_saSongs.getAtIndex(index)->artist == artist)
	//	{
	//		return this->m_saSongs.getAtIndex(index);
	//	}
	//}
	//std::cout << "Unable to Find Song with title and artist";
	return nullptr;
}
cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	if (this->m_saSongs.getSize() > 0)
	{
		MergeSort_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1);
		int index = BinarySearch_SongByID(this->m_saSongs, 0, this->m_saSongs.getSize() - 1, uniqueID);
		if (index < 0)
		{
			//std::cout << "Unable to Find Song with uniqueID" << std::endl;
			return nullptr;
		}
		else
		{
			return this->m_saSongs.getAtIndex(index);
		}
	}
	
	//for (unsigned int index = 0; index != this->m_saSongs.getSize(); index++)
	//{
	//	if (this->m_saSongs.getAtIndex(index)->getUniqueID() == uniqueID)
	//	{
	//		return this->m_saSongs.getAtIndex(index);
	//	}
	//}
	//std::cout << "Unable to Find Song with uniqueID";
	return nullptr;
}


// Returns false if these don't work
		// This returns a COPY of the users library, in the form of a regular dynamic array.
	// See the cSnotify.cpp file for more infomration on how this is supposed to work
	// It will return false if it can't find that user
// This returns a COPY of the users library, in the form of a regular dynamic array.
bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// The caller would do something like this (assume the user ID = 28472382)
	//
	//	cSong* pTheSongs = 0;
	//	unsigned int arraySize = 0;
	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
	// 
	// Inside this method, you'd do something like this:

	// TODO: Find that user... 
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);

	// Alloate a heap based array to hold all the songs...
	if (tempPerson != nullptr)
	{
		sizeOfLibary = tempPerson->saMyPlayList.getSize();
		cSong* pCopyOfLibrary = new cSong[sizeOfLibary];

		// Copy all the songs over
		for (unsigned int index = 0; index != sizeOfLibary; index++)
		{
			pCopyOfLibrary[index] = *(tempPerson->saMyPlayList.getAtIndex(index));
		}
		// pass back as reference
		pLibraryArray = pCopyOfLibrary;
		return true;
	}
	

//	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
//	pCopyOfLibrary = new cSong[sizeOfLibary];

	// The array and the size of the array are "returned" by reference to the caller. 

	// TODO: Copy all the songs over
	std::cout << "User doesn't exist" << std::endl;
	return false;
}


bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		MergeSort_SongByName(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
		// Copied from the other GetUsersSongLibrary
		sizeOfLibary = tempPerson->saMyPlayList.getSize();
		cSong* pCopyOfLibrary = new cSong[sizeOfLibary];

		for (unsigned int index = 0; index != sizeOfLibary; index++)
		{
			pCopyOfLibrary[index] = *(tempPerson->saMyPlayList.getAtIndex(index));
		}
		pLibraryArray = pCopyOfLibrary;
		return true;

	}
	return false;
}
// Same, but array is sorted by artist name, ascending ("A to Z")
bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	cPerson* tempPerson = FindUserBySnotifyID(snotifyUserID);
	if (tempPerson != nullptr)
	{
		MergeSort_SongByArtist(tempPerson->saMyPlayList, 0, tempPerson->saMyPlayList.getSize() - 1);
		// Copied from the other GetUsersSongLibrary
		sizeOfLibary = tempPerson->saMyPlayList.getSize();
		cSong* pCopyOfLibrary = new cSong[sizeOfLibary];

		for (unsigned int index = 0; index != sizeOfLibary; index++)
		{
			pCopyOfLibrary[index] = *(tempPerson->saMyPlayList.getAtIndex(index));
		}
		pLibraryArray = pCopyOfLibrary;
		return true;

	}
	return false;
}


bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	sizeOfUserArray = this->m_saUsers.getSize();
	cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
	for (unsigned int index = 0; index != sizeOfUserArray; index++)
	{
		pCopyOfUsers[index] = *(this->m_saUsers.getAtIndex(index));
	}
	pAllTheUsers = pCopyOfUsers;
	return true;
}
// Sorded ascending by Snotify ID
bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	MergeSort_UsersBySnotifyID(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);	// sort then copy over
	sizeOfUserArray = this->m_saUsers.getSize();
	cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
	for (unsigned int index = 0; index != sizeOfUserArray; index++)
	{
		pCopyOfUsers[index] = *(this->m_saUsers.getAtIndex(index));
	}
	pAllTheUsers = pCopyOfUsers;
	return true;
}

// These should all be sorted ascending ("A to Z") IF there are duplicates
bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	// If we are finding users by first name then we have to linearly search for them, at least until the firstName we're looking for is smaller than the current name
	MergeSort_UsersByFirstName(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
	// Users are now sorted by first name
	// let's make a new array and find any people that have the same first name
	cSmartArray_Template<cPerson*> tempPeople;
	for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	{
		if (this->m_saUsers.getAtIndex(index)->first.compare(firstName) == 0)
		{
			// hey, we found someone!
			tempPeople.insertAtEnd(this->m_saUsers.getAtIndex(index));
		}
		else if (this->m_saUsers.getAtIndex(index)->first.compare(firstName) > 0)
		{
			// ok, so if this works the way I think it does
			// we've gotten past the point where the first names are possible...
			if (tempPeople.getSize() > 0)
			{
				// let's copy the people over then
				sizeOfUserArray = tempPeople.getSize();
				cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
				for (unsigned int index = 0; index != sizeOfUserArray; index++)
				{
					pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
				}
				pAllTheUsers = pCopyOfUsers;

				return true;
			}
			return false;
		}
	}

	// hahahaha, ran into an issue where if the poeple being added are at the end of the list it returns before setting the pAllTheUserse
	if (tempPeople.getSize() > 0)
	{
		// let's copy the people over then
		sizeOfUserArray = tempPeople.getSize();
		cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
		}
		pAllTheUsers = pCopyOfUsers;

		return true;
	}

	return false;
}
bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	MergeSort_UsersByLastName(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
	// Users are now sorted by last name
	// let's make a new array and find any people that have the same first name
	cSmartArray_Template<cPerson*> tempPeople;
	for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	{
		if (this->m_saUsers.getAtIndex(index)->last.compare(lastName) == 0)
		{
			// hey, we found someone!
			tempPeople.insertAtEnd(this->m_saUsers.getAtIndex(index));
		}
		else if (this->m_saUsers.getAtIndex(index)->last.compare(lastName) > 0)
		{
			// ok, so if this works the way I think it does
			// we've gotten past the point where the first names are possible...
			if (tempPeople.getSize() > 0)
			{
				// let's copy the people over then
				sizeOfUserArray = tempPeople.getSize();
				cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
				for (unsigned int index = 0; index != sizeOfUserArray; index++)
				{
					pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
				}
				pAllTheUsers = pCopyOfUsers;

				return true;
			}
			return false;
		}
	}
	if (tempPeople.getSize() > 0)
	{
		// let's copy the people over then
		sizeOfUserArray = tempPeople.getSize();
		cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
		}
		pAllTheUsers = pCopyOfUsers;

		return true;
	}
	return false;
}
// Sorted ascending by last name THEN first name.
bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	MergeSort_UsersByLastThenFirstName(this->m_saUsers, 0, this->m_saUsers.getSize() - 1);
	// Users are now sorted by first name
	// let's make a new array and find any people that have the same first name
	cSmartArray_Template<cPerson*> tempPeople;
	for (unsigned int index = 0; index != this->m_saUsers.getSize(); index++)
	{
		if (this->m_saUsers.getAtIndex(index)->last.compare(lastName) == 0 
			&& this->m_saUsers.getAtIndex(index)->first.compare(firstName) == 0)
		{
			// hey, we found someone!
			tempPeople.insertAtEnd(this->m_saUsers.getAtIndex(index));
		}
		else if (this->m_saUsers.getAtIndex(index)->last.compare(lastName) > 0)
		{
			// ok, so if this works the way I think it does
			// we've gotten past the point where the first names are possible...
			if (tempPeople.getSize() > 0)
			{
				// let's copy the people over then
				sizeOfUserArray = tempPeople.getSize();
				cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
				for (unsigned int index = 0; index != sizeOfUserArray; index++)
				{
					pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
				}
				pAllTheUsers = pCopyOfUsers;

				return true;
			}
			return false;
		}
	}
	if (tempPeople.getSize() > 0)
	{
		// let's copy the people over then
		sizeOfUserArray = tempPeople.getSize();
		cPerson* pCopyOfUsers = new cPerson[sizeOfUserArray];
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			pCopyOfUsers[index] = *(tempPeople.getAtIndex(index));
		}
		pAllTheUsers = pCopyOfUsers;

		return true;
	}
	return false;
}


bool cSnotify::GetSnotifySongs(cSong*& pAllTheSongs, unsigned int& sizeOfSongArray)
{
	sizeOfSongArray = this->m_saSongs.getSize();
	cSong* pCopyOfSongs = new cSong[sizeOfSongArray];
	for (unsigned int index = 0; index != sizeOfSongArray; index++)
	{
		pCopyOfSongs[index] = *(this->m_saSongs.getAtIndex(index));
	}
	pAllTheSongs = pCopyOfSongs;
	return true;
}