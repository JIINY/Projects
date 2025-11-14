#pragma once
#include "IEditState.hpp"

class EditStartState : public IEditState
{
public:
	using IEditState::IEditState; //주인을 받는 생성자를 상속
	
	virtual void draw() override;
	virtual EditPhase update() override;
};

