#pragma once
#include "IDataInputState.hpp"


class InputNameState : public IDataInputState 
{
public:
	using IDataInputState::IDataInputState; //���

	virtual void draw() override;
	virtual DataInputPhase update() override;
};
