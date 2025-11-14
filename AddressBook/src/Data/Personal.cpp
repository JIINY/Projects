#include "Personal.hpp"
#include <vector>
#include <string>
#include "../Common/ResultEnums.hpp"
#include "../Common/DataType.hpp"
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

