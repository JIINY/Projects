#pragma once
#include "IEditState.hpp"

class EditStartState : public IEditState
{
public:
	using IEditState::IEditState; //������ �޴� �����ڸ� ���
	
	virtual void draw() override;
	virtual EditPhase update() override;
};
