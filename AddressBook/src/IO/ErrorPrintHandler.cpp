#pragma once
#include "ErrorPrintHandler.hpp"
#include <iostream>
#include <string>
#include <variant>
#include <type_traits>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../UI/OutputPrintHandler.hpp"
using namespace std;


//Public
void ErrorPrintHandler::printErrorMsg(const std::variant<IntParsingResult, InputResult,
	SaveOperationResult, LoadOperationResult, AddOperationResult, RemoveOperationResult,
	MenuSelectResult, AddDataResult, AddEditResult, EditDataResult, SearchDataResult>& err) {

	setErrorMsg(err);
	if (this->errorMsg != "") {
		cout << this->errorMsg << endl;
		OutputPrintHandler::printShort2Line();
	}
}
	

//Protected
void ErrorPrintHandler::setErrorMsg(const ResultVariant& err) {

	visit([this](auto&& err) {
		using T = decay_t<decltype(err)>;
		if constexpr (is_same_v<T, InputResult>) {
			printInputErrorMsg(err);
		}
		else if constexpr (is_same_v<T, SaveOperationResult>) {
			printSaveOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, LoadOperationResult>) {
			printLoadOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddOperationResult>) {
			printAddOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, RemoveOperationResult>) {
			printRemoveOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, MenuSelectResult>) {
			printMenuSelectErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddDataResult>) {
			printAddDataErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddEditResult>) {
			printAddEditErrorMsg(err);
		}
		else if constexpr (is_same_v<T, EditDataResult>) {
			printEditDataErrorMsg(err);
		}
		else if constexpr (is_same_v<T, SearchDataResult>) {
			printSearchDataErrorMsg(err);
		}
		}, err);

}

void ErrorPrintHandler::printInputErrorMsg(const InputResult err) {
	switch (err) {
	case InputResult::WRONG_NUMBER:
		this->errorMsg = "[ERROR] �Է�: �ش� ������ ���ڸ� �Է����ּ���. -1";
		break;
	case InputResult::LENGTH_OVER:
		this->errorMsg = "[ERROR] �Է�: �ش� ������ ���ڸ� �Է����ּ���.";
		break;
	case InputResult::EMPTY_INT:
		this->errorMsg = "[ERROR] �Է�: ���ڸ� �Է��� �ּ���.";
		break;
	case InputResult::EMPTY_CHAR:
		this->errorMsg = "[ERROR] �Է�: ���ڸ� �Է��� �ּ���.";
		break;
	case InputResult::EMPTY_STRING:
		this->errorMsg = "[ERROR] �Է�: ������ �Է��� �ּ���.";
		break;
	case InputResult::EMPTY_YESNO:
		this->errorMsg = "[ERROR] �Է�: Y/N�� �Է��� �ּ���.";
		break;
	case InputResult::INVALID_STRING:
		this->errorMsg = "[ERROR] �Է�: �߸��� �Է��Դϴ�. ������ �Է��� �ּ���.";
		break;
	case InputResult::INVALID_INT:
		this->errorMsg = "[ERROR] �Է�: �߸��� �Է��Դϴ�. ���ڸ� �Է��� �ּ���.";
		break;
	case InputResult::INVALID_CHAR:
		this->errorMsg = "[ERROR] �Է�: �߸��� �Է��Դϴ�. ���ڸ� �Է��� �ּ���.";
		break;
	case InputResult::INVALID_YESNO:
		this->errorMsg = "[ERROR] �Է�: Y/N�� �Է��� �ּ���.";
		break;
	case InputResult::UNKNOWN:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �Է¿� �����߽��ϴ�.";
		break;
	case InputResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �Է¿� �����߽��ϴ�. -1";
		break;
	}
}

void ErrorPrintHandler::printMenuSelectErrorMsg(const MenuSelectResult err) {
	switch (err) {
	case MenuSelectResult::WRONG_INDEX:
		this->errorMsg = "[ERROR] �Է�: ���ϴ� �޴� ��ȣ�� �Է��� �ּ���.";
		break;
	case MenuSelectResult::SUCCESS:
		this->errorMsg = "";
		break;
	case MenuSelectResult::EMPTY_ADDRESSBOOK:
		this->errorMsg = "[ERROR] �ּҷ��� ��� �ֽ��ϴ�.";
		break;
	default:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �޴� ���ÿ� �����߽��ϴ�. -1";
		break;
	}
}

void ErrorPrintHandler::printAddOperationErrorMsg(const AddOperationResult err) {
	switch (err) {
	case AddOperationResult::FAIL:
		this->errorMsg = "[ERROR] ����: �� �� ���� ������ �߰����� ���߽��ϴ�.";
		break;
	case AddOperationResult::EMPTY_NAME:
		this->errorMsg = "[ERROR] �Է�: �̸��� �Է��� �ּ���.";
		break;
	case AddOperationResult::UNKNOWN:
		this->errorMsg = "[ERROR] UI: �� �� ���� ������ �߰����� ���߽��ϴ�.";
		break;
	case AddOperationResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] ����: �� �� ���� ������ �߰����� ���߽��ϴ�. -1";
		break;
	}
}


void ErrorPrintHandler::printRemoveOperationErrorMsg(const RemoveOperationResult err) {
	switch (err) {
	case RemoveOperationResult::WRONG_INDEX:
		cout << "[ERROR] �߸��� ��ȣ�Դϴ�." << endl;
		break;

	case RemoveOperationResult::FAIL:
		cout << "[ERROR] �� �� ���� ������ �������� ���߽��ϴ�." << endl;
		break;
	case RemoveOperationResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		break;
	}
}

void ErrorPrintHandler::printAddDataErrorMsg(const AddDataResult err) {
	switch (err) {
	case AddDataResult::EMPTY_NAME:
		this->errorMsg = "[ERROR] �Է�: �ּҷ� �߰��� ���� �̸� �Է��� �ʿ��մϴ�.";
		break;
	case AddDataResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �ּҷ� �߰��� �����߽��ϴ�. -1";
		break;
	}
}

void ErrorPrintHandler::printAddEditErrorMsg(const AddEditResult err){
	switch (err) {
	case AddEditResult::EMPTY_NAME:
		this->errorMsg = "[ERROR] �Է�: �ּҷ� �߰��� ���� �̸� �Է��� �ʿ��մϴ�.";
		break;
	case AddEditResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �ּҷ� �߰� ������ �����߽��ϴ�. -1";
		break;
	}
}

void ErrorPrintHandler::printEditDataErrorMsg(const EditDataResult err){
	switch (err) {
	case EditDataResult::EMPTY_NAME:
		this->errorMsg = "[ERROR] �Է�: �ּҷϿ��� �̸� �Է��� �ʿ��մϴ�.";
		break;
	case EditDataResult::SUCCESS:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] �Է�: �� �� ���� ������ �ּҷ� ������ �����߽��ϴ�. -1";
		break;
	}
}

void ErrorPrintHandler::printSaveOperationErrorMsg(const SaveOperationResult err) {
	switch (err) {
	case SaveOperationResult::SUCCESS:
		this->errorMsg = "";
		break;
	case SaveOperationResult::FAIL:
		this->errorMsg = "[ERROR] ����: ���忡 �����߽��ϴ�.";
		break;
	default:
		this->errorMsg = "[ERROR] ����: �� �� ���� ������ ���忡 �����߽��ϴ�.-1";
		break;
	}
}

void ErrorPrintHandler::printLoadOperationErrorMsg(const LoadOperationResult err) {
	switch (err) {
	case LoadOperationResult::SUCCESS:
		this->errorMsg = "";
		break;
	case LoadOperationResult::FAIL:
		this->errorMsg = "[ERROR] �ε�: �ҷ����⿡ �����߽��ϴ�.";
		break;
	case LoadOperationResult::NOT_EXIST_FILE:
		this->errorMsg = "";
		break;
	default:
		this->errorMsg = "[ERROR] �ε�: �� �� ���� ������ �ҷ����⿡ �����߽��ϴ�.-1";
		break;
	}
}

void ErrorPrintHandler::printSearchDataErrorMsg(const SearchDataResult err) {
	switch (err) {
	case SearchDataResult::SUCCESS:
		this->errorMsg = "";
		break;
	case SearchDataResult::EMPTY_ITEM:
		this->errorMsg = "[ERROR] ã��: �����ϴ� �����͸� ã�� �� �������ϴ�.";
		break;
	default:
		this->errorMsg = "[ERROR] ã��: �� �� ���� ������ ã�⿡ �����߽��ϴ�. -1";
		break;
	}
}
