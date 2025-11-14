#include "AskAddCancelState.hpp"
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "AddMenu.hpp"
using namespace std;


void AskAddCancelState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.addMenuLine(context.p);
	frame(errorMsgH);
	frame = uiMsgH.cancel(context.err, ActionType::Input);
	frame(errorMsgH);
}

AddPhase AskAddCancelState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	ResultVariant result = inputH.askYesNo();
	context.err = nullopt;
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		return AddPhase::Exit;
	}
	else if (isVariantEqualTo<InputResult>(result, InputResult::NO))
	{
		return AddPhase::AddReview;
	}

	context.err = wrapVariant<ResultVariant>(result);
	return AddPhase::AskAddCancel;
}

