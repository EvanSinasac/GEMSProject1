#pragma once
#include <string>

class cBabyNames
{
public:
	cBabyNames()
	{
		this->name = "";
		this->gender = "";
	}
	~cBabyNames() {}

	void SetName(std::string n) { this->name = n; }
	std::string GetName(void) { return this->name; }

	void SetGender(std::string g) { this->gender = g; }
	std::string GetGender(void) { return this->gender; }

private:
	std::string name;
	std::string gender;

protected:

};