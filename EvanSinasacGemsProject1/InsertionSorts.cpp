#include "cSmartArray_Template.h"
#include "cSong.h"
#include "cPerson.h"

// https://www.geeksforgeeks.org/insertion-sort/

// Insertion sort is one of the best sorting algorithms for mostly sorted data
// such as when we're adding the list of songs and sorting as we go

void InsertionSort_SongsByName(cSmartArray_Template<cSong*> songs, int n)
{
	int i, j;
	cSong* key;
	for (i = 1; i < n; i++)
	{
		key = songs.getAtIndex(i);
		j = i - 1;

		// Move the elemnt sof songs that are greater than key, to one ahead of their current position
		while (j >= 0 && songs.getAtIndex(j)->name.compare(key->name) > 0)
		{
			songs.setAtIndex(j + 1, songs.getAtIndex(j));
			j = j - 1;
		}
		songs.setAtIndex(j + 1, key);
	}
}


// ******************************************************************************************************************

// Don't think I'm going to use these, but I'm adding them just in case
void InsertionSort_UsersBySnotifyID(cSmartArray_Template<cPerson*> people, int n)
{
	int i, j;
	cPerson* key;
	for (i = 1; i < n; i++)
	{
		key = people.getAtIndex(i);
		j = i - 1;

		// Move the elemnt sof songs that are greater than key, to one ahead of their current position
		while (j >= 0 && people.getAtIndex(j)->getSnotifyUniqueUserID() > key->getSnotifyUniqueUserID())
		{
			people.setAtIndex(j + 1, people.getAtIndex(j));
			j = j - 1;
		}
		people.setAtIndex(j + 1, key);
	}
}

void InsertionSort_UsersBySIN(cSmartArray_Template<cPerson*> people, int n)
{
	int i, j;
	cPerson* key;
	for (i = 1; i < n; i++)
	{
		key = people.getAtIndex(i);
		j = i - 1;

		// Move the elemnt sof songs that are greater than key, to one ahead of their current position
		while (j >= 0 && people.getAtIndex(j)->SIN > key->SIN)
		{
			people.setAtIndex(j + 1, people.getAtIndex(j));
			j = j - 1;
		}
		people.setAtIndex(j + 1, key);
	}
}