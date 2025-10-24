#include <iostream>
#include <string>
#include "Common/ResultEnums.hpp"
#include "Common/VariantUtils.hpp"
#include "IO/ErrorPrintHandler.hpp"
#include "Data/AddressBook.hpp"
#include "UI/UICommonShard.hpp"
#include "UI/AddressBookUI.hpp"
using namespace std;


int main(void) {
	AddressBookUI ui;
	ErrorPrintHandler errorMsgH;
	AddressBook& b = ui.extractAddressBook();
	book = &ui; //UICommonShard

	LoadOperationResult loadResult = b.loadFile("AddressBook.csv");
	if (loadResult != LoadOperationResult::SUCCESS) {
		errorMsgH.printErrorMsg(wrapVariant<ResultVariant>(loadResult));
	}

	ui.run();

	SaveOperationResult saveResult = b.saveFile("AddressBook.csv");
	if (saveResult != SaveOperationResult::SUCCESS) {
		errorMsgH.printErrorMsg(wrapVariant<ResultVariant>(saveResult));
	}

	return 0;
}
