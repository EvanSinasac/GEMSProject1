#include "cSmartArray_Template.h"
#include "cSong.h"

// https://www.geeksforgeeks.org/heap-sort/

void heapify(cSmartArray_Template<cSong*> songs, int n, int i)
{
	int largest = i;	// initializes largest as root
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// if left child is larger than root
	if (left < n && songs.getAtIndex(left)->name.compare(songs.getAtIndex(largest)->name) > 0)
	{
		largest = left;
	}

	if (right < n && songs.getAtIndex(right)->name.compare(songs.getAtIndex(largest)->name) > 0)
	{
		largest = right;
	}

	// If largest is not root
	if (largest != i)
	{
		// swap
		cSong* temp = songs.getAtIndex(largest);
		songs.setAtIndex(largest, songs.getAtIndex(i));
		songs.setAtIndex(i, temp);

		// Recursively heapify the affected sub-tree
		heapify(songs, n, largest);
	}
}

void HeapSort_SongsByName(cSmartArray_Template<cSong*> songs, int n)
{
	// build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(songs, n, i);
	}

	// One by one, extract an element from heap
	for (int i = n - 1; i > 0; i--)
	{
		// Swap
		cSong* temp = songs.getAtIndex(0);
		songs.setAtIndex(0, songs.getAtIndex(i));
		songs.setAtIndex(i, temp);

		// call max heapify on the reduced heap
		heapify(songs, i, 0);
	}
}