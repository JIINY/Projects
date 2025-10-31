#include "InputPhoneState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "../PersonalDataInput.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void InputPhoneState::draw()
{
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.editPhone(nullopt);
	frame(errorMsgH);
}

DataInputPhase InputPhoneState::update()
{
	auto& inputH = owner_.getInputH();

	string s = inputH.getString(StringRule::EmptyAllow);
	owner_.setPhone(s);
	return DataInputPhase::InputAddress;
}
