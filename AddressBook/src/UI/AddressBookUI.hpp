#pragma once
#include <string>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../Data/AddressBook.hpp"


class AddressBookUI 
{
public:
    void run();
    int getLastAdd() const;
    int getLength() const { return this->addressBook.getLength(); }
    ResultVariant getLastError() const;

    ResultVariant addPersonalData(const PersonalData& p);
    PersonalData getPersonalDataAt(int i) const;
    std::string getNameAt(int i) const;
    std::string getPhoneAt(int i) const;
    std::string getAddressAt(int i) const;
    std::string getZipCodeAt(int i) const;
    std::string getEmailAt(int i) const;

    AddressBook& extractAddressBook();
    

private:
    AddressBook addressBook;
    ResultVariant lastError;
};
