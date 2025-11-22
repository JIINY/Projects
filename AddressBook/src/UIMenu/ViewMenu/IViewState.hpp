#pragma once
#include "../../UI/UICommonData.hpp"

class ViewMenu;

class IViewState
{
public:
	IViewState(ViewMenu& owner) : owner_(owner) {}
	virtual ~IViewState() = default;

	virtual void draw() = 0;
	virtual ViewPhase update() = 0;

protected:
	ViewMenu& owner_;
};
