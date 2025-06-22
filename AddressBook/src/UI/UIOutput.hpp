#pragma once
#include <functional>
#include <optional>
#include "../Common/ResultEnums.hpp"

class ErrorPrintHandler;

enum class EnterType {
    None,
    RenderOnly,
    ErrorOnly,
    Both
};

enum class RenderOrder {
    RenderToError,
    ErrorToRender
};

struct UIFrame;
struct UITemplate;

struct UIFrame {
    std::function<void()> renderFunc;
    EnterType enter = EnterType::None;
    std::optional<ResultVariant> errorPrint = std::nullopt;
    RenderOrder order = RenderOrder::RenderToError;

    void operator()(ErrorPrintHandler& errorMsgH) const;
};

struct UITemplate {
    std::function<void()> renderFunc;
    EnterType enter = EnterType::None;
    RenderOrder order = RenderOrder::RenderToError;

    UIFrame instantiate(std::optional<ResultVariant> err) const;
};
