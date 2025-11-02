#include "InputNameState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "../PersonalDataInput.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void InputNameState::draw()
{
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	optional<ResultVariant> error = owner_.getLastError();
	frame = uiMsgH.editName(error);
	frame(errorMsgH);
}

DataInputPhase InputNameState::update()
{
	auto& inputH = owner_.getInputH();

	string name = inputH.getString(StringRule::EmptyDisallow);
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		owner_.setLastError(wrapVariant<ResultVariant>(EditDataResult::EMPTY_NAME));
		return DataInputPhase::InputName;
	}

	owner_.setName(name);
	owner_.setLastError(nullopt);
	return DataInputPhase::InputPhone;
}
