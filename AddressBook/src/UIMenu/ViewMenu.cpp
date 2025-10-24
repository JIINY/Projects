#include "ViewMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"


void ViewMenu::processView() {
	ContextData context;
	int length = book->getLength();
	int page = 0;

	while (page < length) {
		ui.clearScreen();
		context.err = nullopt;
		frame = uiMsgH.viewTitle(context.err);
		frame(errorMsgH);

		for (int i = page; i < length && i < page + 10; i++) {
			context.p = book->getPersonalDataAt(i);
			context.sub = ui.getPersonalDataTableFormat(context.p);

			int remainder = (i + 1) % 10;
			if (remainder == 5) {
				frame = uiMsgH.tableDataCenter(context.err, i + 1, context.sub);
			}
			else if (remainder == 0 || (i + 1) == length) {
				frame = uiMsgH.tableDataBottom(context.err, i + 1, context.sub);
				frame(errorMsgH);

				if (i + 1 == length) {
					frame = uiMsgH.tableComplete(context.err);
				}
				else {
					frame = uiMsgH.tableContinue(context.err);
				}
			}
			else {
				frame = uiMsgH.tableDataNormal(context.err, i + 1, context.sub);
			}
			frame(errorMsgH);
		}

		if ((page + 1) * 10 < length) {
			if (inputH.anyKeyOrQuit()) {
				frame = uiMsgH.tableStop(context.err);
				frame(errorMsgH);

				if (inputH.askYesNo()) {
					break;
				}
				else {
					continue;
				}
			}
		}
		else {
			inputH.getAnyKey();
			break;
		}

		page += 10;
	}
}
