#pragma once
#include "IAddState.hpp"

class AddAgainState : public IAddState
{
public:
	using IAddState::IAddState;

	virtual void draw() override;
	virtual AddPhase update() override;
};

