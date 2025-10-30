#include "PersonalDataInput.hpp"
#include <memory>
#include <optional>

#include "States/InputNameState.hpp"
#include "States/InputPhoneState.hpp"
#include "States/InputAddressState.hpp"
#include "States/InputZipCodeState.hpp"
#include "States/InputEmailState.hpp"
using namespace std;


PersonalData PersonalDataInput::run(optional<PersonalData> initialData) 
{
	if (initialData.has_value()) 
	{
		data_ = initialData.value();
	}
	else 
	{
		data_ = PersonalData{};
	}
	
	lastError_ = nullopt;
}