//
// Declaration of the SearchPage2 class.
//

#pragma once

#include "SearchPage2.g.h"

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    struct SearchPage2 : SearchPage2T<SearchPage2>
    {
        SearchPage2();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation
{
    struct SearchPage2 : SearchPage2T<SearchPage2, implementation::SearchPage2>
    {
    };
}
