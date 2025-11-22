#include "ViewDeleteState.hpp"
#include <variant>
#include <optional>
#include <utility>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ViewMenu.hpp"
#include "../DeleteMenu/DeleteMenu.hpp"
using namespace std;


ViewPhase ViewDeleteState::update()
{
    auto& context = owner_.getContext();
    auto* bookUI = owner_.getBookUI();
    
    int index = context.menu;
    PersonalData dataToDelete = bookUI->getPersonalDataAt(index);
    pair<int, string> resultInfo = make_pair(index + 1, dataToDelete.name);

    DeleteMenu deleteMenu;
    RemoveOperationResult result = deleteMenu.run(*bookUI, index, resultInfo);

    context.err = wrapVariant<ResultVariant>(result);
    return ViewPhase::List;
}
