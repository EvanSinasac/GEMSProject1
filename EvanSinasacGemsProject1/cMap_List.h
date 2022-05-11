#pragma once

// I'm basing this off of the cHasMap_withList we did in class but making it specifically for persons and a list of songs

#include "cPerson.h"
#include "cSong.h"

#include "cSmartArray_Template.h"
#include "cLinkedList_Template.h"
#include "cPair_Templated.h"

class cMap_List
{
public:
	cMap_List()
	{
		this->m_AllocateSpace();
	}
	~cMap_List()
	{
	}

	static const unsigned int INITIAL_SIZE = 1024;
	unsigned int currentSize = INITIAL_SIZE;

	//typedef cPair_Templated <cPerson, cSong> keyPersonSong;
	typedef cPair_Templated <cPerson, cSmartArray_Template<cSong*>> keyPersonSASong;
	typedef cLinkedList_Template<keyPersonSASong> LLofPairs;
	cSmartArray_Template<LLofPairs*> m_theData;

	bool insertAtIndex(cPerson keyValue, cSong* theSong);
	//cSmartArray_Template<cSong*> getAtIndex(cPerson keyValue);
	//cSmartArray_Template<cSong*> getAtIndex(unsigned int keyValue);
	cSong* getAtIndex(unsigned int keyValue, unsigned int songValue);

	//unsigned int calcHashValue(cPerson keyValue);
	unsigned int calcHashValue(unsigned int keyValue);

private:
	void m_AllocateSpace(void);
	void m_ReAllocateSpace(void);
};