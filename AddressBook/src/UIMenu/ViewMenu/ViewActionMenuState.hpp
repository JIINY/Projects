#pragma once
#include "IViewState.hpp"

class ViewActionMenuState : public IViewState
{
public:
	using IViewState::IViewState;

	virtual void draw() override;
	virtual ViewPhase update() override;
};
