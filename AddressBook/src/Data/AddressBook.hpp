#pragma once
#include <vector>
#include <string>
#include "../Common/ResultEnums.hpp"
#include "Personal.hpp"


class AddressBook {
public:
	int getLength() const;
	int getLastAdd() const;
	PersonalData getPersonalAt(int index);
	string getNameAt(int index) const;
	string getPhoneAt(int index) const;
	string getAddressAt(int index) const;
	string getZipCodeAt(int index) const;
	string getEmailAt(int index) const;

	SaveOperationResult saveFile(const std::string& filename) const;
	LoadOperationResult loadFile(const std::string& filename);

	AddOperationResult add(const PersonalData& p);
	RemoveOperationResult remove(int index, string& name);



protected:
	AddOperationResult processAdd(const PersonalData& p);




	RemoveOperationResult processRemove(int index, string& name);

	bool popPersonal(int index, string& name);


private:
	int lastAdd = -1;
	vector<Personal> personal;
};
