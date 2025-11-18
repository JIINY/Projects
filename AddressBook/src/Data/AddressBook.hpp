#pragma once
#include <vector>
#include <utility>
#include <string>
#include "../Common/ResultEnums.hpp"
#include "Personal.hpp"


class AddressBook 
{
public:
	int getLength() const { return static_cast<int>(personal_.size()); }
	int getLastAdd() const { return lastAdd_; }
	PersonalData getPersonalAt(int index) const { return personal_[index].getData(); }
	std::string getNameAt(int index) const { return personal_[index].getName(); }
	std::string getPhoneAt(int index) const { return personal_[index].getPhone(); }
	std::string getAddressAt(int index) const { return personal_[index].getAddress(); }
	std::string getZipCodeAt(int index) const { return personal_[index].getZipCode(); }
	std::string getEmailAt(int index) const { return personal_[index].getEmail(); }

	SaveOperationResult saveFile(const std::string& filename) const;
	LoadOperationResult loadFile(const std::string& filename);

	AddOperationResult add(const PersonalData& p);
	RemoveOperationResult remove(int index, std::string& name);
	RemoveOperationResult removeAll(const std::string& filename);
	AddOperationResult edit(int originalIndex, const PersonalData& newData);

	std::vector<std::pair<PersonalData, int>> searchByName(const std::string& query) const;
	std::vector<std::pair<PersonalData, int>> searchByPhone(const std::string& query) const;
	std::vector<std::pair<PersonalData, int>> searchByAddress(const std::string& query) const;
	std::vector<std::pair<PersonalData, int>> searchByZipCode(const std::string& query) const;
	std::vector<std::pair<PersonalData, int>> searchByEmail(const std::string& query) const;
	int findIndexByData(const PersonalData& data) const;

protected:
	AddOperationResult processAdd(const PersonalData& p);
	RemoveOperationResult processRemove(int index, std::string& name);
	RemoveOperationResult processRemoveAll(const std::string& filename);

	bool popPersonal(int index, std::string& name);


private:
	int lastAdd_ = -1;
	std::vector<Personal> personal_{};
};

