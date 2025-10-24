#include "EditMenu.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../Common/VariantUtils.hpp"//log
using namespace std;


void EditMenu::editMenuPhaseController(ContextData& context) {
	if (context.caller == EditDataCaller::AddEdit) {
		processAddEditMenu(context);
	}
	if (context.caller == EditDataCaller::Edit) {
		processEditMenu(context);
	}
}

void EditMenu::processAddEditMenu(ContextData& context) {
	while (true) {
		AddPhase addPhase = unwrapVariant<AddPhase>(context.phase);

		switch (addPhase) {
		case(AddPhase::AddEditSelect): {
			frame = uiMsgH.addEdit(context.p);
			frame(errorMsgH);
			frame = uiMsgH.editInput(context.err);
			frame(errorMsgH);
			addEditController(context);
			break;
		}
		case(AddPhase::AddEditMenu): {
			frame = uiMsgH.addEditLine(context.p);
			frame(errorMsgH);
			addEditController(context);
			break;
		}
		case(AddPhase::CancleConfirm): {
			frame = uiMsgH.addEditLine(context.p);
			frame(errorMsgH);
			frame = uiMsgH.cancle(context.err, CancleType::Edit);
			frame(errorMsgH);
			addEditController(context);
			break;
		}
		case(AddPhase::AddEditConfirm): {
			addEditController(context);
			break;
		}
		case(AddPhase::AddEditAgain):{
			frame = uiMsgH.addEditAgain(context.err, book->getLastAdd() + 1, context.sub);
			frame(errorMsgH);
			addEditController(context);
			break;
		}
		}

		UIUtils::clearScreen();
		if (addPhase == AddPhase::Exit || addPhase == AddPhase::InputStart) {
			break;
		}
	}
}

void EditMenu::addEditController(ContextData& context) {
	switch (unwrapVariant<AddPhase>(context.phase)) {
	case(AddPhase::AddEditSelect): {
		context.menu = -1;
		context.menu = inputH.getInt(IntRule::ZeroOrPositive);
		lastError = inputH.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditSelect);
			break;
		}
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditMenu);
		context.err = nullopt;
		break;
	}
	case(AddPhase::AddEditMenu): {
		if (context.menu == 0) {
			context.err = nullopt;
			context.phase = wrapVariant<PhaseVariant>(AddPhase::CancleConfirm);
		}
		else if (context.menu == 9) {
			context.err = nullopt;
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditConfirm);
		}
		else if (context.menu == -1) {
			context.err = wrapVariant<ResultVariant>(InputResult::EMPTY_INT);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditSelect);
		}
		else {
			processEditData(context);
			editDataController(context);

			if (isVariantEqualTo<AddEditResult>(context.err, AddEditResult::EMPTY_NAME)) {
				context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditMenu);				
			}
			else {
				context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditSelect);
				context.menu = -1;
			}
		}
		break;
	}
	case(AddPhase::AddEditConfirm): {
		lastError = book->addPersonalData(context.p);

		if (!isVariantEqualTo <AddOperationResult>(lastError, AddOperationResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditConfirm);
			break;
		}

		context.p = book->getPersonalDataAt(book->getLastAdd());
		context.sub = ui.getPersonalDataTableFormat(context.p);
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditAgain);
		context.err = nullopt;
		break;
	}
	case(AddPhase::AddEditAgain): {
		bool yesNo = inputH.askYesNo();
		lastError = inputH.getLastError();

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::InputStart);
			context.err = nullopt;
			break;
		}

		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditAgain);
		}
		else {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::Exit);
			context.err = nullopt;
		}
		break;
	}
	case(AddPhase::CancleConfirm): {
		bool yesNo = inputH.askYesNo();
		lastError = inputH.getLastError();

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::Exit);
			context.err = nullopt;
			break;
		}

		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::CancleConfirm);
		}
		else {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditSelect);
			context.err = nullopt;
		}
		break;
	}
	}
}

void EditMenu::processEditData(ContextData& context) {

	switch (context.menu) {
	case 1: {
		frame = uiMsgH.editName(context.err);
		frame(errorMsgH);
		break;
	}
	case 2: {
		frame = uiMsgH.editPhone(context.err);
		frame(errorMsgH);
		break;
	}
	case 3: {
		frame = uiMsgH.editAddress(context.err);
		frame(errorMsgH);
		break;
	}
	case 4: {
		frame = uiMsgH.editZipCode(context.err);
		frame(errorMsgH);
		break;
	}
	case 5: {
		frame = uiMsgH.editEmail(context.err);
		frame(errorMsgH);
		break;
	}
	case 6: {
		ui.clearScreen();
		break;
	}
	case 9: {
		break;
	}
	}
}

void EditMenu::assignEditNameEmptyError(ContextData& context) {
	if (context.caller == EditDataCaller::AddEdit) {
		context.err = wrapVariant<ResultVariant>(AddEditResult::EMPTY_NAME);
	}
	else {
		context.err = wrapVariant<ResultVariant>(EditDataResult::EMPTY_NAME);
	}
}

void EditMenu::editDataController(ContextData& context) {
	if (context.menu == -1 && context.err.has_value() &&
		holds_alternative<InputResult>(*context.err)) { //InputResult인지 확인

		if (get<InputResult>(*context.err) != InputResult::SUCCESS) {
			return;
		}
	}
		
	switch (context.menu) {
	case 1: {
		string s = inputH.getString(StringRule::EmptyDisallow);
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		if (s == "") {
			assignEditNameEmptyError(context);
			break;
		}
		context.p.name = s;
		context.err = nullopt;
		break;
	}
	case 2: {
		string s = inputH.getString(StringRule::EmptyAllow);
		context.p.phone = s;
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		break;
	}
	case 3: {
		string s = inputH.getString(StringRule::EmptyAllow);
		context.p.address = s;
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		break;
	}
	case 4: {
		string s = inputH.getString(StringRule::EmptyAllow);
		context.p.zipCode = s;
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		break;
	}
	case 5: {
		string s = inputH.getString(StringRule::EmptyAllow);
		context.p.email = s;
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		break;
	}
	case 6: {
		context.p = ui.processInputPersonalData(OutputPrintHandler::printAddEditTitle);
		context.err = wrapVariant<ResultVariant>(inputH.getLastError());
		break;
	}
	default:
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
		break;
	}
}

void EditMenu::processEditMenu(ContextData& context) {
	EditPhase editPhase = EditPhase::EditStart;
}
