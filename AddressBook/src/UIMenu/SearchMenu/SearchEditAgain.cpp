#include "SearchEditAgain.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchEditAgainState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();
	auto* bookUI = owner_.getBookUI();

	owner_.drawLongTitle();
	owner_.drawResultTable(*bookUI, context);
	owner_.drawResultMsg();

	frame = uiMsgH.searchEdit(context.err);
	frame(errorMsgH);
}

SearchPhase SearchEditAgainState::update()
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int resultCount = static_cast<int>(owner_.accessSearchResult().size());

	int input = -1; 
	ResultVariant result = inputH.getInt(IntRule::PositiveOnly, input);
	if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(result);
		return SearchPhase::EditAgain;
	}
	else if (input > resultCount)
	{
		result = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(result);
		return SearchPhase::EditAgain;
	}

	context.menu = input - 1;
	context.err = nullopt;
	return SearchPhase::EditItem;
}

