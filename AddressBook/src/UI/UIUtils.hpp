#pragma once
#include "../Common/ResultEnums.hpp"
#include "../IO/InputHandler.hpp"
#include "../IO/ErrorPrintHandler.hpp"
#include "UIPrintHandler.hpp"
#include "UIOutput.hpp"

struct PersonalData;

class UIUtils
{
public:
    static void clearScreen();
    static void executeFunc0(void(*func)()) { func(); }
    PersonalData subtractPersonalData(const PersonalData& p);
    PersonalData processInputPersonalData(void (*title)());
    PersonalData getPersonalDataTableFormat(const PersonalData& p);
    size_t getDisplayWidth(const std::string& str);
    std::string truncateByWidth(const std::string& str, size_t maxWidth);
    std::string getPadding(const std::string& str, size_t maxWidth);

private:
    UIFrame frame_{};
    InputHandler inputH_{};
    ErrorPrintHandler errorMsgH_{};
    UIPrintHandler uiMsgH_{};

    struct CharMetrics 
    {
        size_t bytes = 0;
        size_t width = 0;
    };
    static CharMetrics getCharMetrics(const std::string& str, size_t bytePos);
};
