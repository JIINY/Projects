#pragma once
#include "IDataInputState.hpp"


class InputNameState : public IDataInputState 
{
public:
	using IDataInputState::IDataInputState; //상속

	virtual void draw() override;
	virtual DataInputPhase update() override;
};

