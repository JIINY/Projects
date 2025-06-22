#pragma once
#include <string>
#include "../Common/DataType.hpp"
using namespace std;


class Personal {
public:
	Personal(const PersonalData& input);

	void setData(const PersonalData& input);
	void setName(const string& input);
	void setPhone(const string& input);
	void setAddress(const string& input);
	void setZipCode(const string& input);
	void setEmail(const string& input);

	PersonalData getData() const;
	string getName() const;
	string getPhone() const;
	string getAddress() const;
	string getZipCode() const;
	string getEmail() const;

private:
	string name;
	string phone;
	string address;
	string zipCode;
	string email;
};
