#pragma once
#include "../../UI/UICommonData.hpp"

class SearchMenu;

class ISearchState
{
public:
	ISearchState(SearchMenu& owner) : owner_(owner) {}
	virtual ~ISearchState() = default;

	virtual void draw() = 0;
	virtual SearchPhase update() = 0;

protected:
	SearchMenu& owner_;
};

