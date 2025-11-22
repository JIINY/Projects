#include "ViewMenu.hpp"
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "../../UI/AddressBookUI.hpp"

#include "ViewListState.hpp"
#include "ViewActionMenuState.hpp"
#include "ViewEditState.hpp"
#include "ViewDeleteState.hpp"
using namespace std;


int ViewMenu::getLength() const 
{
	if (bookUI_) 
	{
		return bookUI_->extractAddressBook().getLength();
	}
	return 0;
}

void ViewMenu::run(AddressBookUI& bookUI)
{
	bookUI_ = &bookUI;
	context_.err = nullopt;
	bool needsScreenClear = true;

	ViewPhase currentPhase = ViewPhase::List;
	transitionTo(currentPhase);

	while (currentPhase != ViewPhase::Exit)
	{
		if (needsScreenClear) 
		{
			ui_.clearScreen();
		}
		
		if (currentState_) 
		{
			currentState_->draw();
		}

		ViewPhase nextPhase = currentPhase;
		if (currentState_) 
		{
			nextPhase = currentState_->update();
		}

		if (nextPhase != currentPhase) 
		{
			needsScreenClear = transitionTo(nextPhase);
			currentPhase = nextPhase;
		}
		else if (context_.err.has_value() || currentPhase == ViewPhase::List)
		{
			needsScreenClear = true;
		}
		else 
		{
			needsScreenClear = false;
		}
	}

	ui_.clearScreen();
	bookUI_ = nullptr;
}

bool ViewMenu::transitionTo(ViewPhase nextPhase) 
{
	bool shouldClearNextFrame = true;

	//화면 유지케이스 처리
	if (nextPhase == ViewPhase::DeleteConfirm
		|| nextPhase == ViewPhase::Action) 
	{
		shouldClearNextFrame = false;
	}

	switch (nextPhase) {
	case ViewPhase::List:
	{
		currentState_ = make_unique<ViewListState>(*this);
		break;
	}
	case ViewPhase::Action:
	{
		currentState_ = make_unique<ViewActionMenuState>(*this);
		break;
	}
	case ViewPhase::Edit:
	{
		currentState_ = make_unique<ViewEditState>(*this);
		break;
	}
	case ViewPhase::DeleteConfirm:
	{
		currentState_ = make_unique<ViewDeleteState>(*this);
		break;
	}
	case ViewPhase::Exit:
	{
		currentState_.reset();
		break;
	}
	}

	return shouldClearNextFrame;
}
