﻿#include "pch.h"
#include "SearchUrlPage.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    SearchUrlPage::SearchUrlPage()
    {
        InitializeComponent();
    }

    int32_t SearchUrlPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SearchUrlPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SearchUrlPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
