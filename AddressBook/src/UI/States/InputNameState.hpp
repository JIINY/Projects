#pragma once
#include "IDataInputState.hpp"


class InputNameState : public IDataInputState 
{
public:
	using IDataInputState::IDataInputState; //»ó¼Ó

	virtual void draw() override;
	virtual DataInputPhase update() override;
};
