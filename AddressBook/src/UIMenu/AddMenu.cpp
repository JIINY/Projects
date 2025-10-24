#include "AddMenu.hpp"
#include "../Common/VariantUtils.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "EditMenu.hpp"


void AddMenu::run() {
	processAddMenu();
}

void AddMenu::addMenuController(ContextData& context) {
	switch (context.menu) {
	case(0): {
		context.phase = AddPhase::InputAddCancle;
		context.err = nullopt;
		break;
	}
	case(1): {
		context.phase = AddPhase::AddSuccess;
		context.err = nullopt;
		break;
	}
	case(2): {
		context.phase = AddPhase::AddEditStart;
		context.err = nullopt;
		break;
	}
	default: {
		lastError = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(lastError);
		break;
	}
	}
}

void AddMenu::processAddMenu() {
	ContextData context;
	context.phase = wrapVariant<PhaseVariant>(AddPhase::InputStart);
	while (true) {
		AddPhase phase = unwrapVariant<AddPhase>(context.phase);
		switch (phase) {
		case(AddPhase::InputStart): {
			addController(context); //controller내에서 출력 실행
			break;
		}

		case(AddPhase::AddMenuSelect): {
			frame = uiMsgH.addConfirm(context.p);
			frame(errorMsgH);
			frame = uiMsgH.menuSelect(context.err);
			frame(errorMsgH);
			addController(context);
			break;
		}

		case(AddPhase::InputAddCancle): {
			frame = uiMsgH.addMenuLine(context.p);
			frame(errorMsgH);
			frame = uiMsgH.cancle(context.err, CancleType::Input);
			frame(errorMsgH);
			addController(context);
			break;
		}

		case(AddPhase::AddSuccess): {
			addController(context);
			break;
		}

		case(AddPhase::AddAgain): {
			frame = uiMsgH.addSuccess(book->getLastAdd() + 1, context.sub);
			frame(errorMsgH);
			frame = uiMsgH.addAgain(context.err);
			frame(errorMsgH);
			addController(context);
			break;
		}

		case(AddPhase::AddEditStart): {
			addController(context);
			break;
		}
		}

		UIUtils::clearScreen();
		if (phase == AddPhase::Exit) {
			break;
		}
	}
}

void AddMenu::addController(ContextData& context) {
	AddPhase phase = unwrapVariant<AddPhase>(context.phase);

	switch (phase) {
	case(AddPhase::InputStart): {
		context.p = ui.processInputPersonalData(OutputPrintHandler::printAddTitle);
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddMenuSelect);
		context.err = nullopt;
		break;
	}

	case(AddPhase::AddMenuSelect): {
		context.menu = inputH.getInt(IntRule::ZeroOrPositive);

		lastError = inputH.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			break;
		}

		context.err = nullopt;
		addMenuController(context);
		break;
	}

	case(AddPhase::InputAddCancle): {
		bool yesNo = inputH.askYesNo();
		lastError = inputH.getLastError();

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::Exit);
			context.err = nullopt;
			break;
		}

		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::InputAddCancle);
		}
		else {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddMenuSelect);
			context.err = nullopt;
		}
		break;
	}

	case(AddPhase::AddSuccess): {
		lastError = book->addPersonalData(context.p);

		if (!isVariantEqualTo <AddOperationResult>(lastError, AddOperationResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddAgain);
			break;
		}

		context.p = book->getPersonalDataAt(book->getLastAdd());
		context.sub = ui.getPersonalDataTableFormat(context.p);
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddAgain);
		context.err = nullopt;
		break;
	}

	case(AddPhase::AddAgain): {
		bool yesNo = inputH.askYesNo();
		lastError = inputH.getLastError();

		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddAgain);
			break;
		}

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::InputStart);
		}
		else {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::Exit);
		}
		context.err = nullopt;
		break;
	}

	case(AddPhase::AddEditStart): {
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddEditSelect);
		context.caller = EditDataCaller::AddEdit;
		context.err = nullopt;
		EditMenu edit;
		edit.editMenuPhaseController(context);
		break;
	}
	}
}
