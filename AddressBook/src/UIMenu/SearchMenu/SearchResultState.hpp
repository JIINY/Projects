#pragma once
#include "ISearchState.hpp"

class SearchResultState : public ISearchState
{
public:
	using ISearchState::ISearchState;

	virtual void draw() override;
	virtual SearchPhase update() override;


private:
	SearchPhase processSubMenu(int menu, int resultSize);
	SearchPhase processEmptyMenu(int menu);
	SearchPhase processResultMenu(int menu);
};

