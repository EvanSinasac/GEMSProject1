#pragma once

// pair we did in class, going to be used to make a map type class

template <class T, class U>
class cPair_Templated
{
public:
	cPair_Templated() {};
	cPair_Templated(T first, U second)
	{
		this->First = first;
		this->Second = second;
	}
	~cPair_Templated() {};

	T First;
	U Second;
};
