#include "SearchDeleteAgainState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchDeleteAgainState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	owner_.drawLongTitle();
	owner_.drawResultTable();
	owner_.drawResultMsg();

	frame = uiMsgH.searchDelete(context.err);
	frame(errorMsgH);
}

SearchPhase SearchDeleteAgainState::update()
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int resultCount = static_cast<int>(owner_.accessSearchResult().size());

	int input = inputH.getInt(IntRule::PositiveOnly);
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::DeleteAgain;
	}

	if (input > resultCount)
	{
		error = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::DeleteAgain;
	}

	//¼º°ø
	context.menu = input - 1;
	context.err = nullopt;
	return SearchPhase::DeleteItem;
}
