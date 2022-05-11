#include "cMap_List.h"

void cMap_List::m_AllocateSpace(void)
{
	for (unsigned int count = 0; count != this->currentSize; count++)
	{
		LLofPairs* pEmptyLL = new LLofPairs();

		this->m_theData.insertAtEnd(pEmptyLL);
	}

	return;
}
// idk, just trying this for now I guess
void cMap_List::m_ReAllocateSpace(void)
{
	// Make a new smart array that's 2x the size of the old one
	int size = currentSize;
	currentSize *= 2;
	for (unsigned int count = size; count != this->currentSize; count++)
	{
		LLofPairs* pEmptyLL = new LLofPairs();

		this->m_theData.insertAtEnd(pEmptyLL);
	}
}

//unsigned int cMap_List::calcHashValue(cPerson keyValue)
//{
//	unsigned int hashValue = 0;
//	for (unsigned int index = 0; index != keyValue.first.length(); index++)
//	{
//		unsigned char curChar = keyValue.first[index] + (index * 10);
//
//		hashValue += (unsigned int)curChar;
//	}
//	hashValue %= this->currentSize;
//
//	return hashValue;
//}

unsigned int cMap_List::calcHashValue(unsigned int keyValue)
{
	unsigned int hashValue = keyValue % this->currentSize;
	return hashValue;
}

// the point of insertAtIndex for this is to add theSong to the user's list of songs
// so we need to find the keyValue in the list of pairs, then add the song to their list
bool cMap_List::insertAtIndex(cPerson keyValue, cSong* theSong)
{
	//unsigned int hashIndex = this->calcHashValue(keyValue);
	unsigned int hashIndex = this->calcHashValue(keyValue.getSnotifyUniqueUserID());

	LLofPairs* pLLatLocation = this->m_theData.getAtIndex(hashIndex);

	if (pLLatLocation->bIsEmpty())
	{
		// Nothing on the list, add it
		keyPersonSASong newKPS;
		newKPS.First = keyValue;
		newKPS.Second.insertAtEnd(theSong);
		pLLatLocation->insertAtCurrent(newKPS);
		return false;
	}

	// There's at least one thing in the list...

	// See if that person is already there.  If not, add them
	pLLatLocation->moveToHead();
	do
	{
		keyPersonSASong curKPS = pLLatLocation->getAtCurrent();
		// Is this a match
		if (curKPS.First.getSnotifyUniqueUserID() == keyValue.getSnotifyUniqueUserID())	// the spotify unique user ID is set when the person is made, so I can use it to identify if they're the same person
		{
			// Yes, this is the same key, so overwrite them
			// Not actually, we're going to add the song to the user's list of songs

			// TODO: Check if the song is already in the list
			for (unsigned int index = 0; index != curKPS.Second.getSize(); index++)
			{
				if (curKPS.Second.getAtIndex(index)->getUniqueID() == theSong->getUniqueID())
				{
					return true;
				}
			}

			curKPS.Second.insertAtEnd(theSong);

			pLLatLocation->getAtCurrent().Second = curKPS.Second;

			return false;
		}
	} while (pLLatLocation->moveToNext());

	// If we are here, then we DIDN'T find a key match
	// i.e. the person isn't in the list yet

	// So let's add them to the list
	keyPersonSASong newPair;
	newPair.First = keyValue;
	newPair.Second.insertAtEnd(theSong);

	pLLatLocation->insertAtCurrent(newPair);

	return false;
}


//cSmartArray_Template<cSong*> cMap_List::getAtIndex(cPerson keyValue)
//{
//	unsigned int hashIndex = this->calcHashValue(keyValue);
//
//	return this->m_theData.getAtIndex(hashIndex)->getAtCurrent().Second;
//
//}
//
//cSmartArray_Template<cSong*> cMap_List::getAtIndex(unsigned int keyValue)
//{
//	unsigned int hashIndex = this->calcHashValue(keyValue);
//	cSmartArray_Template<cSong*> tempSA;
//	for (unsigned int index = 0; index != this->m_theData.getAtIndex(hashIndex)->getAtCurrent().Second.getSize(); index++)
//	{
//		tempSA.insertAtEnd(this->m_theData.getAtIndex(hashIndex)->getAtCurrent().Second.getAtIndex(index));
//	}
//
//	//return this->m_theData.getAtIndex(hashIndex)->getAtCurrent().Second;
//	return tempSA;
//
//}

cSong* cMap_List::getAtIndex(unsigned int keyValue, unsigned int songValue)
{
	unsigned int hashIndex = this->calcHashValue(keyValue);

	LLofPairs* pLLatLocation = this->m_theData.getAtIndex(hashIndex);

	// See if that person is already there.  If not, add them
	pLLatLocation->moveToHead();
	do
	{
		keyPersonSASong curKPS = pLLatLocation->getAtCurrent();
		// Is this a match
		if (curKPS.First.getSnotifyUniqueUserID() == keyValue)	// the spotify unique user ID is set when the person is made, so I can use it to identify if they're the same person
		{
			// Yes, this is the same key, so overwrite them
			// Not actually, we're going to add the song to the user's list of songs

			// TODO: Check if the song is already in the list
			for (unsigned int index = 0; index != curKPS.Second.getSize(); index++)
			{
				if (curKPS.Second.getAtIndex(index)->getUniqueID() == songValue)
				{
					return curKPS.Second.getAtIndex(index);
				}
			}

			//return nullptr;
		}
	} while (pLLatLocation->moveToNext());

	return nullptr;
}