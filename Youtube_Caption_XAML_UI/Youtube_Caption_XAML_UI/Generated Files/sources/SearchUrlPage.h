#pragma once

#include "SearchUrlPage.g.h"

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    struct SearchUrlPage : SearchUrlPageT<SearchUrlPage>
    {
        SearchUrlPage() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation
{
    struct SearchUrlPage : SearchUrlPageT<SearchUrlPage, implementation::SearchUrlPage>
    {
    };
}
