#include "ViewEmptyState.hpp"
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ViewMenu.hpp"
using namespace std;


void ViewEmptyState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();


	frame = uiMsgH.viewTitle(context.err);
	frame(errorMsgH);

	frame = uiMsgH.searchEmpty();
	frame(errorMsgH);
}

ViewPhase ViewEmptyState::update()
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	inputH.getAnyKey();

	context.err = nullopt;
    return ViewPhase::Exit;
}
