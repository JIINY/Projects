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

	void setPhone(const std::string& phone) { phone_ = phone; }
	void setAddress(const std::string& address) { address_ = address; }
	void setZipCode(const std::string& zipCode) { zipCode_ = zipCode; }
	void setEmail(const std::string& email) { email_ = email; }

	PersonalData getData() const;
	std::string getName() const { return name_; }
	std::string getPhone() const { return phone_; }
	std::string getAddress() const { return address_; }
	std::string getZipCode() const { return zipCode_; }
	std::string getEmail() const { return email_; }

private:
	std::string name_ = "";
	std::string phone_ = "";
	std::string address_ = "";
	std::string zipCode_ = "";
	std::string email_ = "";
};

