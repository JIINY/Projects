#pragma once
#include "../Common/ResultEnums.hpp"
#include "../IO/InputHandler.hpp"
#include "../IO/ErrorPrintHandler.hpp"
#include "UIPrintHandler.hpp"
#include "UIOutput.hpp"

struct PersonalData;

class UIUtils {
public:
    static void clearScreen();
    static void executeFunc0(void(*func)()) { func(); }
    PersonalData subtractPersonalData(const PersonalData& p);
    PersonalData processInputPersonalData(void (*title)());
    PersonalData getPersonalDataTableFormat(const PersonalData& p);

protected:
    std::string eucKrSubStr(const std::string& str, size_t maxBytes);

private:
    ResultVariant lastError_;
    UIFrame frame_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
};
