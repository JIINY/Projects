#include "UIOutput.hpp"
#include <iostream>
#include "../Common/ResultEnums.hpp"
#include "../IO/ErrorPrintHandler.hpp"
using namespace std;


UIFrame UITemplate::instantiate(std::optional<ResultVariant> err) const 
{
    return UIFrame { renderFunc, enter, err, order };
}


void UIFrame::operator()(ErrorPrintHandler& errorMsgH) const 
{
    switch (order) 
    {
    case RenderOrder::RenderToError:
        if (enter == EnterType::RenderOnly || enter == EnterType::Both) 
        {
            cout << endl; 
        }
        renderFunc();
        if (errorPrint.has_value()) 
        {
            errorMsgH.printErrorMsg(errorPrint.value());
        }
        break;

    case RenderOrder::ErrorToRender:
        if ((enter == EnterType::ErrorOnly && errorPrint.has_value()) || enter == EnterType::Both) 
        {
            cout << endl;
        }
        if (errorPrint.has_value()) 
        {
            errorMsgH.printErrorMsg(errorPrint.value());
        }
        renderFunc();
        break;
    }
}
