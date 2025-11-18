#include "SearchDeleteItemState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
#include "../DeleteMenu/DeleteMenu.hpp"
using namespace std;


SearchPhase SearchDeleteItemState::update() 
{
	auto& context = owner_.getContext();
	auto* bookUI = owner_.getBookUI();
	auto& resultVec = owner_.accessSearchResult();
	int i = context.menu;

	if (i >= resultVec.size()) 
	{
		context.err = wrapVariant<ResultVariant>(InputResult::WRONG_NUMBER);
		return SearchPhase::DeleteStart;
	}

	string name = resultVec[i].first.name;
	int index = resultVec[i].second;

	DeleteMenu deleteMenu;
	RemoveOperationResult result = deleteMenu.run(*bookUI, index, name);
	if (result == RemoveOperationResult::SUCCESS) 
	{
		context.p = resultVec[i].first;
		context.err = wrapVariant<ResultVariant>(result);

		resultVec.erase(resultVec.begin() + i);

		if (resultVec.empty()) 
		{
			return SearchPhase::SearchResult;
		}
	}
	else 
	{
		context.err = wrapVariant<ResultVariant>(result);
	}
	return SearchPhase::SearchResult;
}

