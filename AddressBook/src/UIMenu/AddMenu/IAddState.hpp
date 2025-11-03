#pragma once
#include "../../UI/UICommonData.hpp"

class AddMenu;

class IAddState 
{
public:
	IAddState(AddMenu& owner) : owner_(owner) {}
	virtual ~IAddState() = default;

	virtual void draw() = 0;
	virtual AddPhase update() = 0;


protected:
	AddMenu& owner_;
};