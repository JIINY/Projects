#include "AddMenu.hpp"
#include <iostream>
#include <memory>
#include <cassert>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"

#include "AddInputStartState.hpp"
#include "AddReviewState.hpp"
#include "AddEditStartState.hpp"
#include "AskAddCancelState.hpp"
#include "AddSuccessState.hpp"
#include "AddAgainState.hpp"

#include "../MainMenu.hpp"
#include "../EditMenu/EditMenu.hpp"
using namespace std;


void AddMenu::run(AddressBookUI& bookUI)
{
	bookUI_ = &bookUI;
	context_ = ContextData{};
	context_.err = nullopt;

	AddPhase currentPhase = AddPhase::AddInputStart;
	transitionTo(currentPhase);

	while (currentPhase != AddPhase::Exit)
	{
		//그리기
		if (currentState_) 
		{
			currentState_->draw();
		}

		//처리
		AddPhase nextPhase = currentPhase;
		if (currentState_) 
		{
			nextPhase = currentState_->update();
		}

		//상태 전이
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

	//종료시 화면 정리
	ui_.clearScreen();
}

void AddMenu::transitionTo(AddPhase nextPhase) 
{
	ui_.clearScreen();

	switch (nextPhase) {
	case AddPhase::AddInputStart: 
	{
		currentState_ = make_unique<AddInputStartState>(*this);
		break;
	}
	case AddPhase::AddReview: 
	{
		currentState_ = make_unique<AddReviewState>(*this);
		break;
	}
	case AddPhase::AddEditStart: 
	{
		currentState_ = make_unique<AddEditStartState>(*this);
		break;
	}
	case AddPhase::AskAddCancel:
	{
		currentState_ = make_unique<AskAddCancelState>(*this);
		break;
	}
	case AddPhase::AddSuccess:
	{
		currentState_ = make_unique<AddSuccessState>(*this);
		break;
	}
	case AddPhase::AddAgain:
	{
		currentState_ = make_unique<AddAgainState>(*this);
		break;
	}
	case AddPhase::Exit: 
	{
		currentState_ = nullptr;
		break;
	}
	default: 
	{
		assert(false && "AddMenu::transitionTo: unhandled AddPhase!");
		break;
	}
	}
}
