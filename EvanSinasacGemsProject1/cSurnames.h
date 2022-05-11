#pragma once

#include <string>


class cSurnames
{
public:
	cSurnames()
	{
		this->name = "";
	}
	~cSurnames() {}

	void SetName(std::string n) { this->name = n; }
	std::string GetName(void) { return this->name; }

private:
	std::string name;
	// Don't think I need anything else but I'm making this in case I do

protected:


};