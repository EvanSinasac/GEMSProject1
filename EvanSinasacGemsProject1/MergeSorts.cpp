#include "cSmartArray_Template.h"
#include "cSong.h"
#include "cPerson.h"


// https://www.geeksforgeeks.org/merge-sort/
//MergeSort(arr[], l, r)
//If r > l
//1. Find the middle point to divide the array into two halves :
//middle m = l + (r - l) / 2
//2. Call mergeSort for first half :
//Call mergeSort(arr, l, m)
//3. Call mergeSort for second half :
//Call mergeSort(arr, m + 1, r)
//4. Merge the two halves sorted in step 2 and 3 :
//    Call merge(arr, l, m, r)


void MergeSort_MergeSongByName(cSmartArray_Template<cSong*> songs, int const left, int const mid, int const right)
{
	// why the fuck do people use auto in teaching articles lmfao
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cSong*> leftArray;
	cSmartArray_Template<cSong*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(songs.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(songs.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		// But what is this actually comparing in terms of songs?  Name? ID?
		// Let's sort this one by name (simple)
		//if (leftArray.getAtIndex(indexOfSubArrayOne)->name[0] <= rightArray.getAtIndex(indexOfSubArrayTwo)->name[0])	// sort of works
		// compare returns 0 if they are eaqual, <0 if the first character that does not match is lower in the compared string (one calling compare)
		if (leftArray.getAtIndex(indexOfSubArrayOne)->name.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->name) <= 0)
		{
			songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void MergeSort_MergeSongByArtist(cSmartArray_Template<cSong*> songs, int const left, int const mid, int const right)
{
	// why the fuck do people use auto in teaching articles lmfao
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cSong*> leftArray;
	cSmartArray_Template<cSong*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(songs.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(songs.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		// But what is this actually comparing in terms of songs?  Name? ID?
		// Let's sort this one by artist name (simple)
		//if (leftArray.getAtIndex(indexOfSubArrayOne)->name[0] <= rightArray.getAtIndex(indexOfSubArrayTwo)->name[0])	// sort of works
		// compare returns 0 if they are eaqual, <0 if the first character that does not match is lower in the compared string (one calling compare)
		if (leftArray.getAtIndex(indexOfSubArrayOne)->artist.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->artist) <= 0)
		{
			songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void MergeSort_MergeSongByID(cSmartArray_Template<cSong*> songs, int const left, int const mid, int const right)
{
	// why the fuck do people use auto in teaching articles lmfao
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cSong*> leftArray;
	cSmartArray_Template<cSong*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(songs.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(songs.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->getUniqueID() <= rightArray.getAtIndex(indexOfSubArrayTwo)->getUniqueID())
		{
			songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		songs.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		songs.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void MergeSort_MergeUsersBySnotifyID(cSmartArray_Template<cPerson*> people, int const left, int const mid, int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cPerson*> leftArray;
	cSmartArray_Template<cPerson*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(people.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(people.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->getSnotifyUniqueUserID() <= rightArray.getAtIndex(indexOfSubArrayTwo)->getSnotifyUniqueUserID())
		{
			people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void MergeSort_MergeUsersBySIN(cSmartArray_Template<cPerson*> people, int const left, int const mid, int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cPerson*> leftArray;
	cSmartArray_Template<cPerson*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(people.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(people.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->SIN <= rightArray.getAtIndex(indexOfSubArrayTwo)->SIN)
		{
			people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void MergeSort_MergeUsersByFirstName(cSmartArray_Template<cPerson*> people, int const left, int const mid, int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cPerson*> leftArray;
	cSmartArray_Template<cPerson*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(people.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(people.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->first.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->first) <= 0)
		{
			people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void MergeSort_MergeUsersByLastName(cSmartArray_Template<cPerson*> people, int const left, int const mid, int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cPerson*> leftArray;
	cSmartArray_Template<cPerson*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(people.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(people.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->last.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->last) <= 0)
		{
			people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void MergeSort_MergeUsersByLastThenFirstName(cSmartArray_Template<cPerson*> people, int const left, int const mid, int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create the temp array
	cSmartArray_Template<cPerson*> leftArray;
	cSmartArray_Template<cPerson*> rightArray;

	// Copy the data
	for (unsigned int i = 0; i < subArrayOne; i++)
	{
		leftArray.insertAtEnd(people.getAtIndex(left + i));
	}
	for (unsigned int j = 0; j < subArrayTwo; j++)
	{
		rightArray.insertAtEnd(people.getAtIndex(mid + 1 + j));
	}

	unsigned int indexOfSubArrayOne = 0;	// Inital index of first sub-array
	unsigned int indexOfSubArrayTwo = 0;	// Initial index of second sub-array
	int indexOfMergedArray = left;			// Initla index of merged array

	// Merge the temp arrays back into array[left...right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray.getAtIndex(indexOfSubArrayOne)->last.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->last) == 0)
		{
			if (leftArray.getAtIndex(indexOfSubArrayOne)->first.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->first) < 0)
			{
				people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
				indexOfSubArrayOne++;
			}
			else
			{
				people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
				indexOfSubArrayTwo++;
			}
		}
		else if (leftArray.getAtIndex(indexOfSubArrayOne)->last.compare(rightArray.getAtIndex(indexOfSubArrayTwo)->last) < 0)
		{
			people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
			indexOfSubArrayOne++;
		}
		else
		{
			people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of left if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		people.setAtIndex(indexOfMergedArray, leftArray.getAtIndex(indexOfSubArrayOne));
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaing elements of the right array if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		people.setAtIndex(indexOfMergedArray, rightArray.getAtIndex(indexOfSubArrayTwo));
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// *****************************************************************************************************

// begin is for left index and end is right index of the sub-array to be sorted
void MergeSort_SongByName(cSmartArray_Template<cSong*> songs, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_SongByName(songs, begin, mid);
	MergeSort_SongByName(songs, mid + 1, end);
	MergeSort_MergeSongByName(songs, begin, mid, end);
}


void MergeSort_SongByArtist(cSmartArray_Template<cSong*> songs, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_SongByArtist(songs, begin, mid);
	MergeSort_SongByArtist(songs, mid + 1, end);
	MergeSort_MergeSongByArtist(songs, begin, mid, end);
}

void MergeSort_SongByID(cSmartArray_Template<cSong*> songs, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_SongByID(songs, begin, mid);
	MergeSort_SongByID(songs, mid + 1, end);
	MergeSort_MergeSongByID(songs, begin, mid, end);
}

void MergeSort_UsersBySnotifyID(cSmartArray_Template<cPerson*> people, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_UsersBySnotifyID(people, begin, mid);
	MergeSort_UsersBySnotifyID(people, mid + 1, end);
	MergeSort_MergeUsersBySnotifyID(people, begin, mid, end);
}

void MergeSort_UsersBySIN(cSmartArray_Template<cPerson*> people, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_UsersBySIN(people, begin, mid);
	MergeSort_UsersBySIN(people, mid + 1, end);
	MergeSort_MergeUsersBySIN(people, begin, mid, end);
}

void MergeSort_UsersByFirstName(cSmartArray_Template<cPerson*> people, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_UsersByFirstName(people, begin, mid);
	MergeSort_UsersByFirstName(people, mid + 1, end);
	MergeSort_MergeUsersByFirstName(people, begin, mid, end);
}

void MergeSort_UsersByLastName(cSmartArray_Template<cPerson*> people, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_UsersByLastName(people, begin, mid);
	MergeSort_UsersByLastName(people, mid + 1, end);
	MergeSort_MergeUsersByLastName(people, begin, mid, end);
}

void MergeSort_UsersByLastThenFirstName(cSmartArray_Template<cPerson*> people, int const begin, int const end)
{
	if (begin >= end)
		return;		// returns recursively

	int mid = begin + (end - begin) / 2;
	MergeSort_UsersByLastThenFirstName(people, begin, mid);
	MergeSort_UsersByLastThenFirstName(people, mid + 1, end);
	MergeSort_MergeUsersByLastThenFirstName(people, begin, mid, end);
}

