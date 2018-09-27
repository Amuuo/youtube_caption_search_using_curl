#include "pch.h"
#include "SearchPage2.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    SearchPage2::SearchPage2()
    {
        InitializeComponent();
    }

    int32_t SearchPage2::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SearchPage2::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SearchPage2::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        
    }
}
