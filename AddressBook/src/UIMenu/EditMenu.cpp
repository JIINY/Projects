#include "EditMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
#include "../Common/VariantUtils.hpp"//log
using namespace std;


optional<PersonalData> EditMenu::run(AddressBookUI& bookUI, const PersonalData& dataToEdit)
{
	ContextData context;
	EditPhase currentPhase = EditPhase::EditStart;
	context.p = dataToEdit;
	context.err = nullopt;
	context.menu = -1;

	while (currentPhase != EditPhase::ExitSuccess && currentPhase != EditPhase::ExitCancel) 
	{
		//그리기
		switch (currentPhase) {
		case EditPhase::EditStart:
		{
			frame_ = uiMsgH_.editTitle();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.personalEdit(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editConfirm();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editInput(context.err);
			frame_(errorMsgH_);
			break;
		}
		case EditPhase::EditItem:
		{
			processEditData(context);
			break;
		}
		case EditPhase::EditCancle:
		{
			frame_ = uiMsgH_.editTitle();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.personalEdit(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editConfirm();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.cancle(context.err, CancleType::Edit);
			frame_(errorMsgH_);
			break;
		}
		default:
			break;
		}


		//처리
		EditPhase nextPhase = currentPhase;
		switch (currentPhase){
		case EditPhase::EditStart: 
		{
			nextPhase = onEditStart(context);
			break;
		}
		case EditPhase::EditItem:
		{
			nextPhase = onEditItem(context);
			break;
		}
		case EditPhase::EditCancle: 
		{
			nextPhase = onEditCancle(context);
			break;
		}
		default:
			break;
		}


		//화면 정리 및 상태 전이
		UIUtils::clearScreen();
		currentPhase = nextPhase;
	}

	if (currentPhase == EditPhase::ExitSuccess)
	{
		context.err = nullopt;
		return context.p;
	}

	return std::nullopt;
}

void EditMenu::processEditData(ContextData& context)
{
	switch (context.menu)
	{
	case 1:
	{
		frame_ = uiMsgH_.editName(context.err);
		frame_(errorMsgH_);
		break;
	}
	case 2:
	{
		frame_ = uiMsgH_.editPhone(context.err);
		frame_(errorMsgH_);
		break;
	}
	case 3:
	{
		frame_ = uiMsgH_.editAddress(context.err);
		frame_(errorMsgH_);
		break;
	}
	case 4:
	{
		frame_ = uiMsgH_.editZipCode(context.err);
		frame_(errorMsgH_);
		break;
	}
	case 5:
	{
		frame_ = uiMsgH_.editEmail(context.err);
		frame_(errorMsgH_);
		break;
	}
	case 6:
	{
		ui_.clearScreen();
		break;
	}
	case 9:
	{
		break;
	}
	}
}

EditPhase EditMenu::onEditStart(ContextData& context) 
{
	context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return EditPhase::EditStart;
	}

	//다음 상태 결정
	context.err = nullopt;
	if (context.menu == 0)
	{
		return EditPhase::EditCancle;
	}
	if (context.menu == 9)
	{
		return EditPhase::ExitSuccess;
	}
	if (context.menu >= 1 && context.menu <= 6)
	{
		return EditPhase::EditItem;
	}

	lastError_ = MenuSelectResult::WRONG_INDEX;
	context.err = wrapVariant<ResultVariant>(lastError_);
	return EditPhase::EditStart;
}

EditPhase EditMenu::onEditItem(ContextData& context)
{
	if (context.menu == -1 && context.err.has_value() && holds_alternative<InputResult>(*context.err)) //InputResult인지 확인
	{
		if (get<InputResult>(*context.err) != InputResult::SUCCESS)
		{
			return EditPhase::EditStart;
		}
	}

	switch (context.menu){
	case 1:
	{
		string s = inputH_.getString(StringRule::EmptyDisallow);
		lastError_ = inputH_.getLastError();
		context.err = wrapVariant<ResultVariant>(lastError_);

		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS))
		{
			lastError_ = EditDataResult::EMPTY_NAME;
			context.err = wrapVariant<ResultVariant>(lastError_);
			return EditPhase::EditStart;
		}

		context.p.name = s;
		context.err = nullopt;
		break;
	}
	case 2:
	{
		string s = inputH_.getString(StringRule::EmptyAllow);
		context.p.phone = s;
		context.err = wrapVariant<ResultVariant>(inputH_.getLastError());
		break;
	}
	case 3:
	{
		string s = inputH_.getString(StringRule::EmptyAllow);
		context.p.address = s;
		context.err = wrapVariant<ResultVariant>(inputH_.getLastError());
		break;
	}
	case 4:
	{
		string s = inputH_.getString(StringRule::EmptyAllow);
		context.p.zipCode = s;
		context.err = wrapVariant<ResultVariant>(inputH_.getLastError());
		break;
	}
	case 5:
	{
		string s = inputH_.getString(StringRule::EmptyAllow);
		context.p.email = s;
		context.err = wrapVariant<ResultVariant>(inputH_.getLastError());
		break;
	}
	case 6:
	{
		context.p = ui_.processInputPersonalData(OutputPrintHandler::printAddEditTitle);
		context.err = nullopt;
		break;
	}
	default:
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
		break;
	}

	return EditPhase::EditStart;
}

EditPhase EditMenu::onEditCancle(ContextData& context)
{
	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return EditPhase::EditCancle;
	}

	context.err = nullopt;
	if (yesNo) 
	{
		return EditPhase::ExitCancel;
	}

	return EditPhase::EditStart;
}
