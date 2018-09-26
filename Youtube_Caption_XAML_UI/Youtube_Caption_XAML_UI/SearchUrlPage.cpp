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

      auto tmpCaptions = make_shared<VideoCaptions>(tmpUrl);
      tmpCaptions->captionText.clear();
      for (auto linePtr : tmpCaptions->captionLines) 
      {
        tmpCaptions->captionText += linePtr->line + L'\n';          
      }
      ResultsBlock().Text(tmpCaptions->captionText);
    }
}
