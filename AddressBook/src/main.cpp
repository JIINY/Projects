#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include "Common/ResultEnums.hpp"
#include "Common/VariantUtils.hpp"
#include "IO/ErrorPrintHandler.hpp"
#include "Data/AddressBook.hpp"
#include "UI/AddressBookUI.hpp"
using namespace std;


int main(void) {
	SetConsoleCP(CP_UTF8); //windows 콘솔 설정
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, ".UTF8"); //C++ 런타임(cout 등) 설정

	AddressBookUI ui;
	ErrorPrintHandler errorMsgH;
	AddressBook& b = ui.extractAddressBook();

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

