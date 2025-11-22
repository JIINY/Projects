#pragma once
#include "IViewState.hpp"

class ViewEditState : public IViewState
{
public:
	using IViewState::IViewState;

	virtual void draw() override {};
	virtual ViewPhase update() override;
};
