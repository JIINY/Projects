#pragma once
#include "ResultEnums.hpp"
#include "ResultUtils.hpp"
#include "../UI/UICommonData.hpp"
#include <variant>
#include <optional>
#include <type_traits>


//������ enum�� Variant�� ����
template <typename TargetVariant, typename SourceType>
TargetVariant wrapVariant(const SourceType& src) {
    return TargetVariant(src);
}


//�Է°����� ���� ���°� Variant�� ��ġ�ϴ��� Ȯ��
template <typename T, typename VariantType>
bool isVariantEqualTo(const VariantType& variant, T target) {
    if (holds_alternative<T>(variant)) {
        return get<T>(variant) == target;
    }
    return false;
}

template <typename T, typename VariantType>
bool isVariantEqualTo(const std::optional<VariantType>& variant, T target) {
    if (variant.has_value()) {
        return isVariantEqualTo<T>(*variant, target);
    }
    else {
        //std::cout << "Optional has empty value" << std::endl;
        return false;
    }
}


//variant���� ���ϴ� Ÿ�� ������
template <typename T, typename VariantType>
T unwrapVariant(const VariantType& variant) {
    return std::get<T>(variant);
}


//ResultVariant ����׿� �Լ�
void printVariant(const ResultVariant& result);
void printVariant(const std::optional<ResultVariant>& result);
