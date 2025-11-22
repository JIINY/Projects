#pragma once
#include "IViewState.hpp"

class ViewListState : public IViewState
{
public:
	using IViewState::IViewState;

	virtual void draw() override;
	virtual ViewPhase update() override;
};
