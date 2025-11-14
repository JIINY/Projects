#include "EditItemState.hpp"
#include <string>
#include <optional>
#include <cassert>
#include "EditMenu.hpp"
#include "../../Common/VariantUtils.hpp"
#include "../PersonalDataInput/PersonalDataInput.hpp"
using namespace std;


void EditItemState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();
	auto& ui = owner_.getUI();

	switch (context.menu) {
	case 1: 
	{
		frame = uiMsgH.editName(context.err);
		frame(errorMsgH);
		break;
	}
	case 2:
	{
		frame = uiMsgH.editPhone(context.err);
		frame(errorMsgH);
		break;
	}
	case 3:
	{
		frame = uiMsgH.editAddress(context.err);
		frame(errorMsgH);
		break;
	}
	case 4:
	{
		frame = uiMsgH.editZipCode(context.err);
		frame(errorMsgH);
		break;
	}
	case 5:
	{
		frame = uiMsgH.editEmail(context.err);
		frame(errorMsgH);
		break;
	}
	default:
		ui.clearScreen();
		break; // 6. 전체수정은 PersonalDataInput가 처리
	}
}


EditPhase EditItemState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	string s = "";

	switch (context.menu) {
	case 1:
	{
		ResultVariant result = inputH.getString(StringRule::EmptyDisallow, s);
		if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS)) 
		{
			context.err = wrapVariant<ResultVariant>(EditDataResult::EMPTY_NAME);
			return EditPhase::EditStart;
		}

		context.p.name = s;
		break;
	}
	case 2: 
	{
		ResultVariant result = inputH.getString(StringRule::EmptyAllow, s);
		context.p.phone = s;
		break;
	}
	case 3:
	{
		ResultVariant result = inputH.getString(StringRule::EmptyAllow, s);
		context.p.address = s;
		break;
	}
	case 4:
	{
		ResultVariant result = inputH.getString(StringRule::EmptyAllow, s);
		context.p.zipCode = s;
		break;
	}
	case 5:
	{
		ResultVariant result = inputH.getString(StringRule::EmptyAllow, s);
		context.p.email = s;
		break;
	}
	case 6:
	{
		PersonalDataInput personalDataInput(owner_.getMode());
		context.p = personalDataInput.run(context.p);
		break;
	}
	default:
		assert(false && "EditItemState::update: Unhandled context.menu!");
		break;
	}

	context.err = nullopt;
	return EditPhase::EditStart;
}

