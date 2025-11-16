#include "SearchModeSelectState.hpp"
#include <vector>
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


SearchPhase SearchModeSelectState::update() 
{
	int resultSize = static_cast<int>(owner_.accessSearchResult().size());
	SearchMode mode = owner_.getMode();

	if (resultSize == 0) 
	{
		return SearchPhase::SearchEmptyMode;
	}
	switch (mode) 
	{
	case SearchMode::Edit:
		return SearchPhase::EditMode;
	case SearchMode::Delete:
		return SearchPhase::DeleteMode;
	case SearchMode::Action:
		return SearchPhase::ActionMode;
	case SearchMode::Search:
	default:
		return SearchPhase::SearchMode;
	}
}
