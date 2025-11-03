#include "AddSuccessState.hpp"
#include <optional>
#include "../../Common/VariantUtils.hpp"
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "AddMenu.hpp"
using namespace std;


void AddSuccessState::draw() {} //AddAgainState°¡ ´ã´ç

AddPhase AddSuccessState::update() 
{
	auto& context = owner_.getContext();
	auto* bookUI = owner_.getAddressBookUI();

	ResultVariant error = bookUI->addPersonalData(context.p);
	if (!isVariantEqualTo<AddOperationResult>(error, AddOperationResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
	}
	else 
	{
		context.err = nullopt;
		context.p = bookUI->getPersonalDataAt(bookUI->getLastAdd());
		context.sub = owner_.getUI().getPersonalDataTableFormat(context.p);
	}
	return AddPhase::AddAgain;
}
