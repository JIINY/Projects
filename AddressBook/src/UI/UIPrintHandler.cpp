#include "UIPrintHandler.hpp"
#include <optional>
#include <string>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "OutputPrintHandler.hpp"
#include "UIOutput.hpp"
using namespace std;



UIFrame UIPrintHandler::mainMenu() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printMainMenu();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::searchMenu() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printSearchTitle();
			OutputPrintHandler::printSearchMenu();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::menuSelect(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printMenuSelect();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::cancle(optional<ResultVariant> err, CancleType action) 
{
	return UIFrame{
		[action]{
			OutputPrintHandler::printCancle(action);
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::inputName(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printInputName();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::inputPhone() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printInputPhone();
		}, EnterType::None, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::inputAddress() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printInputAddress();
		}, EnterType::None, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::inputZipCode() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printInputZipCode();
		}, EnterType::None, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::inputEmail() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printInputEmail();
		}, EnterType::None, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::short1Line() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printShort1Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::short2Line() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printShort2Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::addConfirm(const PersonalData& p) 
{
	return UIFrame{
		[p]{
			OutputPrintHandler::printAddTitle();
			OutputPrintHandler::printPersonalData(p);
			OutputPrintHandler::printAddMenu();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::addMenuLine(const PersonalData& p) 
{
	return UIFrame{
		[p]{
			OutputPrintHandler::printAddTitle();
			OutputPrintHandler::printPersonalData(p);
			OutputPrintHandler::printAddMenu();
			OutputPrintHandler::printMenuSelect();
			OutputPrintHandler::printEnter();
			OutputPrintHandler::printShort1Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::addSuccess(const int i, const PersonalData& p) 
{
	return UIFrame{
		[i, p]{
			OutputPrintHandler::printAddTitle();
			OutputPrintHandler::printPersonalData(p);
			OutputPrintHandler::printAddMenu();
			OutputPrintHandler::printMenuSelect();
			OutputPrintHandler::printEnter();
			OutputPrintHandler::printAddSuccess(i, p);
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::addAgain(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printAddAgain();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::addEditAgain(optional<ResultVariant> err, const int i, const PersonalData& p) 
{
	return UIFrame{
		[i, p]{
			OutputPrintHandler::printAddEditTitle();
			OutputPrintHandler::printPersonalEdit(p);
			OutputPrintHandler::printAddEditConfirm();
			OutputPrintHandler::printEditInput();
			OutputPrintHandler::printEnter();
			OutputPrintHandler::printAddSuccess(i, p);
			OutputPrintHandler::printAddAgain();
		}, EnterType::ErrorOnly, err, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::addEdit(const PersonalData& p) 
{
	return UIFrame{
		[p]{
			OutputPrintHandler::printAddEditTitle();
			OutputPrintHandler::printPersonalEdit(p);
			OutputPrintHandler::printAddEditConfirm();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::editInput(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditInput();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::addEditLine(const PersonalData& p)
{
	return UIFrame{
		[p]{
			OutputPrintHandler::printAddEditTitle();
			OutputPrintHandler::printPersonalEdit(p);
			OutputPrintHandler::printAddEditConfirm();
			OutputPrintHandler::printEditInput();
			OutputPrintHandler::printEnter();
			OutputPrintHandler::printShort1Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::editTitle()
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditTitle();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::personalEdit(const PersonalData& p)
{
	return UIFrame{
		[p] {
			OutputPrintHandler::printPersonalEdit(p);
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::editConfirm()
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditConfirm();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::editName(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditName();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::editPhone(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditPhone();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::editAddress(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditAddress();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::editZipCode(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditZipCode();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::editEmail(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printEditEmail();
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::editSuccess(const int i, const string& name)
{
	return UIFrame{
		[i, name]{
			OutputPrintHandler::printEditSuccess(i, name);
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::viewTitle(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printViewTitle();
			OutputPrintHandler::printTableTitle();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableDataNormal(optional<ResultVariant> err, const int i, const PersonalData& p) 
{
	return UIFrame{
		[i, p]{
			OutputPrintHandler::printTablePersonalData(i, p);
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableDataCenter(optional<ResultVariant> err, const int i, const PersonalData& p) 
{
	return UIFrame{
		[i, p]{
			OutputPrintHandler::printTablePersonalData(i, p);
			OutputPrintHandler::printLong1Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableDataBottom(optional<ResultVariant> err, const int i, const PersonalData& p) 
{
	return UIFrame{
		[i, p]{
			OutputPrintHandler::printTablePersonalData(i, p);
			OutputPrintHandler::printLong2Line();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableComplete(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printTableComplete();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableSearchEnd(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printTableSearchEnd();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableContinue(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printTableContinue();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::tableStop(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printTableStop();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::searchTitle() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printSearchTitle();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::searchResult() 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printSearchLongTitle();
			OutputPrintHandler::printTableTitle();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::searchSubMenu()
{
	return UIFrame{
		[]{
			OutputPrintHandler::printShort2Line();
			OutputPrintHandler::printSearchSubMenu();
		}, EnterType::Both, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::searchEmptySubMenu()
{
	return UIFrame{
		[]{
			OutputPrintHandler::printShort2Line();
			OutputPrintHandler::printSearchEmptySubMenu();
		}, EnterType::Both, nullopt, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::searchEdit(optional<ResultVariant> err)
{
	return UIFrame{		
		[]{
			OutputPrintHandler::printEditItem();
		}, EnterType::Both, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::searchDelete(optional<ResultVariant> err)
{
	return UIFrame{
		[]{
			OutputPrintHandler::printDeleteItem();
		}, EnterType::Both, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::searchAgain(optional<ResultVariant> err) 
{
	return UIFrame{
		[]{
			OutputPrintHandler::printSearchAgain();
		}, EnterType::None, err, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::searchEmpty()
{
	return UIFrame{
		[]{
			OutputPrintHandler::printSearchEmpty();
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}

UIFrame UIPrintHandler::deleteConfirm(optional<ResultVariant> err, const int i, const string& name) 
{
	return UIFrame{
		[i, name] {
			OutputPrintHandler::printDeleteConfirm(i, name);
		}, EnterType::None, err, RenderOrder::ErrorToRender
	};
}

UIFrame UIPrintHandler::deleteSuccess(const int i, const string& name) 
{
	return UIFrame{
		[i, name] {
			OutputPrintHandler::printDeleteSuccess(i, name);
		}, EnterType::None, nullopt, RenderOrder::RenderToError
	};
}
