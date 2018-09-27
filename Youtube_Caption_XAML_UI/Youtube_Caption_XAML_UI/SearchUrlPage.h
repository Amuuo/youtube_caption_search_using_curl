//
// Declaration of the SearchUrlPage class.
//

#pragma once

#include "SearchUrlPage.g.h"


namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    struct SearchUrlPage : SearchUrlPageT<SearchUrlPage>
    {
        SearchUrlPage();

        shared_ptr<VideoCaptions> captions;
        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, 
                          Windows::UI::Xaml::RoutedEventArgs const& args);
       
        void testGridClick(Windows::Foundation::IInspectable const& sender,
                           Windows::UI::Xaml::RoutedEventArgs const& args);
        
        void mostFrequentClick(Windows::Foundation::IInspectable const& sender, 
                         Windows::UI::Xaml::RoutedEventArgs const& args);
       
        void searchWordsClick(Windows::Foundation::IInspectable const& sender, 
                              Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation
{
    struct SearchUrlPage : SearchUrlPageT<SearchUrlPage, implementation::SearchUrlPage>
    {
    };
}
