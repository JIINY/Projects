#pragma once
#include "../../UI/UICommonData.hpp"

class EditMenu;

class IEditState 
{
public:
	IEditState(EditMenu& owner) : owner_(owner) {}
	virtual ~IEditState() = default;

	virtual void draw() = 0;
	virtual EditPhase update() = 0;

protected:
	EditMenu& owner_;
};
