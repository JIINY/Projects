#pragma once
#include "IDataInputState.hpp"


class InputZipCodeState : public IDataInputState
{
public:
	using IDataInputState::IDataInputState; //���

	virtual void draw() override;
	virtual DataInputPhase update() override;
};
