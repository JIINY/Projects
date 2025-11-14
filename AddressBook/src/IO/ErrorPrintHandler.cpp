#include "ErrorPrintHandler.hpp"
#include <iostream>
#include <string>
#include <variant>
#include <type_traits>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "../UI/OutputPrintHandler.hpp"
using namespace std;


void ErrorPrintHandler::printErrorMsg(const std::variant<InputResult,
	SaveOperationResult, LoadOperationResult, AddOperationResult, RemoveOperationResult,
	MenuSelectResult, AddDataResult, AddEditResult, EditDataResult, SearchDataResult>& err) 
{
	setErrorMsg(err);
	if (this->errorMsg_ != "") 
	{
		cout << this->errorMsg_ << endl;
		OutputPrintHandler::printShort2Line();
	}
}
	

//Protected
void ErrorPrintHandler::setErrorMsg(const ResultVariant& err) 
{
	visit([this](auto&& err){
		using T = decay_t<decltype(err)>;
		if constexpr (is_same_v<T, InputResult>) 
		{
			printInputErrorMsg(err);
		}
		else if constexpr (is_same_v<T, SaveOperationResult>) 
		{
			printSaveOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, LoadOperationResult>) 
		{
			printLoadOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddOperationResult>) 
		{
			printAddOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, RemoveOperationResult>) 
		{
			printRemoveOperationErrorMsg(err);
		}
		else if constexpr (is_same_v<T, MenuSelectResult>) 
		{
			printMenuSelectErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddDataResult>) 
		{
			printAddDataErrorMsg(err);
		}
		else if constexpr (is_same_v<T, AddEditResult>) 
		{
			printAddEditErrorMsg(err);
		}
		else if constexpr (is_same_v<T, EditDataResult>) 
		{
			printEditDataErrorMsg(err);
		}
		else if constexpr (is_same_v<T, SearchDataResult>) 
		{
			printSearchDataErrorMsg(err);
		}}, err);
}

void ErrorPrintHandler::printInputErrorMsg(const InputResult err) 
{
	switch (err) 
	{
	case InputResult::WRONG_NUMBER:
		this->errorMsg_ = "[ERROR] 입력: 해당 범위의 숫자를 입력해주세요. -1";
		break;
	case InputResult::LENGTH_OVER:
		this->errorMsg_ = "[ERROR] 입력: 해당 범위의 숫자를 입력해주세요.";
		break;
	case InputResult::EMPTY_INT:
		this->errorMsg_ = "[ERROR] 입력: 숫자를 입력해 주세요.";
		break;
	case InputResult::EMPTY_CHAR:
		this->errorMsg_ = "[ERROR] 입력: 문자를 입력해 주세요.";
		break;
	case InputResult::EMPTY_STRING:
		this->errorMsg_ = "[ERROR] 입력: 문장을 입력해 주세요.";
		break;
	case InputResult::EMPTY_YESNO:
		this->errorMsg_ = "[ERROR] 입력: Y/N를 입력해 주세요.";
		break;
	case InputResult::INVALID_STRING:
		this->errorMsg_ = "[ERROR] 입력: 잘못된 입력입니다. 문장을 입력해 주세요.";
		break;
	case InputResult::INVALID_INT:
		this->errorMsg_ = "[ERROR] 입력: 잘못된 입력입니다. 숫자를 입력해 주세요.";
		break;
	case InputResult::INVALID_CHAR:
		this->errorMsg_ = "[ERROR] 입력: 잘못된 입력입니다. 문자를 입력해 주세요.";
		break;
	case InputResult::INVALID_YESNO:
		this->errorMsg_ = "[ERROR] 입력: Y/N를 입력해 주세요.";
		break;
	case InputResult::UNKNOWN:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 입력에 실패했습니다.";
		break;
	case InputResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 입력에 실패했습니다. -1";
		break;
	}
}

void ErrorPrintHandler::printMenuSelectErrorMsg(const MenuSelectResult err) 
{
	switch (err) 
	{
	case MenuSelectResult::WRONG_INDEX:
		this->errorMsg_ = "[ERROR] 입력: 원하는 메뉴 번호를 입력해 주세요.";
		break;
	case MenuSelectResult::WRONG_COMMAND:
		this->errorMsg_ = "[ERROR] 입력: 유효한 명령어 키를 입력해 주세요.";
		break;
	case MenuSelectResult::PAGE_START:
		this->errorMsg_ = "[ERROR] 입력: 첫 페이지입니다.";
		break;
	case MenuSelectResult::PAGE_END:
		this->errorMsg_ = "[ERROR] 입력: 마지막 페이지입니다.";
		break;
	case MenuSelectResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	case MenuSelectResult::EMPTY_ADDRESSBOOK:
		this->errorMsg_ = "[ERROR] 주소록이 비어 있습니다.";
		break;
	default:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 메뉴 선택에 실패했습니다. -1";
		break;
	}
}

void ErrorPrintHandler::printAddOperationErrorMsg(const AddOperationResult err) 
{
	switch (err) 
	{
	case AddOperationResult::FAIL:
		this->errorMsg_ = "[ERROR] 로직: 알 수 없는 이유로 추가하지 못했습니다.";
		break;
	case AddOperationResult::EMPTY_NAME:
		this->errorMsg_ = "[ERROR] 입력: 이름을 입력해 주세요.";
		break;
	case AddOperationResult::UNKNOWN:
		this->errorMsg_ = "[ERROR] UI: 알 수 없는 이유로 추가하지 못했습니다.";
		break;
	case AddOperationResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 로직: 알 수 없는 이유로 추가하지 못했습니다. -1";
		break;
	}
}


void ErrorPrintHandler::printRemoveOperationErrorMsg(const RemoveOperationResult err) 
{
	switch (err) 
	{
	case RemoveOperationResult::WRONG_INDEX:
		this->errorMsg_ = "[ERROR] 잘못된 번호입니다.";
		break;
	case RemoveOperationResult::FAIL:
		this->errorMsg_ = "[ERROR] 알 수 없는 이유로 삭제하지 못했습니다.";
		break;
	case RemoveOperationResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		break;
	}
}

void ErrorPrintHandler::printAddDataErrorMsg(const AddDataResult err) 
{
	switch (err) 
	{
	case AddDataResult::EMPTY_NAME:
		this->errorMsg_ = "[ERROR] 입력: 주소록 추가를 위해 이름 입력이 필요합니다.";
		break;
	case AddDataResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 주소록 추가에 실패했습니다. -1";
		break;
	}
}

void ErrorPrintHandler::printAddEditErrorMsg(const AddEditResult err)
{
	switch (err) 
	{
	case AddEditResult::EMPTY_NAME:
		this->errorMsg_ = "[ERROR] 입력: 주소록 추가를 위해 이름 입력이 필요합니다.";
		break;
	case AddEditResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 주소록 추가 수정에 실패했습니다. -1";
		break;
	}
}

void ErrorPrintHandler::printEditDataErrorMsg(const EditDataResult err)
{
	switch (err) 
	{
	case EditDataResult::EMPTY_NAME:
		this->errorMsg_ = "[ERROR] 입력: 주소록에는 이름 입력이 필요합니다.";
		break;
	case EditDataResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 입력: 알 수 없는 이유로 주소록 수정에 실패했습니다. -1";
		break;
	}
}

void ErrorPrintHandler::printSaveOperationErrorMsg(const SaveOperationResult err) 
{
	switch (err) 
	{
	case SaveOperationResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	case SaveOperationResult::FAIL:
		this->errorMsg_ = "[ERROR] 저장: 저장에 실패했습니다.";
		break;
	default:
		this->errorMsg_ = "[ERROR] 저장: 알 수 없는 이유로 저장에 실패했습니다.-1";
		break;
	}
}

void ErrorPrintHandler::printLoadOperationErrorMsg(const LoadOperationResult err) 
{
	switch (err) 
	{
	case LoadOperationResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	case LoadOperationResult::FAIL:
		this->errorMsg_ = "[ERROR] 로드: 불러오기에 실패했습니다.";
		break;
	case LoadOperationResult::NOT_EXIST_FILE:
		this->errorMsg_ = "";
		break;
	default:
		this->errorMsg_ = "[ERROR] 로드: 알 수 없는 이유로 불러오기에 실패했습니다.-1";
		break;
	}
}

void ErrorPrintHandler::printSearchDataErrorMsg(const SearchDataResult err) 
{
	switch (err) 
	{
	case SearchDataResult::SUCCESS:
		this->errorMsg_ = "";
		break;
	case SearchDataResult::EMPTY_ITEM:
		this->errorMsg_ = "[ERROR] 찾기: 포함하는 데이터를 찾을 수 없었습니다.";
		break;
	default:
		this->errorMsg_ = "[ERROR] 찾기: 알 수 없는 이유로 찾기에 실패했습니다. -1";
		break;
	}
}

