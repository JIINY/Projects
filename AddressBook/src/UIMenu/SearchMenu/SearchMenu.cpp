#include "SearchMenu.hpp"
#include <vector>
#include <optional>
#include <algorithm>
#include <memory>
#include <utility>
#include <cassert>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "../../UI/AddressBookUI.hpp"

#include "SearchStartState.hpp"
#include "SearchInputDataState.hpp"
#include "SearchResultState.hpp"
#include "SearchModeSelectState.hpp"
#include "SearchModeMenuState.hpp"
#include "SearchActionMenuState.hpp"
#include "SearchEmptyMenuState.hpp"
#include "SearchEditMenuState.hpp"
#include "SearchEditState.hpp"
#include "SearchEditItemState.hpp"
#include "SearchDeleteMenuState.hpp"
#include "SearchDeleteState.hpp"
#include "SearchDeleteItemState.hpp"
#include "SearchAgainState.hpp"
#include "../EditMenu/EditMenu.hpp"
#include "../DeleteMenu/DeleteMenu.hpp"
using namespace std;


void SearchMenu::run(AddressBookUI& bookUI)
{
	bookUI_ = &bookUI;
	context_ = ContextData{};
	context_.err = nullopt;
	searchResult_.clear();
	bool needsScreenClear = true;

	SearchPhase currentPhase = SearchPhase::SearchStart;
	transitionTo(currentPhase);

	while (currentPhase != SearchPhase::Exit)
	{
		if (needsScreenClear) 
		{
			ui_.clearScreen();
			
		}
		if (currentState_)
		{
			currentState_->draw();
		}

		SearchPhase nextPhase = currentPhase;
		if (currentState_)
		{
			nextPhase = currentState_->update();
		}

		if (nextPhase != currentPhase)
		{
			needsScreenClear = transitionTo(nextPhase);
			currentPhase = nextPhase;
		}
		else if (context_.err.has_value()) 
		{
			needsScreenClear = true;
		}
		else
		{
			needsScreenClear = false;
		}
	}

	ui_.clearScreen(); //종료시 화면 정리
}

bool SearchMenu::transitionTo(SearchPhase nextPhase) 
{
	bool shouldClearNextFrame = false;
	if (nextPhase == SearchPhase::SearchStart ||
		nextPhase == SearchPhase::SearchInputData ||
		nextPhase == SearchPhase::SearchResult ||
		nextPhase == SearchPhase::SearchAgain) 
	{
		shouldClearNextFrame = true;
	}

	switch (nextPhase) {
	case SearchPhase::SearchStart: 
	{
		currentState_ = make_unique<SearchStartState>(*this);
		break;
	}
	case SearchPhase::SearchInputData:
	{
		currentState_ = make_unique<SearchInputDataState>(*this);
		break;
	}
	case SearchPhase::SearchResult: 
	{
		currentState_ = make_unique<SearchResultState>(*this);
		break;
	}
	case SearchPhase::ModeSelect: 
	{
		currentState_ = make_unique<SearchModeSelectState>(*this);
		break;
	}
	case SearchPhase::SearchMode:
	{
		currentState_ = make_unique<SearchModeMenuState>(*this);
		break;
	}
	case SearchPhase::SearchEmptyMode:
	{
		currentState_ = make_unique<SearchEmptyMenuState>(*this);
		break;
	}
	case SearchPhase::ActionMode:
	{
		currentState_ = make_unique<SearchActionMenuState>(*this);
		break;
	}
	case SearchPhase::EditMode:
	{
		currentState_ = make_unique<SearchEditMenuState>(*this);
		break;
	}
	case SearchPhase::EditStart:
	{
		currentState_ = make_unique<SearchEditState>(*this);
		break;
	}
	case SearchPhase::EditItem:
	{
		currentState_ = make_unique<SearchEditItemState>(*this);
		break;
	}
	case SearchPhase::DeleteMode:
	{
		currentState_ = make_unique<SearchDeleteMenuState>(*this);
		break;
	}
	case SearchPhase::DeleteStart:
	{
		currentState_ = make_unique<SearchDeleteState>(*this);
		break;
	}
	case SearchPhase::DeleteItem:
	{
		currentState_ = make_unique<SearchDeleteItemState>(*this);
		break;
	}
	case SearchPhase::SearchAgain:
	{
		currentState_ = make_unique<SearchAgainState>(*this);
		break;
	}
	case SearchPhase::Exit:
	{
		currentState_ = nullptr;
		break;
	}
	default:
	{
		assert(false && "SearchMenu::transitionTo: unhandled SearchPhase!");
		break;
	}
	}

	return shouldClearNextFrame;
}

void SearchMenu::drawLongTitle() 
{
	switch (mode_) {
	case SearchMode::SearchEmpty:
	case SearchMode::Action:
	case SearchMode::Search: 
	{
		frame_ = uiMsgH_.searchLongTitle();
		frame_(errorMsgH_);
		break;
	}
	case SearchMode::Edit: 
	{
		frame_ = uiMsgH_.editLongTitle();
		frame_(errorMsgH_);
		break;
	}
	case SearchMode::Delete:
	{
		frame_ = uiMsgH_.deleteLongTitle();
		frame_(errorMsgH_);
		break;
	}
	}
}

void SearchMenu::drawResultTable(AddressBookUI& bookUI, ContextData& context)
{
	int length = static_cast<int>(searchResult_.size());
	if (length > 0)
	{
		int page = page_;
		int startIndex = page * 10;
		int endIndex = min(startIndex + 10, length);

		for (int i = startIndex; i < endIndex; ++i)
		{
			PersonalData p = searchResult_[i].first;

			int displayNum = i + 1;
			if (i == (endIndex - 1))
			{
				frame_ = uiMsgH_.tableDataBottom(context.err, displayNum, p);
			}
			else
			{
				int remainder = (displayNum) % 10;
				if (remainder == 5)
				{
					frame_ = uiMsgH_.tableDataCenter(context.err, displayNum, p);
				}
				else
				{
					frame_ = uiMsgH_.tableDataNormal(context.err, displayNum, p);
				}
			}
			frame_(errorMsgH_);
		}
	}
}

void SearchMenu::drawResultMsg() 
{
	int length = static_cast<int>(searchResult_.size());
	if (length > 9)
	{
		frame_ = uiMsgH_.tableCommand();
		frame_(errorMsgH_);
	}

	switch (mode_) {
	case SearchMode::Edit: 
	{
		if (context_.err.has_value() 
			&& isVariantEqualTo<AddOperationResult>(*context_.err, AddOperationResult::SUCCESS))
		{
			frame_ = uiMsgH_.tableEditSuccess(context_.menu + 1, context_.p.name);
			frame_(errorMsgH_);

			context_.err = nullopt;
		}
		else //다른 에러거나, nullopt
		{
			frame_ = uiMsgH_.tableAction(ActionType::Edit);
			frame_(errorMsgH_);
		}
		break;
	}
	case SearchMode::Delete:
	{
		if (context_.err.has_value()
			&& isVariantEqualTo<RemoveOperationResult>(*context_.err, RemoveOperationResult::SUCCESS))
		{
			frame_ = uiMsgH_.tableDeleteSuccess(context_.menu + 1, context_.p.name);
			frame_(errorMsgH_);
			context_.err = nullopt;
		}
		else
		{
			frame_ = uiMsgH_.tableAction(ActionType::Delete);
			frame_(errorMsgH_);
		}
		break;
	}
	case SearchMode::SearchEmpty: 
	{
		frame_ = uiMsgH_.searchEmpty();
		frame_(errorMsgH_);
		break;
	}
	case SearchMode::Action:
	{
		frame_ = uiMsgH_.tableSearchEnd();
		frame_(errorMsgH_);
		frame_ = uiMsgH_.searchSubMenu(context_.err);
		frame_(errorMsgH_);
		frame_ = uiMsgH_.menuSelect(context_.err);
		frame_(errorMsgH_);
		break;
	}
	default:
	{
		frame_ = uiMsgH_.tableSearchEnd();
		frame_(errorMsgH_);
		break;
	}
	}
}
