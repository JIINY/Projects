#include "SearchEditItemState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include <cassert>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
#include "../EditMenu/EditMenu.hpp"
using namespace std;


SearchPhase SearchEditItemState::update() 
{
	auto& context = owner_.getContext();
	auto* bookUI = owner_.getBookUI();
	auto& resultVec = owner_.accessSearchResult();
	int i = context.menu;

	assert(i < resultVec.size() && "SearchEditItemState: Invalid index received.");

	PersonalData dataToEdit = resultVec[i].first;
	int index = resultVec[i].second;
	int validIndex = bookUI->extractAddressBook().findIndexByData(dataToEdit);

	assert(validIndex != -1 && "SearchEditItemState: Data in SearchResult_ is stale and not found in AddressBook.");

	EditMenu editMenu(InputMode::Edit);
	optional<PersonalData> editResult = editMenu.run(*bookUI, dataToEdit);
	if (editResult.has_value()) 
	{
		PersonalData editedData = editResult.value();
		AddOperationResult addResult = bookUI->extractAddressBook().edit(validIndex, editedData);

		if (addResult == AddOperationResult::SUCCESS) 
		{
			resultVec[i].first = editedData; //검색 결과도 업데이트

			context.p = editedData;
			context.err = wrapVariant<ResultVariant>(addResult);
		}
		else 
		{
			context.err = wrapVariant<ResultVariant>(addResult);
		}
	}
	else
	{
		context.err = nullopt; //수정 취소
	}
	return SearchPhase::SearchResult;
}
