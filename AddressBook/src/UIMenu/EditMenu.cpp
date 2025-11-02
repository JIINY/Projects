#include "EditMenu.hpp"
#include <iostream>
#include <memory>
#include <cassert>
#include "../UI/AddressBookUI.hpp"
#include "../Common/VariantUtils.hpp"//log

#include "States/EditStartState.hpp"
#include "States/EditItemState.hpp"
#include "States/EditCancelState.hpp"
using namespace std;


optional<PersonalData> EditMenu::run(AddressBookUI& bookUI, const PersonalData& dataToEdit)
{
	bookUI_ = &bookUI;
	context_.p = dataToEdit;
	context_.err = nullopt;
	context_.menu = -1;

	//시작 상태로 설정
	EditPhase currentPhase = EditPhase::EditStart;
	transitionTo(currentPhase);

	while (currentPhase != EditPhase::ExitSuccess && currentPhase != EditPhase::ExitCancel) 
	{
		currentState_->draw();

		EditPhase nextPhase = currentState_->update();
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

	if (currentPhase == EditPhase::ExitSuccess)
	{
		context_.err = nullopt;
		return context_.p;
	}

	return nullopt;
}

void EditMenu::transitionTo(EditPhase nextPhase) 
{
	if (nextPhase != EditPhase::EditItem) 
	{
		ui_.clearScreen();
	}

	switch (nextPhase) {
	case EditPhase::EditStart: 
	{
		currentState_ = make_unique<EditStartState>(*this);
		break;
	}
	case EditPhase::EditItem:
	{
		currentState_ = make_unique<EditItemState>(*this);
		break;
	}
	case EditPhase::EditCancel:
	{
		currentState_ = make_unique<EditCancelState>(*this);
		break;
	}
	case EditPhase::ExitSuccess:
	{
		currentState_ = nullptr;
		break;
	}
	case EditPhase::ExitCancel:
	{
		currentState_ = nullptr;
		break;
	}
	default:
	{
		assert(false && "EditMenu::transitionTo: unhandled EditPhase!");
		break;
	}
	}
}
