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
#include "SearchEmptyMenuState.hpp"
#include "SearchEditMenuState.hpp"
#include "SearchEditState.hpp"
#include "SearchEditItemState.hpp"
#include "SearchDeleteMenuState.hpp"
#include "SearchDeleteState.hpp"
#include "SearchDeleteItemState.hpp"
#include "SearchAgainState.hpp"
#include "../EditMenu/EditMenu.hpp"
#include "../DeleteMenu.hpp"
using namespace std;


void SearchMenu::run(AddressBookUI& bookUI)
{
	bookUI_ = &bookUI;
	context_ = ContextData{};
	context_.err = nullopt;
	searchResult_.clear();


	SearchPhase currentPhase = SearchPhase::SearchStart;
	transitionTo(currentPhase);

	while (currentPhase != SearchPhase::Exit)
	{
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
			transitionTo(nextPhase);
			currentPhase = nextPhase;
		}
		else
		{
			ui_.clearScreen();
		}
	}

	ui_.clearScreen(); //종료시 화면 정리
}

void SearchMenu::transitionTo(SearchPhase nextPhase) 
{
	if (nextPhase == SearchPhase::SearchStart ||
		nextPhase == SearchPhase::SearchInputData ||
		nextPhase == SearchPhase::SearchResult ||
		nextPhase == SearchPhase::SearchAgain) 
	{
		ui_.clearScreen();
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
}

void SearchMenu::drawLongTitle() 
{
	switch (mode_) {
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
			int bookIndex = searchResult_[i].second;
			context.p = bookUI.getPersonalDataAt(bookIndex);

			int displayNum = i + 1;
			if (i == (endIndex - 1))
			{
				frame_ = uiMsgH_.tableDataBottom(context.err, displayNum, context.p);
			}
			else
			{
				int remainder = (displayNum) % 10;
				if (remainder == 5)
				{
					frame_ = uiMsgH_.tableDataCenter(context.err, displayNum, context.p);
				}
				else
				{
					frame_ = uiMsgH_.tableDataNormal(context.err, displayNum, context.p);
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

	if (mode_ == SearchMode::Edit) 
	{
		if (isVariantEqualTo<AddOperationResult>(*context_.err, AddOperationResult::SUCCESS))
		{
			frame_ = uiMsgH_.tableEditSuccess(context_.menu + 1, context_.p.name);
			frame_(errorMsgH_);

			context_.err = nullopt;
		}
		else 
		{
			frame_ = uiMsgH_.tableAction(ActionType::Edit);
			frame_(errorMsgH_);
		}
	}
	else if (mode_ == SearchMode::Delete)
	{
		if (isVariantEqualTo<RemoveOperationResult>(*context_.err, RemoveOperationResult::SUCCESS)) 
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
	}
	else
	{
		if (length > 0)
		{
			frame_ = uiMsgH_.tableSearchEnd();
			frame_(errorMsgH_);
		}
		else 
		{
			frame_ = uiMsgH_.searchEmpty();
			frame_(errorMsgH_);
		}
	}
}
