#pragma once

#include "SearchPage2.g.h"

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    struct SearchPage2 : SearchPage2T<SearchPage2>
    {
        SearchPage2() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation
{
    struct SearchPage2 : SearchPage2T<SearchPage2, implementation::SearchPage2>
    {
    };
}
