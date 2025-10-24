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
		lastError_ = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(lastError_);
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
			frame_ = uiMsgH_.addConfirm(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			addController(bookUI, context);
			break;
		}

		case(AddPhase::InputAddCancle): {
			frame_ = uiMsgH_.addMenuLine(context.p);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.cancle(context.err, CancleType::Input);
			frame_(errorMsgH_);
			addController(bookUI, context);
			break;
		}

		case(AddPhase::AddSuccess): {
			addController(context);
			break;
		}

		case(AddPhase::AddAgain): {
			addController(context);
			frame_ = uiMsgH_.addSuccess(bookUI.getLastAdd() + 1, context.sub);
			frame_(errorMsgH_);
			frame_ = uiMsgH_.addAgain(context.err);
			frame_(errorMsgH_);
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
		context.p = ui_.processInputPersonalData(OutputPrintHandler::printAddTitle);
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddMenuSelect);
		context.err = nullopt;
		break;
	}

	case(AddPhase::AddMenuSelect): {
		context.menu = inputH_.getInt(IntRule::ZeroOrPositive);

		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			break;
		}

		context.err = nullopt;
		addMenuController(context);
		break;
	}

	case(AddPhase::InputAddCancle): {
		bool yesNo = inputH_.askYesNo();
		lastError_ = inputH_.getLastError();

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(AddPhase::Exit);
			context.err = nullopt;
			break;
		}

		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
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

		if (!isVariantEqualTo <AddOperationResult>(lastError_, AddOperationResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<PhaseVariant>(AddPhase::AddAgain);
			break;
		}

		context.p = book->getPersonalDataAt(book->getLastAdd());
		context.sub = ui_.getPersonalDataTableFormat(context.p);
		context.phase = wrapVariant<PhaseVariant>(AddPhase::AddAgain);
		context.err = nullopt;
		break;
	}

	case(AddPhase::AddAgain): {
		bool yesNo = inputH_.askYesNo();
		lastError_ = inputH_.getLastError();

		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
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
