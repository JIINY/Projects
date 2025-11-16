#pragma once
#include <string>

enum class ActionType;
struct PersonalData;


class OutputPrintHandler 
{
public:
    static std::string getVersion() { return version; }

    static void printEnter();
    static void printShort1Line();
    static void printShort2Line();
    static void printLong1Line();
    static void printLong2Line();

    static void printAddTitle();
    static void printAddEditTitle();
    static void printViewTitle();
    static void printEditTitle();
    static void printSearchTitle();
    static void printSearchLongTitle();
    static void printEditLongTitle();
    static void printDeleteLongTitle();
    static void printMenuSelect();
    static void printCancel(const ActionType action);
    static void printTableAction(const ActionType action);

    static void printPersonalData(const PersonalData& p);
    static void printPersonalEdit(const PersonalData& p);

    static void printMainMenu();
    static void printSearchMenu();
    static void printSearchSubMenu();
    static void printSearchEmptySubMenu();
    static void printSearchEditSubMenu();
    static void printSearchDeleteSubMenu();

    static void printInputName();
    static void printInputPhone();
    static void printInputAddress();
    static void printInputZipCode();
    static void printInputEmail();
    static void printInputCommand();

    static void printAddMenu();
    static void printAddSuccess(const int i, const PersonalData& p);
    static void printAddAgain();
    static void printAddEditConfirm();
    static void printAddConfirm();
    
    static void printTableTitle();
    static void printTablePersonalData(const int i, const PersonalData& p);
    static void printTableSearchEnd();
    static void printTableCommand();
    static void printTableComplete();
    static void printTableStop();
    static void printTableEditSuccess(int i, const std::string& name);
    static void printTableDeleteSuccess(int i, const std::string& name);

    static void printEditItem();
    static void printEditName();
    static void printEditPhone();
    static void printEditAddress();
    static void printEditZipCode();
    static void printEditEmail();
    static void printEditInput();
    static void printEditAgain();
    static void printEditConfirm();

    static void printDeleteItem();
    static void printDeleteConfirm(int i, const std::string& name);
    static void printSearchAgain();
    static void printSearchEmpty();

protected:


private:
    static constexpr const char* version = "v0.0.1";
};

