#pragma once
#include "IDataInputState.hpp"


class InputEmailState : public IDataInputState
{
public:
	using IDataInputState::IDataInputState; //���

	virtual void draw() override;
	virtual DataInputPhase update() override;
};
