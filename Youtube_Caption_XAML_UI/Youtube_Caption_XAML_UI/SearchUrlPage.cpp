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

    void SearchUrlPage::ClickHandler(IInspectable const&, 
                                     RoutedEventArgs const&)
    {
      wstring tmpUrl{UrlBox().Text()};

      if(captions) captions.~shared_ptr();

      captions = make_shared<VideoCaptions>(tmpUrl);
      captions->captionText.clear();
      for (auto linePtr : captions->captionLines) 
      {
        captions->captionText += linePtr->line + L'\n';          
      }
      ResultsBlock().Text(captions->captionText);
    }
    
    void SearchUrlPage::testGridClick(IInspectable const & sender, 
                                      RoutedEventArgs const & args) {
      this->Frame().Navigate(xaml_typename<Youtube_Caption_XAML_UI::SearchPage2>(), nullptr);
    }
    
    void SearchUrlPage::mostFrequentClick(IInspectable const & sender, 
                                    RoutedEventArgs const & args) {
    
      mostFrequentBox().Text(captions->printMaxMentions());
    }
    
    void SearchUrlPage::searchWordsClick(IInspectable const & sender,
                                         RoutedEventArgs const & args) {
    
    }
}
