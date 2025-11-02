#pragma once
#include <memory>
#include <optional>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "States/IDataInputState.hpp"


class PersonalDataInput 
{
public:
	PersonalDataInput(InputMode mode) : mode_(mode) {}

	PersonalData run(std::optional<PersonalData> initialData);
	InputMode getMode() const { return mode_; }

	InputHandler& getInputH() { return inputH_; }
	ErrorPrintHandler& getErrorMsgH() { return errorMsgH_; }
	UIPrintHandler& getUIMsgH() { return uiMsgH_; }
	UIFrame& getUIFrame() { return frame_; }
	UIUtils& getUI() { return ui_; }

	void setName(const std::string& name) { data_.name = name; }
	void setPhone(const std::string& phone) { data_.phone = phone; }
	void setAddress(const std::string& address) { data_.address = address; }
	void setZipCode(const std::string& zipCode) { data_.zipCode = zipCode; }
	void setEmail(const std::string& email) { data_.email = email; }

	std::optional<ResultVariant> getLastError() const { return lastError_; }
	void setLastError(const ResultVariant& error) { lastError_ = error; }
	void setLastError(std::nullopt_t) { lastError_ = std::nullopt; }


private:
	InputHandler inputH_;
	UIPrintHandler uiMsgH_;
	ErrorPrintHandler errorMsgH_;
	UIFrame frame_;
	UIUtils ui_;

	PersonalData data_{};
	InputMode mode_;
	std::optional<ResultVariant> lastError_ = std::nullopt;
	std::unique_ptr<IDataInputState> currentState_ = nullptr;

	void transitionTo(DataInputPhase nextPhase);
};
