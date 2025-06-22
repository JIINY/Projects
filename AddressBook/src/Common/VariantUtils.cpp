#pragma once
#include "VariantUtils.hpp"
#include <iostream>
#include <optional>
#include "ResultEnums.hpp"
#include "ResultUtils.hpp"
using namespace std;



//ResultVariant 디버그용 함수: variant 내용을 출력하는 본체
void printVariant(const ResultVariant& result) {
    visit([](auto&& arg) {
        cout << toString(arg) << endl; //ResultUtils에서 추가
        }, result);
}

//optional<ResultVariant>가 들어올 때의 처리를 위한 wrapper (함수 오버로딩)
void printVariant(const optional<ResultVariant>& result) {
    if (result.has_value()) {
        printVariant(*result);
    }
    else {
        cout << "No Error" << endl;
    }
}
