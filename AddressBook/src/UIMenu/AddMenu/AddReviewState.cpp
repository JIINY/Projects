#include "AddReviewState.hpp"
#include <optional>
#include "../../Common/VariantUtils.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/PersonalDataInput/PersonalDataInput.hpp"
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

	context.menu = inputH.getInt(IntRule::ZeroOrPositive);
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo <InputResult>(error, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(error);
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
		error = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(error);
		return AddPhase::AddReview;
	}
	}
}
