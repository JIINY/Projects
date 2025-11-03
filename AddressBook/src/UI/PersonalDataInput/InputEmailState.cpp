#include "InputEmailState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "PersonalDataInput.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void InputEmailState::draw()
{
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.editEmail(nullopt);
	frame(errorMsgH);
}

DataInputPhase InputEmailState::update()
{
	auto& inputH = owner_.getInputH();

	string s = inputH.getString(StringRule::EmptyAllow);
	owner_.setEmail(s);
	return DataInputPhase::Exit;
}
