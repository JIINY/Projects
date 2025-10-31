#pragma once
#include "IDataInputState.hpp"


class InputAddressState : public IDataInputState
{
public:
	using IDataInputState::IDataInputState; //»ó¼Ó

	virtual void draw() override;
	virtual DataInputPhase update() override;
};
