#pragma once
#include "VariantUtils.hpp"
#include <iostream>
#include <optional>
#include "ResultEnums.hpp"
#include "ResultUtils.hpp"
using namespace std;



//ResultVariant ����׿� �Լ�: variant ������ ����ϴ� ��ü
void printVariant(const ResultVariant& result) {
    visit([](auto&& arg) {
        cout << toString(arg) << endl; //ResultUtils���� �߰�
        }, result);
}

//optional<ResultVariant>�� ���� ���� ó���� ���� wrapper (�Լ� �����ε�)
void printVariant(const optional<ResultVariant>& result) {
    if (result.has_value()) {
        printVariant(*result);
    }
    else {
        cout << "No Error" << endl;
    }
}
