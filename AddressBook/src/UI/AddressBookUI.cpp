#include "AddressBookUI.hpp"
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../Data/AddressBook.hpp"
#include "../UIMenu/MainMenu.hpp"
using namespace std;


void AddressBookUI::run() 
{ 
	MainMenu main;
	main.run(*this);
}

ResultVariant AddressBookUI::addPersonalData(const PersonalData& p) 
{
	AddOperationResult err = addressBook_.add(p);
	return wrapVariant<ResultVariant>(err);
}

PersonalData AddressBookUI::getPersonalDataAt(int i) const 
{
	PersonalData p = addressBook_.getPersonalAt(i);
	return p;
}


