#pragma once
#include "../../UI/UICommonData.hpp"

class PersonalDataInput;

class IDataInputState 
{
public:
	IDataInputState(PersonalDataInput& owner) : owner_(owner) {}
	virtual ~IDataInputState() = default;

	virtual void draw() = 0;
	virtual DataInputPhase update() = 0;


protected:
	PersonalDataInput& owner_;
};

