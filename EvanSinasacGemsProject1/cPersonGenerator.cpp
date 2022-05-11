#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

cPersonGenerator::cPersonGenerator()
{
	this->numOfNames = 0;
	this->numOfSurnames = 0;
	this->numOfStreets = 0;
}
cPersonGenerator::~cPersonGenerator()
{

}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	// TODO: Put YOUR amazing code here!
	// Bit messy, but I'll do each load here
	// TODO: Add to some kind of list or array I make to track the surnames (probably want an array or vector type so when I'm generating I can use the index as a random selection)
	// What I think I'll end up doing is have some kind of storage container for each file, and after/while they've been read
	// load the storage container.  Then when generating a random person I can use an index or something for them

	// TODO: Baby names
	std::ifstream babyFile(babyNameFile);
	if (!babyFile.is_open())
	{
		errorString = "Didn't open baby file";
		std::cout << "Didn't open baby file" << std::endl;
		return false;
	}

	// name,gender,number of babies
	// Olivia,F,18451
	//		- there can be entries with the same name but different genders
	//		- so when we generate the person, they can be male or female if the name appears as both in the file
	//		- otherwise, we can't identify them by the other gender
	//		- however, any person can be non-binary (although there is no non-binary in the file since that is something you decide as a person later in life)

	std::string theLine;

	unsigned int lineCount = 0;

	while (std::getline(babyFile, theLine))
	{
		cBabyNames tempBaby;
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			// TODO: Replace this with adding to my storage container
			if (tokenCount == 0)		// 0 is name
			{
				//std::cout << token << std::endl;
				tempBaby.SetName(token);
			}
			if (tokenCount == 1)		// 1 is gender (will need to be stored)
			{
				tempBaby.SetGender(token);
			}
			// 2 is number born (not needed)
			// Ignore the other parts of the line
			tokenCount++;
		}
		this->saBabyNames.insertAtEnd(tempBaby);
	}

	std::cout << "Baby names Lines read = " << lineCount << std::endl;
	std::cout << "saBabyNames size: " << this->saBabyNames.getSize() << std::endl;
	this->numOfNames = lineCount;

	babyFile.close();

	// Surnames
	// Open the file
	std::ifstream namesFile(surnameFile);
	if (!namesFile.is_open())
	{
		errorString = "Didn't open Surname File";
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	/*std::string*/ theLine = "";

	/*unsigned int*/ lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		cSurnames tempSurname;
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			// When this is uncommented, it takes about 40 seconds to load and print the file
			// TODO: Replace this with adding to my storage container
			if (tokenCount == 0)
			{
				tempSurname.SetName(token);
				//std::cout << token << std::endl;
			}
			// Might use things such as rank or count to weigh the likliness of someone being randomly generated with a name, but for generating people will really only need the name
			// Ignore the other parts of the line
			tokenCount++;
		}
		this->saSurnames.insertAtEnd(tempSurname);
	}

	std::cout << "Surnames Lines read = " << lineCount << std::endl;
	std::cout << "saSurnames size: " << saSurnames.getSize() << std::endl;
	this->numOfSurnames = lineCount;

	namesFile.close();

	// TODO: Street Names
	std::ifstream streetFile(streetNameFile);
	if (!streetFile.is_open())
	{
		errorString = "Didn't open Street Name File";
		std::cout << "Didn't open Street Name File" << std::endl;
		return false;
	}

	// FullStreetName, StreetName, StreetType, PostDirection
	// MISSION BAY BLVD NORTH, MISSION BAY, BLVD, NORTH
	//			- When generating a person we want the name, type and direction
	//			- however, not every street has a direction, so that will need a default null value
	//			- otherwise, take each token out and store it in the custom container

	/*std::string*/ theLine = "";

	/*unsigned int*/ lineCount = 0;
	while (std::getline(streetFile, theLine))
	{
		cStreetNames tempStreet;
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			// TODO: Replace this with adding to my storage container
			// 0 is the full line
			if (tokenCount == 1)		// 1 is the street name
			{
				//std::cout << token << std::endl;	// just using this to test for now
				tempStreet.SetName(token);
			}
			if (tokenCount == 2)		// 2 is the street type
			{
				tempStreet.SetType(token);
			}
			if (tokenCount == 3)		// 3 is the street direction (may be empty for some streets)
			{
				tempStreet.SetDirection(token);
			}
			// Will need all but the first token, so the inverse of the other reads
			tokenCount++;
		}
		this->saStreetNames.insertAtEnd(tempStreet);
	}

	std::cout << "Street Names Lines read = " << lineCount << std::endl;
	std::cout << "saStreetNames size: " << saStreetNames.getSize() << std::endl;
	this->numOfStreets = lineCount;

	streetFile.close();

	return true;
}


unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return this->numOfNames;
}
unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return this->numOfSurnames;
}
unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return this->numOfStreets;
}


cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cPerson* newPerson = new cPerson();

	//std::string first;
	//std::string middle;
	//std::string last;
	//eGenderType gender;
	//int age;

	//int streetNumber;		// default = 0 
	//std::string streetName;
	//std::string streetType;
	//std::string streetDirection;

	//std::string city;
	//std::string province;
	//// N5Y 5R6  is Fanshawe's postal code
	//char postalCode[6];		// Canadian postal codes are 6 characters

	//// Social Insurance Number (Candian "... is a 9 digit number...")
	//unsigned int SIN;	// = 0

	// These all need to be made at least somewhat randomly
	// First and middle name will be chosen randomly from babyNames


	unsigned int randomIndex = rand() %  saBabyNames.getSize();
	newPerson->first = saBabyNames.getAtIndex(randomIndex).GetName();

	// The first name will also be used for gender
	//...
	// actually, I should probably use a map of some kind for the babyNames since there are names that can have different genders...
	// so either check the list for the same name with another gender (which would take a while), or change this to a map TODO
	if (saBabyNames.getAtIndex(randomIndex).GetGender() == "M")
	{
		newPerson->gender = cPerson::eGenderType::MALE;
	}
	else if (saBabyNames.getAtIndex(randomIndex).GetGender() == "F")
	{
		newPerson->gender = cPerson::eGenderType::FEMALE;
	}
	else
	{
		newPerson->gender = cPerson::eGenderType::NON_BINARY;
	}

	randomIndex = rand() % saBabyNames.getSize();
	newPerson->middle = saBabyNames.getAtIndex(randomIndex).GetName();

	// Last Name will be chosen from surnames
	randomIndex = rand() % saSurnames.getSize();
	newPerson->last = saSurnames.getAtIndex(randomIndex).GetName();

	// age is made randomly
	newPerson->age = rand() % 120;

	// Street information
	randomIndex = rand() % saStreetNames.getSize();
	newPerson->streetName = saStreetNames.getAtIndex(randomIndex).GetName();
	newPerson->streetType = saStreetNames.getAtIndex(randomIndex).GetType();
	newPerson->streetDirection = saStreetNames.getAtIndex(randomIndex).GetDirection();
	
	newPerson->streetNumber = (rand() % 9999) + 1;		// depends on the area, idk, numbers between 1 and 10000

	// City and province would be set by the user and is a little harder to randomize, so this is going to all be people in London, ON
	// (even though the street names are from San Francisco lol)
	newPerson->city = "London";
	newPerson->province = "ON";

	// N5Y 5R6  is Fanshawe's postal code
	newPerson->postalCode[0] = 'A' + rand() % 26;	// Letter
	newPerson->postalCode[1] = '0' + rand() % 10;			// Number
	newPerson->postalCode[2] = 'A' + rand() % 26;	// Letter

	newPerson->postalCode[3] = '0' + rand() % 10;			// Number
	newPerson->postalCode[4] = 'A' + rand() % 26;	// Letter
	newPerson->postalCode[5] = '0' + rand() % 10;			// Number
	
	// SIN is a 9 digit number
	newPerson->SIN = rand() % 1000000000;

	return newPerson;
}


// Here's a simple way to load the comma delimited files:
bool readCSVFile(void)
{
	// Open the file
	std::ifstream namesFile("Names_2010Census.csv");
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				std::cout << token << std::endl;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}