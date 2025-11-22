#include "SearchListState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;

void SearchListState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();
	int resultSize = static_cast<int>(owner_.accessSearchResult().size());
	auto* bookUI = owner_.getBookUI();

	owner_.drawLongTitle();
	owner_.drawResultTable(*bookUI, context);
	owner_.drawResultMsg();
}

SearchPhase SearchListState::update() 
{
	return SearchPhase::ModeSelect;
}
