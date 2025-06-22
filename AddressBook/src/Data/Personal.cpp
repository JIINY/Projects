#include "Personal.hpp"
#include <vector>
#include <string>
using namespace std;


Personal::Personal(const PersonalData& input)
: name(input.name), phone(input.phone), address(input.address), zipCode(input.zipCode), email(input.email) {}


PersonalData Personal::getData() const {
	PersonalData p = { name, phone, address, zipCode, email };
	return p;
}
string Personal::getName() const { return name; }
string Personal::getPhone() const {	return phone; }
string Personal::getAddress() const { return address; }
string Personal::getZipCode() const { return zipCode; }
string Personal::getEmail() const { return email; }


void Personal::setData(const PersonalData& input) {
	if (input.name != "") { name = input.name; }
	if (input.phone != "") { phone = input.phone; }
	if (input.address != "") { address = input.address; }
	if (input.zipCode != "") { zipCode = input.zipCode; }
	if (input.email != "") { email = input.email; }
}

void Personal::setName(const string& input) { name = input; }
void Personal::setPhone(const string& input) {}
void Personal::setAddress(const string& input) {}
void Personal::setZipCode(const string& input) {}
void Personal::setEmail(const string& input) {}
