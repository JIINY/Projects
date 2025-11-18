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
	owner_.setMode(SearchMode::Delete);

	auto& context = owner_.getContext();
	auto* bookUI = owner_.getBookUI();
	auto& resultVec = owner_.accessSearchResult();
	int i = context.menu;

	if (i >= resultVec.size()) 
	{
		context.err = wrapVariant<ResultVariant>(InputResult::WRONG_NUMBER);
		return SearchPhase::DeleteStart;
	}

	PersonalData dataToDelete = resultVec[i].first;
	const string& backupName = dataToDelete.name;
	int backupIndex = i + 1;

	int validIndex = bookUI->extractAddressBook().findIndexByData(dataToDelete);
	if (validIndex == -1) 
	{
		context.err = wrapVariant<ResultVariant>(RemoveOperationResult::NOT_FOUND);
		return SearchPhase::SearchResult;
	}

	DeleteMenu deleteMenu;
	RemoveOperationResult result = deleteMenu.run(*bookUI, validIndex, std::make_pair(backupIndex, backupName));

	if (result == RemoveOperationResult::SUCCESS) 
	{
		context.p = dataToDelete;
		context.err = wrapVariant<ResultVariant>(result);

		resultVec.erase(resultVec.begin() + i);

		if (resultVec.empty()) 
		{
			owner_.setMode(SearchMode::SearchEmpty);
			return SearchPhase::SearchResult;
		}
	}
	else 
	{
		context.err = wrapVariant<ResultVariant>(result);
	}
	return SearchPhase::SearchResult;
}
