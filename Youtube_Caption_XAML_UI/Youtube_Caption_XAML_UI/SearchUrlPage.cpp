#include "pch.h"
#include "SearchUrlPage.h"
#include "VideoCaptions.h"

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
      wstring tmpUrl{UrlBox().Text()};
      /*HttpClient tmpClient;
      auto testURI = Windows::Foundation::Uri{L"https://www.google.com"};
      HttpRequestMessage urlRequest(HttpMethod::Get(), testURI);
      
      
      auto response = tmpClient.GetStringAsync(testURI);
      OutputDebugString(response.get().c_str());
      */
      VideoCaptions* tmpCaptions = new VideoCaptions{tmpUrl};
    }
}
