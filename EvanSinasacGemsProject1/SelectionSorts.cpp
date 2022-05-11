#include "cSmartArray_Template.h"
#include "cSong.h"


// https://www.geeksforgeeks.org/selection-sort/


void SelectionSort_SongsByName(cSmartArray_Template<cSong*> songs, int n)
{
	int i, j, min_index;

	// One by one, move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// find the minnimum element in unsorted array
		min_index = i;
		for (j = i + 1; j < n; j++)
		{
			if (songs.getAtIndex(j)->name.compare(songs.getAtIndex(min_index)->name) < 0)
			{
				min_index = j;
			}
		}

		// Swap the found minimum element with the first element
		cSong* temp = songs.getAtIndex(min_index);
		songs.setAtIndex(min_index, songs.getAtIndex(i));
		songs.setAtIndex(i, temp);
	}
}