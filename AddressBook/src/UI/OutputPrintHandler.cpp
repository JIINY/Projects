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
    cout << left << setw(20) << "�ּҷ�: �߰� ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}
void OutputPrintHandler::printAddEditTitle() {
    cout << "=======================================" << endl;
    cout << left << setw(20) << "�ּҷ�: �߰� ���� ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}
void OutputPrintHandler::printEditTitle() {
    cout << "=======================================" << endl;
    cout << left << setw(20) << "�ּҷ�: ���� ";
    cout << right << setw(18) << version << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchTitle() {
	cout << "=======================================" << endl;
	cout << left << setw(20) << "�ּҷ�: ã�� ";
	cout << right << setw(18) << version << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchLongTitle() {
	cout << "============================================================================================================" << endl;
	cout << left << setw(20) << "�ּҷ�: ã�� ";
	cout << right << setw(87) << version << endl;
	cout << "============================================================================================================" << endl;
}

void OutputPrintHandler::printViewTitle() {
	cout << "============================================================================================================" << endl;
	cout << left << setw(20) << "�ּҷ�: ���� ";
	cout << right << setw(87) << version << endl;
	cout << "============================================================================================================" << endl;
}

void OutputPrintHandler::printMenuSelect() {
    cout << "�޴��� ������ �ּ���: ";
}

void OutputPrintHandler::printCancle(CancleType action) {
	switch (action) {
	case CancleType::Input:
		cout << "�Է���";
		break;
	case CancleType::Edit:
		cout << "������";
		break;
	case CancleType::Delete:
		cout << "������";
		break;
	case CancleType::AddConfirm:
		cout << "�߰���";
		break;
	}
    cout << " ����Ͻðڽ��ϱ�? (Y/N): ";
}



void OutputPrintHandler::printMainMenu() {
    cout << "=======================================" << endl;
    cout << " �ּҷ� " << setw(30) << version << endl;
    cout << "=======================================" << endl;
    cout << "[1] �ּҷ� �߰�" << endl;
    cout << "[2] �ּҷ� ����" << endl;
    cout << "[3] �ּҷ� ã�� + ����/����" << endl;
    cout << "[0] ����" << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchMenu() {
	cout << "[1] �̸����� ã��" << endl;
	cout << "[2] �޴��� ��ȣ�� ã��" << endl;
	cout << "[3] �ּҷ� ã��" << endl;
	cout << "[4] �����ȣ�� ã��" << endl;
	cout << "[5] �̸��Ϸ� ã��" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[0] ����ϰ� ���ư���" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printInputName() {
	cout << "��    ��: ";
}
void OutputPrintHandler::printInputPhone() {
	cout << "�� �� ��: ";
}
void OutputPrintHandler::printInputAddress() {
	cout << "��    ��: ";
}
void OutputPrintHandler::printInputZipCode() {
	cout << "�����ȣ: ";
}
void OutputPrintHandler::printInputEmail() {
	cout << "�� �� ��: ";
}

void OutputPrintHandler::printPersonalData(const PersonalData& p) {
    cout << "��    ��: " << p.name << endl;
    cout << "�� �� ��: " << p.phone << endl;
    cout << "��    ��: " << p.address << endl;
    cout << "�����ȣ: " << p.zipCode << endl;
    cout << "�� �� ��: " << p.email << endl;
    cout << "=======================================" << endl;
}

void OutputPrintHandler::printAddMenu() {
	cout << "[1] �߰��ϱ�" << endl;
	cout << "[2] �Է� �����ϱ�" << endl;
	cout << "[0] ����ϰ� ���ư���" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchSubMenu() {
	cout << "[1] �׸� �����ϱ�" << endl;
	cout << "[2] �׸� �����ϱ�" << endl;
	cout << "[9] �ٽ� �˻��ϱ�" << endl;
	cout << "[0] ���� �޴��� ���ư���" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printSearchEmptySubMenu() {
	cout << "[9] �ٽ� �˻��ϱ�" << endl;
	cout << "[0] ���� �޴��� ���ư���" << endl;
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
	cout << "���� Ű�� ������ ���� �������� �Ѿ�ϴ�. �ߴ��� Q�� ��������. ";
}

void OutputPrintHandler::printTableComplete() {
	cout << "�ּҷ��� ���Դϴ�. ���� Ű�� ������ ���� �޴��� ���ư��ϴ�. ";
}

void OutputPrintHandler::printTableSearchEnd() {
	cout << "�˻��� �������ϴ�. ����/�����Ͻ÷��� �޴��� ������ �ּ���. ";
}

void OutputPrintHandler::printTableStop() {
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << "�ּҷ� ���⸦ �����Ͻðڽ��ϱ�? (Y/N) ";
}

void OutputPrintHandler::printAddSuccess(const int i, const PersonalData& p) {
	cout << "============================================================================================================" << endl;
	cout << " No.   Name        PhoneNumber      Address                                ZipCode    E-Mail   " << endl;
	cout << "------------------------------------------------------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(f.no) << i << setw(f.name) << p.name << setw(f.phone) << p.phone << setw(f.address) << p.address
		<< setw(f.zipCode) << p.zipCode << setw(f.email) << p.email << endl;
	cout << "============================================================================================================" << endl;
	cout << "[�Ϸ�] �ּҷϿ� " << p.name << "��/�� �߰��Ǿ����ϴ�." << endl;
	cout << "---------------------------------------" << endl;
}

void OutputPrintHandler::printAddAgain() {
	cout << "�̾ �߰��Ͻðڽ��ϱ�? (Y/N): ";
}

void OutputPrintHandler::printPersonalEdit(const PersonalData& p) {
	cout << "[1] ��    ��: " << p.name << endl;
	cout << "[2] �� �� ��: " << p.phone << endl;
	cout << "[3] ��    ��: " << p.address << endl;
	cout << "[4] �����ȣ: " << p.zipCode << endl;
	cout << "[5] �� �� ��: " << p.email << endl;
	cout << "[6] ���� ����" << endl;
	cout << "---------------------------------------" << endl;
}

void OutputPrintHandler::printAddEditConfirm() {
	cout << "[9] ���� �Ϸ��ϰ� �߰��ϱ�" << endl;
	cout << "[0] ����ϰ� ���ư���" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printEditConfirm() {
	cout << "[9] ���� �Ϸ�" << endl;
	cout << "[0] ����ϰ� ���ư���" << endl;
	cout << "=======================================" << endl;
}

void OutputPrintHandler::printEditInput() {
	cout << "������ �׸��� �Է��� �ּ���: ";
}

void OutputPrintHandler::printEditName() {
	cout << "[1] ��   ��: ";
}

void OutputPrintHandler::printEditPhone() {
	cout << "[2] �� �� ��: ";
}

void OutputPrintHandler::printEditAddress() {
	cout << "[3] ��    ��: ";
}

void OutputPrintHandler::printEditZipCode() {
	cout << "[4] �����ȣ: ";
}

void OutputPrintHandler::printEditEmail() {
	cout << "[5] �� �� ��: ";
}

void OutputPrintHandler::printEditAgain() {
	cout << "[�Ϸ�] �����Ǿ����ϴ�." << endl;
	cout << "=======================================" << endl;
	cout << "��� �����Ͻðڽ��ϱ�? (Y/N): ";
}

void OutputPrintHandler::printAddConfirm() {
	cout << "=======================================" << endl;
	cout << "�߰��Ͻðڽ��ϱ�? (Y/N): ";
}

void OutputPrintHandler::printEditItem() {
	cout << "---------------------------------------" << endl;
	cout << "������ �ּҷ��� ��ȣ�� �Է��� �ּ���: ";
}

void OutputPrintHandler::printDeleteItem() {
	cout << "---------------------------------------" << endl;
	cout << "������ �ּҷ��� ��ȣ�� �Է��� �ּ���: ";
}

void OutputPrintHandler::printSearchAgain() {
	cout << "---------------------------------------" << endl;
	cout << "�ٽ� �˻��Ͻðڽ��ϱ�? (Y/N): ";
}

void OutputPrintHandler::printSearchEmpty() {
	cout << "�˻� ����� �����ϴ�. ";
}
