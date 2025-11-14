#include "AddReviewState.hpp"
#include <optional>
#include "../../Common/VariantUtils.hpp"
#include "../../UI/UICommonData.hpp"
#include "../PersonalDataInput/PersonalDataInput.hpp"
#include "AddMenu.hpp"
using namespace std;


void AddReviewState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.addConfirm(context.p);
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

AddPhase AddReviewState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	ResultVariant result = inputH.getInt(IntRule::ZeroOrPositive, context.menu);
	if (!isVariantEqualTo <InputResult>(result, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(result);
		return AddPhase::AddReview;
	}

	context.err = nullopt;
	switch (context.menu) {
	case(0):
	{
		context.err = nullopt;
		return AddPhase::AskAddCancel;
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
		result = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(result);
		return AddPhase::AddReview;
	}
	}
}

