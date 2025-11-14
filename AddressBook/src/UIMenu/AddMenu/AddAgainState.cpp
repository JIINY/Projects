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
	context.err = nullopt;

	ResultVariant result = inputH.askYesNo();
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		return AddPhase::AddInputStart;
	}
	else if (isVariantEqualTo<InputResult>(result, InputResult::NO))
	{
		return AddPhase::Exit;
	}

	context.err = wrapVariant<ResultVariant>(result);
	return AddPhase::AddAgain;
}

