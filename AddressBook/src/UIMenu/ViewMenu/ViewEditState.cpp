#include "ViewEditState.hpp"
#include <variant>
#include <optional>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ViewMenu.hpp"
#include "../EditMenu/EditMenu.hpp"
using namespace std;


ViewPhase ViewEditState::update() 
{
    auto& context = owner_.getContext();
    int& page = owner_.getPage();

    auto* bookUI = owner_.getBookUI();
    int index = context.menu;
    PersonalData dataToEdit = bookUI->getPersonalDataAt(index);

    EditMenu editMenu(InputMode::Edit);
    optional<PersonalData> editResult = editMenu.run(*bookUI, dataToEdit);

    if (editResult.has_value()) 
    {
        PersonalData editedData = editResult.value();
        AddOperationResult addResult = bookUI->extractAddressBook().edit(index, editedData);
        context.err = wrapVariant<ResultVariant>(addResult);

        if (addResult == AddOperationResult::SUCCESS) 
        {
            int newIndex = bookUI->extractAddressBook().getLastAdd();
            if (newIndex != -1) 
            {
                context.menu = newIndex;
                page = newIndex / 10;
            }
        }
    }
    else 
    {
        context.err = nullopt;
    }
    return ViewPhase::List;
}
