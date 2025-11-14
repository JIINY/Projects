#include "UIUtils.hpp"
#include <string>
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


PersonalData UIUtils::processInputPersonalData(void (*title)()) //함수 포인터
{
	PersonalData p;
	optional<ResultVariant> err = nullopt;
	ResultVariant result;

	while (true)
	{
		executeFunc0(title);

		//이름 입력(필수) + 에러 출력
		frame_ = uiMsgH_.inputName(err);
		frame_(errorMsgH_);

		//이름 입력 처리
		string name = "";
		result = inputH_.getString(StringRule::EmptyDisallow, name);

		//에러 처리
		if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS))
		{
			err = wrapVariant<ResultVariant>(result);
			UIUtils::clearScreen();
			continue;
		}

		//초기화
		p.name = name;
		err = nullopt;
		break;
	}

	//나머지 데이터 입력
	frame_ = uiMsgH_.inputPhone();
	frame_(errorMsgH_);
	result = inputH_.getString(StringRule::EmptyAllow, p.phone);

	frame_ = uiMsgH_.inputAddress();
	frame_(errorMsgH_);
	result = inputH_.getString(StringRule::EmptyAllow, p.address);

	frame_ = uiMsgH_.inputZipCode();
	frame_(errorMsgH_);
	result = inputH_.getString(StringRule::EmptyAllow, p.zipCode);

	frame_ = uiMsgH_.inputEmail();
	frame_(errorMsgH_);
	result = inputH_.getString(StringRule::EmptyAllow, p.email);

	frame_ = uiMsgH_.short2Line();
	frame_(errorMsgH_);

	return p;
}

void UIUtils::clearScreen()
{
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


UIUtils::CharMetrics UIUtils::getCharMetrics(const string& str, size_t bytePos) 
{
	CharMetrics metrics;
	unsigned char c = static_cast<unsigned char>(str[bytePos]);

	//이번 문자는 몇 바이트인가
	if (c < 0x80)
	{
		metrics.bytes = 1; //1-byte ASCII (0xxxxxxx)
		metrics.width = 1;
	}
	else if ((c & 0xE0) == 0xC0)
	{
		metrics.bytes = 2; //2-byte (110xxxxx)
		metrics.width = 1;
	}
	else if ((c & 0xF0) == 0xE0)
	{
		metrics.bytes = 3; //3-byte (1110xxxx) 한글
		metrics.width = 2;
	}
	else if ((c & 0xF8) == 0xF0)
	{
		metrics.bytes = 4; //4-byte (11110xxx)
		metrics.width = 2;
	}
	else
	{
		metrics.bytes = 1; //깨진 UTF-8문자 또는 중간 바이트, 그냥 1바이트만 건너뜀
		metrics.width = 1;
	}

	//문자열 끝을 넘어서는지 확인
	if (bytePos + metrics.bytes > str.size())
	{
		return {1, 1}; //1byte 1칸으로 취급
	}
	return metrics;
}

size_t UIUtils::getDisplayWidth(const string& str)
{
	size_t currentBytePos = 0;
	size_t currentWidth = 0;

	while (currentBytePos < str.size())
	{
		auto [charBytes, charWidth] = getCharMetrics(str, currentBytePos);

		currentBytePos += charBytes;
		currentWidth += charWidth;
	}
	return currentWidth;
}

string UIUtils::truncateByWidth(const string& str, size_t maxWidth)
{
	if (str.empty())
	{
		return " - ";
	}

	//화면 너비 계산해서 처리
	size_t currentBytePos = 0;
	size_t currentWidth = 0;
	size_t safeCutOffBytes = 0;

	while (currentBytePos < str.size())
	{
		auto [charBytes, charWidth] = getCharMetrics(str, currentBytePos);

		//너비를 초과하면 멈춤
		if (currentWidth + charWidth > maxWidth) 
		{
			break; //문자열의 끝에서 문자가 깨지는 경우
		}

		currentBytePos += charBytes;
		currentWidth += charWidth;
		safeCutOffBytes = currentBytePos;
	}

	return str.substr(0, safeCutOffBytes);
}

string UIUtils::getPadding(const string& str, size_t maxWidth) 
{
	size_t currentWidth = getDisplayWidth(str);
	size_t padding = 0;
	if (maxWidth > currentWidth) 
	{
		padding = maxWidth - currentWidth;
	}
	return string(padding, ' ');
}

PersonalData UIUtils::subtractPersonalData(const PersonalData& p)
{
	PersonalData sub;

	sub.name = truncateByWidth(p.name, f.name);
	sub.phone = truncateByWidth(p.phone, f.phone);
	sub.address = truncateByWidth(p.address, f.address);
	sub.zipCode = truncateByWidth(p.zipCode, f.zipCode);
	sub.email = truncateByWidth(p.email, f.email);

	return sub;
}

PersonalData UIUtils::getPersonalDataTableFormat(const PersonalData& p)
{
	return subtractPersonalData(p);
}
