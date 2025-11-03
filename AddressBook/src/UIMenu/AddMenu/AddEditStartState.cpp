#include "AddEditStartState.hpp"
#include <optional>
#include <memory>
#include "../../Common/VariantUtils.hpp"
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"

#include "AddMenu.hpp"
#include "../EditMenu/EditMenu.hpp"
using namespace std;


void AddEditStartState::draw() {} //EditMenu°¡ Ã³¸®

AddPhase AddEditStartState::update() 
{
	auto& context = owner_.getContext();
	auto* bookUI = owner_.getAddressBookUI();

	EditMenu editMenu(InputMode::AddEdit);
	optional<PersonalData> editResult = editMenu.run(*bookUI, context.p);

	if (editResult.has_value()) 
	{
		context.p = editResult.value();
		context.err = nullopt;
		return AddPhase::AddSuccess;
	}
	else 
	{
		context.err = nullopt;
		return AddPhase::AddReview;
	}
}
