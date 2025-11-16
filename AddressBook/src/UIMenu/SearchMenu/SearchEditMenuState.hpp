#pragma once
#include "ISearchState.hpp"

class SearchEditMenuState : public ISearchState
{
public:
	using ISearchState::ISearchState;

	virtual void draw() override;
	virtual SearchPhase update() override;
};
