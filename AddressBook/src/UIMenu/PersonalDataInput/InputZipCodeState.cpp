#include "InputZipCodeState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "PersonalDataInput.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void InputZipCodeState::draw()
{
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.editZipCode(nullopt);
	frame(errorMsgH);
}

DataInputPhase InputZipCodeState::update()
{
	auto& inputH = owner_.getInputH();
	string s = "";
	ResultVariant result = inputH.getString(StringRule::EmptyAllow, s);
	owner_.setZipCode(s);
	return DataInputPhase::InputEmail;
}

