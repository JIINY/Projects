#include "AddressBookUI.hpp"
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../Data/AddressBook.hpp"
#include "../UIMenu/MainMenu.hpp"
using namespace std;


//Public
void AddressBookUI::run() { 
	MainMenu main;
	main.run();
}
int AddressBookUI::getLastAdd() const {
	return addressBook.getLastAdd();
}

ResultVariant AddressBookUI::getLastError() const { return this->lastError; }

ResultVariant AddressBookUI::addPersonalData(const PersonalData& p) {
	AddOperationResult err = addressBook.add(p);
	return wrapVariant<ResultVariant>(err);
}

PersonalData AddressBookUI::getPersonalDataAt(int i) {
	PersonalData p = addressBook.getPersonalAt(i);
	return p;
}

string AddressBookUI::getNameAt(int i) const { return addressBook.getNameAt(i); }
string AddressBookUI::getPhoneAt(int i) const { return addressBook.getPhoneAt(i); }
string AddressBookUI::getAddressAt(int i) const { return addressBook.getAddressAt(i); }
string AddressBookUI::getZipCodeAt(int i) const { return addressBook.getZipCodeAt(i); }
string AddressBookUI::getEmailAt(int i) const { return addressBook.getEmailAt(i); }

AddressBook& AddressBookUI::extractAddressBook() {
	return addressBook;
}

/*
	case RemoveOperationResult::SUCCESS: //���� ó���� ����
		cout << "[�Ϸ�] �ּҷϿ��� " << index << " " << name << "�� �����Ǿ����ϴ�." << endl;
		break;
*/
