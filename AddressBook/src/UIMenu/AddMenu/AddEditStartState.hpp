#pragma once
#include "IAddState.hpp"

class AddEditStartState : public IAddState
{
public:
	using IAddState::IAddState;

	virtual void draw() override;
	virtual AddPhase update() override;
};

