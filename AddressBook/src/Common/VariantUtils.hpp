#pragma once
#include "ResultEnums.hpp"
#include "ResultUtils.hpp"
#include "../UI/UICommonData.hpp"
#include <variant>
#include <optional>
#include <type_traits>


//각각의 enum을 Variant로 랩핑
template <typename TargetVariant, typename SourceType>
TargetVariant wrapVariant(const SourceType& src) 
{
    return TargetVariant(src);
}


//입력값으로 들어온 상태가 Variant와 일치하는지 확인
template <typename T, typename VariantType>
bool isVariantEqualTo(const VariantType& variant, T target) 
{
    if (std::holds_alternative<T>(variant)) 
    {
        return std::get<T>(variant) == target;
    }
    return false;
}

template <typename T, typename VariantType>
bool isVariantEqualTo(const std::optional<VariantType>& variant, T target) 
{
    if (variant.has_value()) 
    {
        return isVariantEqualTo<T>(*variant, target);
    }
    else 
    {
        //std::cout << "Optional has empty value" << std::endl;
        return false;
    }
}


//variant에서 원하는 타입 꺼내기
template <typename T, typename VariantType>
T unwrapVariant(const VariantType& variant) 
{
    return std::get<T>(variant);
}


//ResultVariant 디버그용 함수
void printVariant(const ResultVariant& result);
void printVariant(const std::optional<ResultVariant>& result);

