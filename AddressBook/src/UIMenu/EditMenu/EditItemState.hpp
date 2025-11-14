#pragma once
#include "IEditState.hpp"

class EditItemState : public IEditState 
{
public:
	using IEditState::IEditState;

	virtual void draw() override;
	virtual EditPhase update() override;
};

