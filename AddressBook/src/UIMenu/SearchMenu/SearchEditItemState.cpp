#include "SearchEditItemState.hpp"
#include <vector>
#include <optional>
#include <utility>
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

	if (i >= resultVec.size()) 
	{
		context.err = wrapVariant<ResultVariant>(InputResult::WRONG_NUMBER);
		return SearchPhase::EditItem;
	}

	PersonalData dataToEdit = resultVec[i].first;
	int index = resultVec[i].second;

	EditMenu editMenu(InputMode::Edit);
	optional<PersonalData> editResult = editMenu.run(*bookUI, dataToEdit);
	if (editResult.has_value()) 
	{
		PersonalData editedData = editResult.value();
		AddOperationResult addResult = bookUI->extractAddressBook().edit(index, editedData);

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
	return SearchPhase::EditAgain;
}
