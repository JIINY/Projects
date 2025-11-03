#include "InputAddressState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "PersonalDataInput.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void InputAddressState::draw()
{
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.editAddress(nullopt);
	frame(errorMsgH);
}

DataInputPhase InputAddressState::update()
{
	auto& inputH = owner_.getInputH();

	string s = inputH.getString(StringRule::EmptyAllow);
	owner_.setAddress(s);
	return DataInputPhase::InputZipCode;
}
