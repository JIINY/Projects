#include "Personal.hpp"
#include <vector>
#include <string>
#include "../Common/ResultEnums.hpp"
using namespace std;


Personal::Personal(const PersonalData& input)
{
	(void)setName(input.name);
	setPhone(input.phone);
	setAddress(input.address);
	setZipCode(input.zipCode);
	setEmail(input.email);
}


PersonalData Personal::getData() const 
{
	PersonalData p = { name_, phone_, address_, zipCode_, email_ };
	return p;
}
string Personal::getName() const { return name_; }
string Personal::getPhone() const {	return phone_; }
string Personal::getAddress() const { return address_; }
string Personal::getZipCode() const { return zipCode_; }
string Personal::getEmail() const { return email_; }


AddOperationResult Personal::setData(const PersonalData& input) 
{
	AddOperationResult nameResult = setName(input.name);
	if (nameResult != AddOperationResult::SUCCESS) { return nameResult; }

	setPhone(input.phone);
	setAddress(input.address);
	setZipCode(input.zipCode);
	setEmail(input.email);

	return AddOperationResult::SUCCESS;
}

AddOperationResult Personal::setName(const string& name) 
{ 
	if (name.empty()) { return AddOperationResult::EMPTY_NAME; }

	name_ = name;
	return AddOperationResult::SUCCESS;
}

void Personal::setPhone(const string& phone) { phone_ = phone; }
void Personal::setAddress(const string& address) { address_ = address; }
void Personal::setZipCode(const string& zipCode) { zipCode_ = zipCode; }
void Personal::setEmail(const string& email) { email_ = email; }
