#pragma once
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../Data/AddressBook.hpp"


class AddressBookUI {
public:
    void run();
    int getLastAdd() const;
    int getLength() const { return this->addressBook.getLength(); }
    ResultVariant getLastError() const;

    ResultVariant addPersonalData(const PersonalData& p);
    PersonalData getPersonalDataAt(int i);
    string getNameAt(int i) const;
    string getPhoneAt(int i) const;
    string getAddressAt(int i) const;
    string getZipCodeAt(int i) const;
    string getEmailAt(int i) const;

    AddressBook& extractAddressBook();
    

private:
    AddressBook addressBook;
    ResultVariant lastError;
};
