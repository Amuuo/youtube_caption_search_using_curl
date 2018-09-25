#pragma once

#include "MainPage.g.h"

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
