#pragma once
#include <iostream>
#include <string>


struct PersonalData 
{
	std::string name = "";
	std::string phone = "";
	std::string address = "";
	std::string zipCode = "";
	std::string email = "";

	bool operator==(const PersonalData& target) const 
	{
		return name == target.name &&
			phone == target.phone &&
			address == target.address &&
			zipCode == target.zipCode &&
			email == target.email;
	}
};

namespace DBConfig 
{
	static const std::string SAVEFILE = "AddressBook.csv";
}
