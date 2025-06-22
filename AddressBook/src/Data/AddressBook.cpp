#pragma once
#include "AddressBook.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../Common/ResultEnums.hpp"
#include "Personal.hpp"
using namespace std;


//default: Public
int AddressBook::getLength() const { return static_cast<int>(personal.size()); }
int AddressBook::getLastAdd() const { return lastAdd; }
PersonalData AddressBook::getPersonalAt(int index) { return personal[index].getData(); }
string AddressBook::getNameAt(int index) const { return personal[index].getName(); }
string AddressBook::getPhoneAt(int index) const { return personal[index].getPhone(); }
string AddressBook::getAddressAt(int index) const { return personal[index].getAddress(); }
string AddressBook::getZipCodeAt(int index) const { return personal[index].getZipCode(); }
string AddressBook::getEmailAt(int index) const { return personal[index].getEmail(); }

SaveOperationResult AddressBook::saveFile(const string& filename) const {
	ofstream outFile(filename);

	if (!outFile) { //쓰기 가능한지(e.g. 폴더 권한 문제)
		return SaveOperationResult::FAIL;
	}

	for (const auto& p : personal) {
		outFile << p.getName() << ',' << p.getPhone() << ',' << p.getAddress() << ',' << p.getZipCode() << ',' << p.getEmail() << '\n';
	}
	return SaveOperationResult::SUCCESS;
}

LoadOperationResult AddressBook::loadFile(const string& filename) {
	ifstream inFile(filename);

	if (!inFile) {
		if (!filesystem::exists(filename)) {
			return LoadOperationResult::NOT_EXIST_FILE;
		}
		return LoadOperationResult::FAIL;
	}

	personal.clear();
	string line;
	while (getline(inFile, line)) {
		istringstream data(line);
		PersonalData input;
		getline(data, input.name, ',');
		getline(data, input.phone, ',');
		getline(data, input.address, ',');
		getline(data, input.zipCode, ',');
		getline(data, input.email, ',');

		Personal p(input);
		personal.push_back(p);
	}
	return LoadOperationResult::SUCCESS;
}



//add: Public
AddOperationResult AddressBook::add(const PersonalData& p) { 
	return processAdd(p);
}

//add: Protected
AddOperationResult AddressBook::processAdd(const PersonalData& p) {
	if (p.name.empty()) { return AddOperationResult::EMPTY_NAME; }

	Personal data = Personal(p);
	auto pos = lower_bound(personal.begin(), personal.end(), data,
		[](const Personal& a, const Personal& b) {
			return a.getName() < b.getName();
		});
	lastAdd = static_cast<int>(pos - personal.begin());
	this->personal.insert(pos, data);
	return AddOperationResult::SUCCESS;
}



//remove: Public
RemoveOperationResult AddressBook::remove(int index, string& name) {
	RemoveOperationResult result = processRemove(index, name);
	return result;
}

//remove: Protected
RemoveOperationResult AddressBook::processRemove(int index, string& name) {
	int length = static_cast<int>(this->personal.size());
	if (index <= 0 || index > length) { return RemoveOperationResult::WRONG_INDEX; }

	if (popPersonal(index, name)) {
		length--;
		return RemoveOperationResult::SUCCESS;
	}
	return RemoveOperationResult::FAIL;
}

bool AddressBook::popPersonal(int index, string& name) { //마찬가지로 length가공 어떻게 할 건지 맞춰서 매개변수 수정할 것
	name = personal[index - 1].getName();
	personal.erase(personal.begin() + (index - 1));
	return true;
}
