#include "AddInputStartState.hpp"
#include <optional>
#include "AddMenu.hpp"
#include "../PersonalDataInput/PersonalDataInput.hpp"
using namespace std;


void AddInputStartState::draw() {} //PersonalDataInput클래스가 처리

AddPhase AddInputStartState::update() 
{
	auto& context = owner_.getContext();
	PersonalDataInput personalDataInput(InputMode::Add);

	context.p = personalDataInput.run(PersonalData{});
	context.err = nullopt;

	return AddPhase::AddReview;
}

