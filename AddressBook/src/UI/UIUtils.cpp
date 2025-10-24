#include "UIUtils.hpp"
#include <iostream>
#include <cstdlib>
#include <optional>
#ifdef _WIN32
#define byte win_byte //Windows.h 전에 정의
#include <Windows.h>
#undef byte
#endif
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "../IO/InputHandler.hpp"
#include "../IO/ErrorPrintHandler.hpp"
#include "UICommonData.hpp"
#include "UIPrintHandler.hpp"
using namespace std;


PersonalData UIUtils::processInputPersonalData(void (*title)()) { //함수 포인터
	PersonalData p;
	optional<ResultVariant> err = nullopt;

	while (true) {
		executeFunc0(title);

		//이름 입력(필수) + 에러 출력
		frame_ = uiMsgH_.inputName(err);
		frame_(errorMsgH_);

		//이름 입력 처리
		p.name = inputH_.getString(StringRule::EmptyDisallow);
		lastError_ = inputH_.getLastError();

		//에러 처리
		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) {
			err = wrapVariant<ResultVariant>(lastError_);
			UIUtils::clearScreen();
			continue;
		}

		//초기화
		err = nullopt;
		break;
	}

	//나머지 데이터 입력
	frame_ = uiMsgH_.inputPhone();
	frame_(errorMsgH_);
	p.phone = inputH_.getString(StringRule::EmptyAllow);

	frame_ = uiMsgH_.inputAddress();
	frame_(errorMsgH_);
	p.address = inputH_.getString(StringRule::EmptyAllow);

	frame_ = uiMsgH_.inputZipCode();
	frame_(errorMsgH_);
	p.zipCode = inputH_.getString(StringRule::EmptyAllow);

	frame_ = uiMsgH_.inputEmail();
	frame_(errorMsgH_);
	p.email = inputH_.getString(StringRule::EmptyAllow);

	frame_ = uiMsgH_.short2Line();
	frame_(errorMsgH_);

	return p;
}

void UIUtils::clearScreen() {
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD written;
	COORD home = { 0, 0 };

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hConsole, ' ', size, home, &written);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, size, home, &written);
	SetConsoleCursorPosition(hConsole, home);
#else
	// ANSI Escape Code (Unix-like 시스템)
	std::cout << "\033[2J\033[1;1H"; 
#endif
}


string UIUtils::eucKrSubStr(const string& str, size_t maxBytes) {
	size_t i = 0;

	if (str == "") {
		return " - ";
	}

	while (i < maxBytes && i < str.size()) {
		unsigned char c = static_cast<unsigned char>(str[i]);

		if (c >= 0x80) {
			if (i + 1 >= maxBytes || i + 1 >= str.size()) { break; } //짝 안 맞는 한글이면 자름
			i += 2;
		}
		else {
			i += 1; //ASCII
		}
	}

	return str.substr(0, i);
}


PersonalData UIUtils::subtractPersonalData(const PersonalData& p) {
	PersonalData sub;

	sub.name = eucKrSubStr(p.name, f.name);
	sub.phone = eucKrSubStr(p.phone, f.phone);
	sub.address = eucKrSubStr(p.address, f.address);
	sub.zipCode = eucKrSubStr(p.zipCode, f.zipCode);
	sub.email = eucKrSubStr(p.email, f.email);

	return sub;
}

PersonalData UIUtils::getPersonalDataTableFormat(const PersonalData& p) {
	return subtractPersonalData(p);
}
