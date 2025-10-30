#pragma once
#include <memory>
#include <optional>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UIMenu/States/IDataInputState.hpp"


class PersonalDataInput 
{
public:
	PersonalData run(std::optional<PersonalData> initialData);

	PersonalData& getData() { return data_; }
	InputHandler& getInputH() { return inputH_; }
	ErrorPrintHandler& getErrorMsgH() { return errorMsgH_; }
	UIPrintHandler& getUIMsgH() { return uiMsgH_; }
	UIFrame& getUIFrame() { return frame_; }
	UIUtils& getUI() { return ui_; }

	ResultVariant getLastError() const { return lastError_; }
	void setLastError(const ResultVariant& error) { lastError_ = error; }


private:
	InputHandler inputH_;
	UIPrintHandler uiMsgH_;
	ErrorPrintHandler errorMsgH_;
	UIFrame frame_;
	UIUtils ui_;

	PersonalData data_;
	ResultVariant lastError_;
	std::unique_ptr<IDataInputState> currentState_;

	void transitionTo(DataInputPhase nextPhase);
};
