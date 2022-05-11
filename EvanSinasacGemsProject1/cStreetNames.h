#pragma once

#include <string>

class cStreetNames
{
public:
	cStreetNames()
	{
		this->streetName = "";
		this->streetType = "";
		this->streetDirection = "";
	}

	~cStreetNames() {}

	void SetName(std::string n) { this->streetName = n; }
	std::string GetName(void) { return this->streetName; }

	void SetType(std::string t) { this->streetType = t; }
	std::string GetType(void) { return this->streetType; }

	void SetDirection(std::string d) { this->streetDirection = d; }
	std::string GetDirection(void) { return this->streetDirection; }

private:
	std::string streetName;
	std::string streetType;
	std::string streetDirection;

protected:

};