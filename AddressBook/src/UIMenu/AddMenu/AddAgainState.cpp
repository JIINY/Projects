#include "AddAgainState.hpp"
#include <optional>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "AddMenu.hpp"
using namespace std;

void AddAgainState::draw() 
{
	auto& context = owner_.getContext();
	auto* bookUI = owner_.getAddressBookUI();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	if (!context.sub.name.empty()) 
	{
		frame = uiMsgH.addSuccess(bookUI->getLastAdd() + 1, context.sub); //성공 메세지
		frame(errorMsgH);
	}

	frame = uiMsgH.addAgain(context.err);
	frame(errorMsgH);
}

AddPhase AddAgainState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	bool yesNo = inputH.askYesNo();
	ResultVariant error = inputH.getLastError();

	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return AddPhase::AddAgain;
	}

	context.err = nullopt;
	if (yesNo) 
	{
		return AddPhase::AddInputStart;
	}
	else 
	{
		return AddPhase::Exit;
	}
}
