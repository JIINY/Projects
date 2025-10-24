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
	context.p = dataToEdit;
	context.phase = wrapVariant<PhaseVariant>(EditPhase::EditStart);
	context.err = nullopt;
	context.menu = -1;

	processEditMenu(bookUI, context);

	EditPhase result = unwrapVariant<EditPhase>(context.phase);
	if (result == EditPhase::ExitSuccess) { return context.p; }

	return std::nullopt;
}

void EditMenu::processEditMenu(AddressBookUI& bookUI, ContextData& context)
{
	while (true) 
	{
		EditPhase phase = unwrapVariant<EditPhase>(context.phase);

		switch (phase)
		{
		case(EditPhase::EditStart):
		{
			frame_ = uiMsgH_.editTitle();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.personalEdit(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editConfirm();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editInput(context.err);
			frame_(errorMsgH_);

			//입력 받기
			context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
			lastError_ = inputH_.getLastError();
			if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
			{
				context.err = wrapVariant<ResultVariant>(lastError_);
				break;
			}

			//다음 상태 결정
			context.err = nullopt;
			if (context.menu == 0) 
			{
				context.phase = wrapVariant<PhaseVariant>(EditPhase::EditCancle);
			}
			else if (context.menu == 9)
			{
				context.phase = wrapVariant<PhaseVariant>(EditPhase::ExitSuccess);
			}
			else if (context.menu >= 1 && context.menu <= 6) 
			{
				context.phase = wrapVariant<PhaseVariant>(EditPhase::EditItem);
			}
			else 
			{
				lastError_ = MenuSelectResult::WRONG_INDEX;
				context.err = wrapVariant<ResultVariant>(lastError_);
			}
			break;
		}
		case(EditPhase::EditItem):
		{
			processEditData(context);
			editDataController(context);

			context.phase = wrapVariant<PhaseVariant>(EditPhase::EditStart);
			break;
		}
		case(EditPhase::EditCancle):
		{
			frame_ = uiMsgH_.editTitle();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.personalEdit(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.editConfirm();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.cancle(context.err, CancleType::Edit);
			frame_(errorMsgH_);

			bool yesNo = inputH_.askYesNo();
			lastError_ = inputH_.getLastError();

			if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
			{
				context.err = wrapVariant<ResultVariant>(lastError_);
				break; //EditCancle 상태 유지
			}

			context.err = nullopt;
			if (yesNo) 
			{
				context.phase = wrapVariant<PhaseVariant>(EditPhase::ExitCancel);
			}
			else 
			{
				context.phase = wrapVariant<PhaseVariant>(EditPhase::EditStart);
			}
			break;
		}
		case(EditPhase::ExitSuccess):
		case(EditPhase::ExitCancel):
		default:
			break;
		}

		UIUtils::clearScreen();

		phase = unwrapVariant<EditPhase>(context.phase);
		if (phase == EditPhase::ExitSuccess || phase == EditPhase::ExitCancel) { break; }
	}
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

void EditMenu::assignEditNameEmptyError(ContextData& context)
{
		context.err = wrapVariant<ResultVariant>(EditDataResult::EMPTY_NAME);
}

void EditMenu::editDataController(ContextData& context)
{
	if (context.menu == -1 && context.err.has_value() && holds_alternative<InputResult>(*context.err)) //InputResult인지 확인
	{
		if (get<InputResult>(*context.err) != InputResult::SUCCESS)
		{
			return;
		}
	}
		
	switch (context.menu)
	{
	case 1:
	{
		string s = inputH_.getString(StringRule::EmptyDisallow);
		lastError_ = inputH_.getLastError();
		context.err = wrapVariant<ResultVariant>(lastError_);

		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
		{
			assignEditNameEmptyError(context);
			break;
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
}
