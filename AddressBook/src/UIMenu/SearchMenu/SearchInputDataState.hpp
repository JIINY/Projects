#pragma once
#include "ISearchState.hpp"

class SearchInputDataState : public ISearchState
{
public:
	using ISearchState::ISearchState;

	virtual void draw() override;
	virtual SearchPhase update() override;
};
