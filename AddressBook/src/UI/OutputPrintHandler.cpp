#pragma once
#include "OutputPrintHandler.hpp"
#include <iostream>
#include <iomanip>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "UICommonData.hpp"
using namespace std;



//public
void OutputPrintHandler::printEnter() {
	cout << endl;
}
void OutputPrintHandler::printShort1Line() {
	cout << "---------------------------------------" << endl;
}
void OutputPrintHandler::printShort2Line() {
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printLong1Line() {
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

void OutputPrintHandler::printLong2Line() {
	cout << "============================================================================================================" << endl;
}

void OutputPrintHandler::printAddTitle() {
    cout << "=======================================" << endl;
    cout << left << setw(20) << "주소록: 추가 ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}
void OutputPrintHandler::printAddEditTitle() {
    cout << "=======================================" << endl;
    cout << left << setw(20) << "주소록: 추가 수정 ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}
void OutputPrintHandler::printEditTitle() {
    cout << "=======================================" << endl;
    cout << left << setw(20) << "주소록: 수정 ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchTitle() {
	cout << "=======================================" << endl;
	cout << left << setw(20) << "주소록: 찾기 ";
	cout << right << setw(18) << version << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchLongTitle() {
	cout << "============================================================================================================" << endl;
	cout << left << setw(20) << "주소록: 찾기 ";
	cout << right << setw(87) << version << endl;
	cout << "============================================================================================================" << endl;
}

void OutputPrintHandler::printViewTitle() {
	cout << "============================================================================================================" << endl;
	cout << left << setw(20) << "주소록: 보기 ";
	cout << right << setw(87) << version << endl;
	cout << "============================================================================================================" << endl;
}

void OutputPrintHandler::printMenuSelect() {
    cout << "메뉴를 선택해 주세요: ";
}

void OutputPrintHandler::printCancle(CancleType action) {
	switch (action) {
	case CancleType::Input:
		cout << "입력을";
		break;
	case CancleType::Edit:
		cout << "수정을";
		break;
	case CancleType::Delete:
		cout << "삭제를";
		break;
	case CancleType::AddConfirm:
		cout << "추가를";
		break;
	}
    cout << " 취소하시겠습니까? (Y/N): ";
}



void OutputPrintHandler::printMainMenu() {
    cout << "=======================================" << endl;
    cout << " 주소록 " << setw(30) << version << endl;
    cout << "=======================================" << endl;
    cout << "[1] 주소록 추가" << endl;
    cout << "[2] 주소록 보기" << endl;
    cout << "[3] 주소록 찾기 + 수정/삭제" << endl;
    cout << "[0] 종료" << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchMenu() {
	cout << "[1] 이름으로 찾기" << endl;
	cout << "[2] 휴대폰 번호로 찾기" << endl;
	cout << "[3] 주소로 찾기" << endl;
	cout << "[4] 우편번호로 찾기" << endl;
	cout << "[5] 이메일로 찾기" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[0] 취소하고 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printInputName() {
	cout << "이    름: ";
}
void OutputPrintHandler::printInputPhone() {
	cout << "핸 드 폰: ";
}
void OutputPrintHandler::printInputAddress() {
	cout << "주    소: ";
}
void OutputPrintHandler::printInputZipCode() {
	cout << "우편번호: ";
}
void OutputPrintHandler::printInputEmail() {
	cout << "이 메 일: ";
}

void OutputPrintHandler::printPersonalData(const PersonalData& p) {
    cout << "이    름: " << p.name << endl;
    cout << "핸 드 폰: " << p.phone << endl;
    cout << "주    소: " << p.address << endl;
    cout << "우편번호: " << p.zipCode << endl;
    cout << "이 메 일: " << p.email << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printAddMenu() {
	cout << "[1] 추가하기" << endl;
	cout << "[2] 입력 수정하기" << endl;
	cout << "[0] 취소하고 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchSubMenu() {
	cout << "[1] 항목 수정하기" << endl;
	cout << "[2] 항목 삭제하기" << endl;
	cout << "[9] 다시 검색하기" << endl;
	cout << "[0] 메인 메뉴로 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchEmptySubMenu() {
	cout << "[9] 다시 검색하기" << endl;
	cout << "[0] 메인 메뉴로 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printTableTitle() {
	cout << " No.   Name        PhoneNumber      Address                                ZipCode    E-Mail   " << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
}

void OutputPrintHandler::printTablePersonalData(const int i, const PersonalData& p) {
	cout << left;
	cout << setw(f.no) << i << setw(f.name) << p.name << setw(f.phone) << p.phone << setw(f.address) << p.address
		<< setw(f.zipCode) << p.zipCode << setw(f.email) << p.email << endl;
}

void OutputPrintHandler::printTableContinue() {
	cout << "엔터 키를 누르면 다음 페이지로 넘어갑니다. 중단은 Q를 누르세요. ";
}

void OutputPrintHandler::printTableComplete() {
	cout << "주소록의 끝입니다. 엔터 키를 누르면 메인 메뉴로 돌아갑니다. ";
}

void OutputPrintHandler::printTableSearchEnd() {
	cout << "검색이 끝났습니다. 수정/삭제하시려면 메뉴를 선택해 주세요. ";
}

void OutputPrintHandler::printTableStop() {
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "주소록 보기를 종료하시겠습니까? (Y/N) ";
}

void OutputPrintHandler::printAddSuccess(const int i, const PersonalData& p) {
	cout << "============================================================================================================" << endl;
	cout << " No.   Name        PhoneNumber      Address                                ZipCode    E-Mail   " << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(f.no) << i << setw(f.name) << p.name << setw(f.phone) << p.phone << setw(f.address) << p.address
		<< setw(f.zipCode) << p.zipCode << setw(f.email) << p.email << endl;
	cout << "============================================================================================================" << endl;
	cout << "[완료] 주소록에 " << p.name << "이/가 추가되었습니다." << endl;
	cout << "---------------------------------------" << endl;
}

void OutputPrintHandler::printAddAgain() {
	cout << "이어서 추가하시겠습니까? (Y/N): ";
}

void OutputPrintHandler::printPersonalEdit(const PersonalData& p) {
	cout << "[1] 이    름: " << p.name << endl;
	cout << "[2] 핸 드 폰: " << p.phone << endl;
	cout << "[3] 주    소: " << p.address << endl;
	cout << "[4] 우편번호: " << p.zipCode << endl;
	cout << "[5] 이 메 일: " << p.email << endl;
	cout << "[6] 전부 수정" << endl;
	cout << "---------------------------------------" << endl;
}

void OutputPrintHandler::printAddEditConfirm() {
	cout << "[9] 수정 완료하고 추가하기" << endl;
	cout << "[0] 취소하고 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printEditConfirm() {
	cout << "[9] 수정 완료" << endl;
	cout << "[0] 취소하고 돌아가기" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printEditInput() {
	cout << "수정할 항목을 입력해 주세요: ";
}

void OutputPrintHandler::printEditName() {
	cout << "[1] 이   름: ";
}

void OutputPrintHandler::printEditPhone() {
	cout << "[2] 핸 드 폰: ";
}

void OutputPrintHandler::printEditAddress() {
	cout << "[3] 주    소: ";
}

void OutputPrintHandler::printEditZipCode() {
	cout << "[4] 우편번호: ";
}

void OutputPrintHandler::printEditEmail() {
	cout << "[5] 이 메 일: ";
}

void OutputPrintHandler::printEditAgain() {
	cout << "[완료] 수정되었습니다." << endl;
	cout << "=======================================" << endl;
	cout << "계속 수정하시겠습니까? (Y/N): ";
}

void OutputPrintHandler::printAddConfirm() {
	cout << "=======================================" << endl;
	cout << "추가하시겠습니까? (Y/N): ";
}

void OutputPrintHandler::printEditItem() {
	cout << "---------------------------------------" << endl;
	cout << "수정할 주소록의 번호를 입력해 주세요: ";
}

void OutputPrintHandler::printDeleteItem() {
	cout << "---------------------------------------" << endl;
	cout << "삭제할 주소록의 번호를 입력해 주세요: ";
}

void OutputPrintHandler::printSearchAgain() {
	cout << "---------------------------------------" << endl;
	cout << "다시 검색하시겠습니까? (Y/N): ";
}

void OutputPrintHandler::printSearchEmpty() {
	cout << "검색 결과가 없습니다. ";
}
