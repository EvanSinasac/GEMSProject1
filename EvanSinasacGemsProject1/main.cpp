// Evan Sinasac - 1081418
// INFO6023 Algorithms & GEMS Project 1
// Description:
//			The purpose of this project is to implement an API for "Snotify"
//			Generating random people and making lists for them.  (A menu of some kind is optional, probably wont do it myself)
//			The other main purpose of this is to use containers and sorting/searching code I have created myself
//			i.e. can't just use the std array or a vector, I have to make it myself
//			
//			1st part: person generator, read information and randomly generate a number of people that are then added to "Snotify"
//			2nd part: song list generator, reads information to generate a playlist for... the user I assume
//			3rd part: snotify, our funny version of Spotify that we can add/remove users, look them up, add and remove songs, track rankings of songs, searches and sorts


#include "cPerson.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"

#include <sstream>
#include <iostream>

int main(int argc, char** argv)
{
	srand(time(NULL));	// seed time so rand is somewhat more random

	std::string errorString;
	cPersonGenerator* personGenerator = new cPersonGenerator();
	cMusicGenerator* musicGenerator = new cMusicGenerator();
	cSnotify* snotify = new cSnotify();

	std::stringstream babyFile;
	babyFile << PROJECT_DIR << "Popular Baby Names/names/" << "yob2019.txt";

	if (!personGenerator->LoadCensusFiles(babyFile.str(), "Names_2010Census.csv", "Street_Names.csv", errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}

	
	std::cout << std::endl;

	// personGenerator testing
	
	cPerson* matt = personGenerator->generateRandomPerson();		// here's our snotify user
	std::cout
			<< matt->first << " " << matt->middle << " " << matt->last << "\n"
			<< ((matt->gender == cPerson::eGenderType::MALE) ? "M" : (matt->gender == cPerson::eGenderType::FEMALE ? "F" : "NB")) << "\n"
			<< matt->age << "\n"
			<< matt->streetName << " " << matt->streetType << " " << matt->streetDirection << "\n"
			<< matt->getSnotifyUniqueUserID() << std::endl;

	//system("pause");
	//cSmartArray_Template<cPerson*> people;

	//cPerson* heyMan = personGenerator->generateRandomPerson();

	//std::cout
	//	<< heyMan->first << " " << heyMan->middle << " " << heyMan->last << "\n"
	//	<< ((heyMan->gender == cPerson::eGenderType::MALE) ? "M" : (heyMan->gender == cPerson::eGenderType::FEMALE ? "F" : "NB")) << "\n"
	//	<< heyMan->age << "\n"
	//	<< heyMan->streetName << " " << heyMan->streetType << " " << heyMan->streetDirection << std::endl;

	//for (unsigned int index = 0; index != 5; index++)
	//{
	//	people.insertAtEnd(personGenerator->generateRandomPerson());
	//}

	//for (unsigned int index = 0; index != people.getSize(); index++)
	//{
	//	cPerson* heyMan = people.getAtIndex(index);
	//	std::cout
	//		<< heyMan->first << " " << heyMan->middle << " " << heyMan->last << "\n"
	//		<< ((heyMan->gender == cPerson::eGenderType::MALE) ? "M" : (heyMan->gender == cPerson::eGenderType::FEMALE ? "F" : "NB")) << "\n"
	//		<< heyMan->age << "\n"
	//		<< heyMan->streetNumber << " " << heyMan->streetName << " " << heyMan->streetType << " " << heyMan->streetDirection << "\n"
	//		<< heyMan->city << ", " << heyMan->province << "\n"
	//		<< heyMan->postalCode[0] << heyMan->postalCode[1] << heyMan->postalCode[2]
	//		<< " " << heyMan->postalCode[3] << heyMan->postalCode[4] << heyMan->postalCode[5] << "\n"
	//		<< std::endl;
	//}

	//// Testing remove
	//people.removeAtIndex(2);
	//std::cout << std::endl;

	//for (unsigned int index = 0; index != people.getSize(); index++)
	//{
	//	cPerson* heyMan = people.getAtIndex(index);
	//	std::cout
	//		<< heyMan->first << " " << heyMan->middle << " " << heyMan->last << "\n"
	//		<< ((heyMan->gender == cPerson::eGenderType::MALE) ? "M" : (heyMan->gender == cPerson::eGenderType::FEMALE ? "F" : "NB")) << "\n"
	//		<< heyMan->age << "\n"
	//		<< heyMan->streetName << " " << heyMan->streetType << " " << heyMan->streetDirection << "\n" << std::endl;
	//}


	if (!musicGenerator->LoadMusicInformation("hot_stuff_2.csv", errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}

	// testing
	//for (unsigned int index = 0; index != musicGenerator->saAllSongs.getSize(); index++)
	//{
	//	std::cout << musicGenerator->saAllSongs.getAtIndex(index)->name 
	//		<< " by " << musicGenerator->saAllSongs.getAtIndex(index)->artist << std::endl;
	//}

	// Song testing
	cSong* quickTest = musicGenerator->findSong("Poor Little Fool", "Ricky Nelson");
	if (!quickTest)
	{
		std::cout << "Didn't find the song!" << std::endl;
	}
	else
	{
		std::cout << "Hey!  I found the song!" << "\n"
			<< quickTest->name << " by " << quickTest->artist << "\n"
			<< "It's Unique ID is: " << quickTest->getUniqueID() << std::endl;
	}

	cSong* randTest = musicGenerator->getRandomSong();
	std::cout << "Random song: " << randTest->name << " by " << randTest->artist << "\n" 
		<< "Unique ID: "  << randTest->getUniqueID() << std::endl;

	std::cout << std::endl;
	//system("pause");

	// and we've got two different songs we can test with

	if (!snotify->AddUser(matt, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	std::cout << "Added User to Snotify!" << std::endl;
	if (!snotify->AddSong(quickTest, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	if (!snotify->AddSong(randTest, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	if (!snotify->AddSong(randTest, errorString))
	{
		std::cout << errorString << std::endl;
		//return -1;
	}
	std::cout << "2 songs added to Snotify" << std::endl;
	if (!snotify->AddSongToUserLibrary(matt->getSnotifyUniqueUserID(), quickTest, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	std::cout << "Added song to user!" << std::endl;
	if (!snotify->AddSongToUserLibrary(matt->getSnotifyUniqueUserID(), randTest, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	if (!snotify->AddSongToUserLibrary(matt->getSnotifyUniqueUserID(), randTest, errorString))
	{
		std::cout << errorString << std::endl;
		//return -1;
	}
	std::cout << "Added second song to user and tried to re-add it as well" << std::endl;

	{
		std::cout << std::endl;
		std::cout << "Songs on Snotify: " << std::endl;
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetSnotifySongs(pTheSongs, arraySize))
		{
			std::cout << "Couldn't get the users" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		std::cout << std::endl;
	}

	//system("pause");

	std::cout << std::endl;
	
	std::cout << "User ID: " << matt->getSnotifyUniqueUserID() << std::endl;
	std::cout << "Song ID: " << randTest->getUniqueID() << std::endl;

	{
		cSong* lookingFor = snotify->GetSong(matt->getSnotifyUniqueUserID(), randTest->getUniqueID(), errorString);
		if (lookingFor == nullptr)
		{
			std::cout << errorString << std::endl;
			return -1;
		}

		std::cout << "Found this on Matt: \n"
			<< lookingFor->name << " by " << lookingFor->artist << "\n"
			<< "Number of times played: " << lookingFor->numberOfTimesPlayed << "\n"
			<< "Rating: " << lookingFor->rating << std::endl;
	}
	std::cout << std::endl;
	{
		cSong* lookingFor = snotify->GetSong(matt->getSnotifyUniqueUserID(), randTest->getUniqueID(), errorString);
		if (lookingFor == nullptr)
		{
			std::cout << errorString << std::endl;
			return -1;
		}

		std::cout << "Found this on Matt, but again!: \n"
			<< lookingFor->name << " by " << lookingFor->artist << "\n"
			<< "Number of times played: " << lookingFor->numberOfTimesPlayed << "\n"
			<< "Rating: " << lookingFor->rating << "\n"
			<< "Age: " << matt->age << std::endl;
	}

	matt->age++;
	// changed matt's age, what happens when I run update user and then another getSong?
	if (!snotify->UpdateUser(matt, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	std::cout << std::endl;
	{
		cSong* lookingFor = snotify->GetSong(matt->getSnotifyUniqueUserID(), randTest->getUniqueID(), errorString);
		if (lookingFor == nullptr)
		{
			std::cout << errorString << std::endl;
			return -1;
		}

		cPerson* mattClone = snotify->FindUserBySnotifyID(matt->getSnotifyUniqueUserID());

		std::cout << "Found this on Matt, after age change, on a clone!: \n"
			<< lookingFor->name << " by " << lookingFor->artist << "\n"
			<< "Number of times played: " << lookingFor->numberOfTimesPlayed << "\n"
			<< "Rating: " << lookingFor->rating << "\n"
			<< "Age: " << mattClone->age << std::endl;
	}
	matt->age++;
	// changed matt's age, what happens when I run update user and then another getSong?
	if (!snotify->UpdateUser(matt, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}
	std::cout << std::endl;
	{
		cSong* lookingFor = snotify->GetSong(matt->getSnotifyUniqueUserID(), randTest->getUniqueID(), errorString);
		if (lookingFor == nullptr)
		{
			std::cout << errorString << std::endl;
			return -1;
		}

		cPerson* mattClone = snotify->FindUserBySIN(matt->SIN);
		if (!snotify->UpdateRatingOnSong(mattClone->getSnotifyUniqueUserID(), lookingFor->getUniqueID(), 10))
		{
			std::cout << "Couldn't update rating" << std::endl;
			//return -1;
		}

		// let's actually test the values in snotify
		unsigned int rating, numberOfPlays;
		if (!snotify->GetCurrentSongNumberOfPlays(mattClone->getSnotifyUniqueUserID(), lookingFor->getUniqueID(), numberOfPlays))
		{
			std::cout << "Couldn't get current song number of plays" << std::endl;
			return -1;
		}
		if (!snotify->GetCurrentSongRating(mattClone->getSnotifyUniqueUserID(), lookingFor->getUniqueID(), rating))
		{
			std::cout << "Couldn't get the current song rating" << std::endl;
			return -1;
		}

		std::cout << "This pass updated the rating on the song, and used the gets to get the current number of plays and song rating" << std::endl;
		std::cout << "Found this on Matt, after age change, on a clone with his SIN!: \n"
			<< lookingFor->name << " by " << lookingFor->artist << "\n"
			<< "Number of times played: " << numberOfPlays<< "\n"
			<< "Rating: " << rating << "\n"
			<< "Age: " << mattClone->age << std::endl;
	}
	// do deletes later
	//system("pause");
	std::cout << std::endl;

	std::cout << "randTest name: " << randTest->name << std::endl;;

	randTest->name = randTest->name + " boo ";
	if (!snotify->UpdateSong(randTest, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}

	cSong* findTestID = snotify->FindSong(randTest->getUniqueID());
	if (findTestID == nullptr)
	{
		std::cout << "couldn't find the song" << std::endl;
		return -1;
	}
	std::cout << "findTestID name: " << findTestID->name << std::endl;
	// this was to make sure update changed the name of the song

	// now real test, did changing the name update it on the user?

	cSong* findTestNameArtist = snotify->FindSong(quickTest->name, quickTest->artist);
	if (findTestNameArtist == nullptr)
	{
		std::cout << "couldn't find the song" << std::endl;
		return -1;
	}
	std::cout << "findTestNameArtist name: " << findTestNameArtist->name << " by " << findTestNameArtist->artist << std::endl;
	
	//system("pause");
	// ********************************************************************************************
	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << std::endl;

	{
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetUsersSongLibrary(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
		{
			std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
			return -1;
		}
		// otherwise, it returned fine and we should be able to print out the array
		std::cout << "Matt's snotify playlist: " << std::endl;
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		// eyyyyy, the song name updated, so that means the update works good
	}

	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << std::endl;

	{
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetUsersSongLibraryAscendingByTitle(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
		{
			std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
			return -1;
		}
		// otherwise, it returned fine and we should be able to print out the array
		std::cout << "Matt's snotify playlist, sorted by title: " << std::endl;
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		// eyyyyy, the song name updated, so that means the update works good
	}

	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << std::endl;

	{
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetUsersSongLibraryAscendingByArtist(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
		{
			std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
			return -1;
		}
		// otherwise, it returned fine and we should be able to print out the array
		std::cout << "Matt's snotify playlist, sorted by artist: " << std::endl;
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		// eyyyyy, the song name updated, so that means the update works good
	}

	{
		std::cout << std::endl;
		std::cout << "Before removes and deletes: " << std::endl;
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetSnotifySongs(pTheSongs, arraySize))
		{
			std::cout << "Couldn't get the users" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		std::cout << std::endl;
	}


	// and to end we have to test the deletes
	// First, let's remove the song from the user's library
	{
		if (!snotify->RemoveSongFromUserLibrary(matt->getSnotifyUniqueUserID(), quickTest->getUniqueID(), errorString))
		{
			std::cout << errorString << std::endl;
			return -1;
		}
		// ok cewl, remove worked, let's quickly grab the playlist again
		std::cout << std::endl;
		std::cout << "********************************************************************************************" << std::endl;
		std::cout << std::endl;

		{
			cSong* pTheSongs = 0;
			unsigned int arraySize = 0;
			if (!snotify->GetUsersSongLibrary(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
			{
				std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
				return -1;
			}
			// otherwise, it returned fine and we should be able to print out the array
			std::cout << "Matt's snotify playlist: " << std::endl;
			for (unsigned int index = 0; index != arraySize; index++)
			{
				std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
			}
		}
		// there, plalist printed, let's add the song back
		if (!snotify->AddSongToUserLibrary(matt->getSnotifyUniqueUserID(), quickTest, errorString))
		{
			std::cout << errorString << std::endl;
			//return -1;
		}
		std::cout << std::endl;
		std::cout << "Re-added the song to test deleting the song, now re-printing playlist" << std::endl;
		{
			cSong* pTheSongs = 0;
			unsigned int arraySize = 0;
			if (!snotify->GetUsersSongLibrary(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
			{
				std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
				return -1;
			}
			// otherwise, it returned fine and we should be able to print out the array
			std::cout << "Matt's snotify playlist: " << std::endl;
			for (unsigned int index = 0; index != arraySize; index++)
			{
				std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
			}
			// eyyyyy, the song name updated, so that means the update works good
		}

		// ok, song is back on the playlist, now we need to delete it from snotify
		if (!snotify->DeleteSong(quickTest->getUniqueID(), errorString))
		{
			std::cout << errorString << std::endl;
			return -1;
		}
		std::cout << std::endl;
		// song should be deleted, now let's re-print the playlist
		std::cout << quickTest->name << " by " << quickTest->artist << " should be deleted from Snotify.  Printing Matt's playlist to make sure it was removed correctly." << std::endl;
		std::cout << std::endl; 
		{
			cSong* pTheSongs = 0;
			unsigned int arraySize = 0;
			if (!snotify->GetUsersSongLibrary(matt->getSnotifyUniqueUserID(), pTheSongs, arraySize))
			{
				std::cout << "GetUsersSongLibrary failed!  Waaaaahhhhh!!!" << std::endl;
				return -1;
			}
			// otherwise, it returned fine and we should be able to print out the array
			std::cout << "Matt's snotify playlist: " << std::endl;
			for (unsigned int index = 0; index != arraySize; index++)
			{
				std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
			}
		}
		// awesome, now we need to delete the user
	}

	{
		std::cout << std::endl;
		std::cout << "After removes and deletes: " << std::endl;
		cSong* pTheSongs = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetSnotifySongs(pTheSongs, arraySize))
		{
			std::cout << "Couldn't get the users" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pTheSongs[index].name << " by " << pTheSongs[index].artist << std::endl;
		}
		std::cout << std::endl;
	}


	//system("pause");
	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	//std::cout << std::endl;

	cPerson* carl = personGenerator->generateRandomPerson();
	std::string carlFirst = carl->first;
	std::string carlLast = carl->last;
	if (!snotify->AddUser(carl, errorString))
	{
		std::cout << errorString << std::endl;
		//return -1;
	}
	cPerson* mattDup = personGenerator->generateRandomPerson();
	mattDup->first = matt->first;
	mattDup->middle = matt->middle;
	mattDup->last = matt->last;
	// MattDup happens to have the same full name but everything else should be different
	if (!snotify->AddUser(mattDup, errorString))
	{
		std::cout << errorString << std::endl;
		//return -1;
	}

	cPerson* mattDupA = personGenerator->generateRandomPerson();
	mattDupA->first = matt->first;
	mattDupA->middle = matt->middle;
	mattDupA->last = matt->last + "a";
	// MattDupA happens to have the same full name with an a on their last name but everything else should be different
	if (!snotify->AddUser(mattDupA, errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}

	{	// testing Get Users
		std::cout << "GetUsers" << std::endl;
		std::cout << std::endl;
		cPerson* pThePeople = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetUsers(pThePeople, arraySize))
		{
			std::cout << "Couldn't get the users" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pThePeople[index].first << " " << pThePeople[index].middle << " " << pThePeople[index].last << "\n"
				<< "Age: " << pThePeople[index].age << "    Gender: " << pThePeople[index].getGenderAsString() << "\n"
				<< "SIN: " << pThePeople[index].SIN << "\n"
				<< "SnotifyID: " << pThePeople[index].getSnotifyUniqueUserID() << "\n"
				<< "Location: " << pThePeople[index].streetNumber << " " << pThePeople[index].streetName << " " << pThePeople[index].streetType
				<< " " << pThePeople[index].streetDirection << " " << pThePeople[index].city << ", " << pThePeople[index].province << " "
				<< pThePeople[index].postalCode[0] << pThePeople[index].postalCode[1] << pThePeople[index].postalCode[2] << " "
				<< pThePeople[index].postalCode[3] << pThePeople[index].postalCode[4] << pThePeople[index].postalCode[5] << "\n"
				<< std::endl;
		}		
	}
	
	// ok, now we have 3 users, let's test the Finds, delete and second get
	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	//std::cout << std::endl;
	{ // testing find first name
		std::cout << "FindUsersFirstName" << std::endl;
		std::cout << std::endl;
		cPerson* pAllTheUsers = 0;
		unsigned int sizeOfUserArray = 0;
		if (!snotify->FindUsersFirstName(matt->first, pAllTheUsers, sizeOfUserArray))
		{
			std::cout << "Couldn't find Users with Matt's real first name" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			std::cout << pAllTheUsers[index].first << " " << pAllTheUsers[index].middle << " " << pAllTheUsers[index].last << "\n"
				<< "Age: " << pAllTheUsers[index].age << "    Gender: " << pAllTheUsers[index].getGenderAsString() << "\n"
				<< "SIN: " << pAllTheUsers[index].SIN << "\n"
				<< "SnotifyID: " << pAllTheUsers[index].getSnotifyUniqueUserID() << "\n"
				<< "Location: " << pAllTheUsers[index].streetNumber << " " << pAllTheUsers[index].streetName << " " << pAllTheUsers[index].streetType
				<< " " << pAllTheUsers[index].streetDirection << " " << pAllTheUsers[index].city << ", " << pAllTheUsers[index].province << " "
				<< pAllTheUsers[index].postalCode[0] << pAllTheUsers[index].postalCode[1] << pAllTheUsers[index].postalCode[2] << " "
				<< pAllTheUsers[index].postalCode[3] << pAllTheUsers[index].postalCode[4] << pAllTheUsers[index].postalCode[5] << "\n"
				<< std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	//std::cout << std::endl;
	{ // testing find last name
		std::cout << "FindUsersLastName" << std::endl;
		std::cout << std::endl;
		cPerson* pAllTheUsers = 0;
		unsigned int sizeOfUserArray = 0;
		if (!snotify->FindUsersLastName(carlLast, pAllTheUsers, sizeOfUserArray))
		{
			std::cout << "Couldn't find Users with Carl's real last name" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			std::cout << pAllTheUsers[index].first << " " << pAllTheUsers[index].middle << " " << pAllTheUsers[index].last << "\n"
				<< "Age: " << pAllTheUsers[index].age << "    Gender: " << pAllTheUsers[index].getGenderAsString() << "\n"
				<< "SIN: " << pAllTheUsers[index].SIN << "\n"
				<< "SnotifyID: " << pAllTheUsers[index].getSnotifyUniqueUserID() << "\n"
				<< "Location: " << pAllTheUsers[index].streetNumber << " " << pAllTheUsers[index].streetName << " " << pAllTheUsers[index].streetType
				<< " " << pAllTheUsers[index].streetDirection << " " << pAllTheUsers[index].city << ", " << pAllTheUsers[index].province << " "
				<< pAllTheUsers[index].postalCode[0] << pAllTheUsers[index].postalCode[1] << pAllTheUsers[index].postalCode[2] << " "
				<< pAllTheUsers[index].postalCode[3] << pAllTheUsers[index].postalCode[4] << pAllTheUsers[index].postalCode[5] << "\n"
				<< std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "********************************************************************************************" << std::endl;
	std::cout << std::endl;
	{ // testing find first last name
		std::cout << "FindUsersFirstLastNames" << std::endl;
		std::cout << std::endl;
		cPerson* pAllTheUsers = 0;
		unsigned int sizeOfUserArray = 0;
		if (!snotify->FindUsersFirstLastNames(matt->first, matt->last, pAllTheUsers, sizeOfUserArray))
		{
			std::cout << "Couldn't find Users with Matt's real full name" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != sizeOfUserArray; index++)
		{
			std::cout << pAllTheUsers[index].first << " " << pAllTheUsers[index].middle << " " << pAllTheUsers[index].last << "\n"
				<< "Age: " << pAllTheUsers[index].age << "    Gender: " << pAllTheUsers[index].getGenderAsString() << "\n"
				<< "SIN: " << pAllTheUsers[index].SIN << "\n"
				<< "SnotifyID: " << pAllTheUsers[index].getSnotifyUniqueUserID() << "\n"
				<< "Location: " << pAllTheUsers[index].streetNumber << " " << pAllTheUsers[index].streetName << " " << pAllTheUsers[index].streetType
				<< " " << pAllTheUsers[index].streetDirection << " " << pAllTheUsers[index].city << ", " << pAllTheUsers[index].province << " "
				<< pAllTheUsers[index].postalCode[0] << pAllTheUsers[index].postalCode[1] << pAllTheUsers[index].postalCode[2] << " "
				<< pAllTheUsers[index].postalCode[3] << pAllTheUsers[index].postalCode[4] << pAllTheUsers[index].postalCode[5] << "\n"
				<< std::endl;
		}
	}

	// ok, now after all those finds, let's delete mattDup from Snotify
	if (!snotify->DeleteUser(mattDup->getSnotifyUniqueUserID(), errorString))
	{
		std::cout << errorString << std::endl;
		return -1;
	}

	{ // final get, getUsersByID
		std::cout << "GetUsersByID" << std::endl;
		std::cout << std::endl;
		cPerson* pThePeople = 0;
		unsigned int arraySize = 0;
		if (!snotify->GetUsersByID(pThePeople, arraySize))
		{
			std::cout << "Couldn't get the users" << std::endl;
			return -1;
		}
		for (unsigned int index = 0; index != arraySize; index++)
		{
			std::cout << pThePeople[index].first << " " << pThePeople[index].middle << " " << pThePeople[index].last << "\n"
				<< "Age: " << pThePeople[index].age << "    Gender: " << pThePeople[index].getGenderAsString() << "\n"
				<< "SIN: " << pThePeople[index].SIN << "\n"
				<< "SnotifyID: " << pThePeople[index].getSnotifyUniqueUserID() << "\n"
				<< "Location: " << pThePeople[index].streetNumber << " " << pThePeople[index].streetName << " " << pThePeople[index].streetType
				<< " " << pThePeople[index].streetDirection << " " << pThePeople[index].city << ", " << pThePeople[index].province << " "
				<< pThePeople[index].postalCode[0] << pThePeople[index].postalCode[1] << pThePeople[index].postalCode[2] << " "
				<< pThePeople[index].postalCode[3] << pThePeople[index].postalCode[4] << pThePeople[index].postalCode[5] << "\n"
				<< std::endl;
		}
	}

	//system("pause");
	std::cout << "End of Program, thank you!" << std::endl;
	system("pause");
	return 0;
}