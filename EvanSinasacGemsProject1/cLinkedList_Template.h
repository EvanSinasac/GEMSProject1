#pragma once

// Linked List we did in class, going to be used to make a map

template <class Q>
class cLinkedList_Template
{
public:
	cLinkedList_Template()
	{
		this->pHead = nullptr;	// Can't use NULL anymore because it's literally character '0'
		this->pCurrent = this->pHead;
		//	this->pCurrent = NULL;
	}
	~cLinkedList_Template()
	{

	}

	// This is holding one instance of the information
	class cNode
	{
	public:
		cNode()
		{
			this->pNext = nullptr;
			this->pPrior = nullptr;
		}
		Q theData;
		cNode* pNext;
		cNode* pPrior;
	};

	cNode* pHead;
	cNode* pCurrent;
	// cNode* pTail;

	bool bIsEmpty(void)
	{
		if (this->pHead == nullptr)
		{
			return true;
		}
		return false;
	}

	void insertAtCurrent(Q thePerson)
	{
		// Check if this is the 1st node
		if (this->pHead == nullptr)
		{
			cNode* pNewNode = new cNode;
			pNewNode->theData = thePerson;	// Copy the person

			this->pHead = pNewNode;
			this->pCurrent = pNewNode;
		}
		else
		{	// Isn't the 1st node
			// We are REPLACING the current node with this node.
			// Convention is we "move" the current node "down" towards the tail

			cNode* pNewNode = new cNode;
			pNewNode->theData = thePerson;	// Copy the person

											// Copy the pointer for the old node
			cNode* pOldCurrent = this->pCurrent;

			// 1. Point the Current node to this new node
			this->pCurrent = pNewNode;

			// 2. Point the "next" node to the "old" current node
			pNewNode->pNext = pOldCurrent;

			// 3. Update the new nodes "prior" the old node's prior
			if (pOldCurrent->pPrior != nullptr)
			{
				pNewNode->pPrior = pOldCurrent->pPrior;

				// 3a. Update the priors "next" node to the new node
				if (pNewNode->pPrior->pNext != nullptr)
				{
					pNewNode->pPrior->pNext = pNewNode;
				}
			}//if ( pOldCurrent->pPrior != NULL )


			 // 4. Point the "old current" node to this node as well (pPrior)
			pOldCurrent->pPrior = pNewNode;

			// 4. See if the old node was the head node
			// (See if the pointers match)
			if (this->pHead == pOldCurrent)
			{	// Yes, it was the old head node, so update it
				this->pHead = pNewNode;
			}

		}

		return;
	}

	// Deletes at the current node
	// TODO: void deleteCurrent(void);

	Q getAtCurrent(void)
	{
		// Copy the person back:
		Q personToReturn = this->pCurrent->theData;

		return personToReturn;
	}

	// Returns true if successful 
	bool moveToNext(void)
	{
		// Will use the convention that returns true if you can move.
		// i.e. if there is a "next" node to move to.
		// Or: if there ISN'T a node to move (no "next node") 
		//	we just stay on the current node.
		// (we never have a current that is pointing to NULL)

		// Possible edge case "gotchas":
		if (this->pCurrent == nullptr)
		{	// 1. There isn't anything in the list, yet
			//    (i.e. the current IS null)
			// Do Nothing, return false
			return false;
		}

		if (this->pCurrent->pNext == nullptr)
		{	// 3. There ISN'T anything after this node
			// CAN'T move "next"
			return false;
		}

		// Everything is "Gucci" (is A-OK, all right, rainbows and sunshine)
		// 2. There IS something after this node
		// Using the current node, see what it's pointing to
		this->pCurrent = this->pCurrent->pNext;

		return true;
	}

	bool moveToPrior(void)
	{
		// Same convention as moveToNext()

		// Possible edge case "gotchas":
		if (this->pCurrent == nullptr)
		{	// 1. There isn't anything in the list, yet
			//    (i.e. the current IS null)
			// Do Nothing, return false
			return false;
		}

		if (this->pCurrent->pPrior == nullptr)
		{	// 3. There ISN'T anything before this node
			// CAN'T move "prior" or previous
			return false;
		}

		// Everything is "Gucci" (is A-OK, all right, rainbows and sunshine)
		// 2. There IS something before this node
		// Using the current node, see what it's pointing to
		this->pCurrent = this->pCurrent->pPrior;

		return true;
	}


	void moveToHead(void)
	{
		this->pCurrent = this->pHead;
		return;
	}

	//TODO: void moveToTail(void);

	// You could also have helpful naviation methods like this:
	// Question: what happens if these fail?
	//	Return false?
	//	Move back to where we were?
	//	Keep track of where we were to move back if we want? 
	//	(like calling "ResetCurrent()" or something?)
	void moveNext(unsigned int numberOfNodesToMove)
	{
		unsigned int count = 0;
		while (count != numberOfNodesToMove)
		{
			this->moveToNext();
			count++;
		}
		return;
	}

	void movePrior(unsigned int numberOfNodesToMove)
	{
		unsigned int count = 0;
		while (count != numberOfNodesToMove)
		{
			this->moveToPrior();
			count++;
		}
		return;
	}


	// Optional stuff, maybe:
	//	getSize();
	//  clear();
	//	makeCoffee();

};
