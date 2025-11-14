#pragma once
#include <string>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../Data/AddressBook.hpp"


class AddressBookUI 
{
public:
    void run();
    int getLastAdd() const { return addressBook_.getLastAdd(); }
    int getLength() const { return this->addressBook_.getLength(); }
    ResultVariant getResult() const { return this->result_; }

    ResultVariant addPersonalData(const PersonalData& p);
    PersonalData getPersonalDataAt(int i) const;
    
    std::string getNameAt(int i) const { return addressBook_.getNameAt(i); }
    std::string getPhoneAt(int i) const { return addressBook_.getPhoneAt(i); }
    std::string getAddressAt(int i) const { return addressBook_.getAddressAt(i); }
    std::string getZipCodeAt(int i) const { return addressBook_.getZipCodeAt(i); }
    std::string getEmailAt(int i) const { return addressBook_.getEmailAt(i); }

    AddressBook& extractAddressBook() { return addressBook_; }
    

private:
    AddressBook addressBook_{};
    ResultVariant result_{};
};

