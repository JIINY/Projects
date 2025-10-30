#include "PersonalDataInput.hpp"
#include <memory>
#include <optional>
#include <cassert>

#include "States/InputNameState.hpp"
#include "States/InputPhoneState.hpp"
#include "States/InputAddressState.hpp"
#include "States/InputZipCodeState.hpp"
#include "States/InputEmailState.hpp"
using namespace std;


PersonalData PersonalDataInput::run(optional<PersonalData> initialData) 
{
	//������� �ʱ�ȭ
	if (initialData.has_value()) 
	{
		data_ = initialData.value();
	}
	else 
	{
		data_ = PersonalData{};
	}	
	lastError_ = nullopt;

	//���� ���·� ����(�̸� �Է�)
	DataInputPhase currentPhase = DataInputPhase::InputName;
	transitionTo(currentPhase);

	while (currentPhase != DataInputPhase::Exit) 
	{
		currentState_->draw();
		
		DataInputPhase nextPhase = currentState_->update();
		if (nextPhase != currentPhase) 
		{
			transitionTo(nextPhase);
			currentPhase = nextPhase;
		}
	}

	return data_;
}

void PersonalDataInput::transitionTo(DataInputPhase nextPhase) 
{
	if (nextPhase != DataInputPhase::Exit) 
	{
		ui_.clearScreen();
	}

	switch (nextPhase) {
	case DataInputPhase::InputName:
	{
		currentState_ = make_unique<InputNameState>(*this);
		break;
	}
	case DataInputPhase::InputPhone:
	{
		currentState_ = make_unique<InputPhoneState>(*this);
		break;
	}
	case DataInputPhase::InputAddress:
	{
		currentState_ = make_unique<InputAddressState>(*this);
		break;
	}
	case DataInputPhase::InputZipCode:
	{
		currentState_ = make_unique<InputZipCodeState>(*this);
		break;
	}
	case DataInputPhase::InputEmail:
	{
		currentState_ = make_unique<InputEmailState>(*this);
		break;
	}
	case DataInputPhase::Exit:
	{
		currentState_ = nullptr;
		break;
	}
	default: 
	{
		assert(false && "PersonalDataInpu::transitionTo: unhandled DataInputPhase.");
		break;
	}
	}
}