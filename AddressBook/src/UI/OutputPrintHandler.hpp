#pragma once
#include <string>

enum class CancleType;
struct PersonalData;


class OutputPrintHandler {
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
    static void printMenuSelect();
    static void printCancle(const CancleType cancle);

    static void printPersonalData(const PersonalData& p);
    static void printPersonalEdit(const PersonalData& p);

    static void printMainMenu();
    static void printSearchMenu();
    static void printSearchSubMenu();
    static void printSearchEmptySubMenu();

    static void printInputName();
    static void printInputPhone();
    static void printInputAddress();
    static void printInputZipCode();
    static void printInputEmail();

    static void printAddMenu();
    static void printAddSuccess(const int i, const PersonalData& p);
    static void printAddAgain();
    static void printAddEditConfirm();
    static void printAddConfirm();
    
    static void printTableTitle();
    static void printTablePersonalData(const int i, const PersonalData& p);
    static void printTableSearchEnd();
    static void printTableContinue();
    static void printTableComplete();
    static void printTableStop();

    static void printEditItem();
    static void printEditName();
    static void printEditPhone();
    static void printEditAddress();
    static void printEditZipCode();
    static void printEditEmail();
    static void printEditInput();
    static void printEditAgain();
    static void printEditConfirm();
    static void printEditSuccess(int i, const std::string& name);

    static void printDeleteItem();
    static void printDeleteConfirm(int i, const std::string& name);
    static void printDeleteSuccess(int i, const std::string& name);
    static void printSearchAgain();
    static void printSearchEmpty();

protected:


private:
    static constexpr const char* version = "v0.0.1";
};
