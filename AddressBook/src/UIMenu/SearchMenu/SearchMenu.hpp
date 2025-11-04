#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ISearchState.hpp"

class AddressBookUi;

enum class SearchMode { Search, Edit, Delete };

class SearchMenu
{
public:
    void run(AddressBookUI& bookUI);

    ContextData& getContext() { return context_; }
    InputHandler& getInputH() { return inputH_; }
    ErrorPrintHandler& getErrorMsgH() { return errorMsgH_; }
    UIPrintHandler& getUIMsgH() { return uiMsgH_; }
    UIFrame& getUIFrame() { return frame_; }
    UIUtils& getUI() { return ui_; }
    
    AddressBookUI* getBookUI() { return bookUI_; }
    std::vector<std::pair<PersonalData, int>>& accessSearchResult() { return searchResult_; }
    void setMode(SearchMode mode) { mode_ = mode; }
    void drawLongTitle();
    void drawResultTable();
    void drawResultMsg();

private:
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
    SearchMode mode_ = SearchMode::Search;

    AddressBookUI* bookUI_ = nullptr;
    ContextData context_;
    std::unique_ptr<ISearchState> currentState_ = nullptr;
    std::vector<std::pair<PersonalData, int>> searchResult_;

    void transitionTo(SearchPhase nextPhase);
};
