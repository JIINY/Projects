#include "AddMenu.hpp"
#include <iostream>
#include "../Common/VariantUtils.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
#include "MainMenu.hpp"
#include "EditMenu.hpp"
using namespace std;


void AddMenu::run(AddressBookUI& bookUI)
{
	ContextData context;
	AddPhase currentPhase = AddPhase::InputStart;
	context.err = nullopt;

	while (currentPhase != AddPhase::Exit) 
	{
		//그리기
		switch (currentPhase)
		{
		case AddPhase::AddMenuSelect:
		{
			frame_ = uiMsgH_.addConfirm(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			break;
		}
		case AddPhase::InputAddCancel:
		{
			frame_ = uiMsgH_.addMenuLine(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.cancel(context.err, CancelType::Input);
			frame_(errorMsgH_);
			break;
		}
		case AddPhase::AddAgain:
		{
			frame_ = uiMsgH_.addSuccess(bookUI.getLastAdd() + 1, context.sub);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.addAgain(context.err);
			frame_(errorMsgH_);
			break;
		}
		default:
			break; //나머지 상태는 그리기가 없거나, 다른 함수가 그리기를 겸함
		}


		//처리
		AddPhase nextPhase = currentPhase;
		switch (currentPhase){
		case AddPhase::InputStart: 
		{
			nextPhase = onInputStart(context);
			break;
		}
		case AddPhase::AddMenuSelect: 
		{
			nextPhase = onAddMenuSelect(context);
			break;
		}
		case AddPhase::InputAddCancel: 
		{
			nextPhase = onInputAddCancel(context);
			break;
		}
		case AddPhase::AddSuccess: 
		{
			nextPhase = onAddSuccess(bookUI, context);
			break;
		}
		case AddPhase::AddAgain: 
		{
			nextPhase = onAddAgain(context);
			break;
		}
		case AddPhase::AddEditStart: 
		{
			nextPhase = onAddEditStart(bookUI, context);
			break;
		}
		case AddPhase::AddEditConfirm: 
		{
			nextPhase = onAddEditConfirm(bookUI, context);
			break;
		}
		default:
			break;
		}


		//화면 정리 및 상태 전이
		UIUtils::clearScreen();
		currentPhase = nextPhase;
	}
}

AddPhase AddMenu::onInputStart(ContextData& context)
{
	context.p = ui_.processInputPersonalData(OutputPrintHandler::printAddTitle);
	context.err = nullopt;
	return AddPhase::AddMenuSelect;
}

AddPhase AddMenu::onAddMenuSelect(ContextData& context)
{
	context.menu = inputH_.getInt(IntRule::ZeroOrPositive);

	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::AddMenuSelect;
	}

	context.err = nullopt;
	return processMenuSelection(context);
}

AddPhase AddMenu::processMenuSelection(ContextData& context)
{
	switch (context.menu) {
	case(0):
	{
		context.err = nullopt;
		return AddPhase::InputAddCancel;
	}
	case(1):
	{
		context.err = nullopt;
		return AddPhase::AddSuccess;
	}
	case(2):
	{
		context.err = nullopt;
		return AddPhase::AddEditStart;
	}
	default:
	{
		lastError_ = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::AddMenuSelect;
	}
	}
}

AddPhase AddMenu::onInputAddCancel(ContextData& context)
{
	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();

	if (yesNo)
	{
		context.err = nullopt;
		return AddPhase::Exit;
	}

	if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::InputAddCancel;
	}

	context.err = nullopt;
	return AddPhase::AddMenuSelect;
}

AddPhase AddMenu::onAddSuccess(AddressBookUI& bookUI, ContextData& context)
{
	lastError_ = bookUI.addPersonalData(context.p);

	if (!isVariantEqualTo <AddOperationResult>(lastError_, AddOperationResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::AddAgain;
	}

	context.p = bookUI.getPersonalDataAt(bookUI.getLastAdd());
	context.sub = ui_.getPersonalDataTableFormat(context.p);
	context.err = nullopt;
	return AddPhase::AddAgain;
}

AddPhase AddMenu::onAddAgain(ContextData& context)
{
	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();

	if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::AddAgain;
	}

	if (yesNo)
	{
		context.err = nullopt;
		return AddPhase::InputStart;
	}

	context.err = nullopt;
	return AddPhase::Exit;
}

AddPhase AddMenu::onAddEditStart(AddressBookUI& bookUI, ContextData& context)
{
	EditMenu edit;
	optional<PersonalData> editResult = edit.run(bookUI, context.p);

	if (editResult.has_value())
	{
		context.p = editResult.value();
		context.err = nullopt;
		return AddPhase::AddEditConfirm;
	}

	context.err = nullopt;
	return AddPhase::AddMenuSelect;
}

AddPhase AddMenu::onAddEditConfirm(AddressBookUI& bookUI, ContextData& context)
{
	lastError_ = bookUI.addPersonalData(context.p);
	if (!isVariantEqualTo<AddOperationResult>(lastError_, AddOperationResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return AddPhase::AddAgain;
	}

	context.p = bookUI.getPersonalDataAt(bookUI.getLastAdd());
	context.sub = ui_.getPersonalDataTableFormat(context.p);
	context.err = nullopt;
	return AddPhase::AddAgain;
}
