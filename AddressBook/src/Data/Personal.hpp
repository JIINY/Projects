#pragma once
#include <string>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"


class Personal 
{
public:
	Personal() = default;
	Personal(const PersonalData& input);

	AddOperationResult setData(const PersonalData& data);
	AddOperationResult setName(const std::string& name);
	void setPhone(const std::string& phone);
	void setAddress(const std::string& address);
	void setZipCode(const std::string& zipCode);
	void setEmail(const std::string& email);

	PersonalData getData() const;
	std::string getName() const;
	std::string getPhone() const;
	std::string getAddress() const;
	std::string getZipCode() const;
	std::string getEmail() const;

private:
	std::string name_;
	std::string phone_;
	std::string address_;
	std::string zipCode_;
	std::string email_;
};
