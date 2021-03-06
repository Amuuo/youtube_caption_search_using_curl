﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "SearchUrlPage.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    using Application = ::winrt::Windows::UI::Xaml::Application;
    using ComponentResourceLocation = ::winrt::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation;
    using DataTemplate = ::winrt::Windows::UI::Xaml::DataTemplate;
    using DependencyObject = ::winrt::Windows::UI::Xaml::DependencyObject;
    using DependencyProperty = ::winrt::Windows::UI::Xaml::DependencyProperty;
    using IComponentConnector = ::winrt::Windows::UI::Xaml::Markup::IComponentConnector;
    using Uri = ::winrt::Windows::Foundation::Uri;
    using XamlBindingHelper = ::winrt::Windows::UI::Xaml::Markup::XamlBindingHelper;

    template <typename D, typename ... I>
    void SearchUrlPageT<D, I...>::InitializeComponent()
    {
        if (!_contentLoaded)
        {
            _contentLoaded = true;
            Uri resourceLocator{ L"ms-appx:///SearchUrlPage.xaml" };
            Application::LoadComponent(*this, resourceLocator, ComponentResourceLocation::Application);
        }
    }

    template <typename D, typename ... I>
    void SearchUrlPageT<D, I...>::Connect(int32_t connectionId, IInspectable const& target)
    {
        switch (connectionId)
        {
        case 2:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::StackPanel>();
                this->titleSearch(targetElement);
            }
            break;
        case 3:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Image>();
                this->title(targetElement);
            }
            break;
        case 4:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::StackPanel>();
                this->searchBar(targetElement);
            }
            break;
        case 5:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Image>();
                this->thumbnail(targetElement);
            }
            break;
        case 6:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::StackPanel>();
                this->buttonStack(targetElement);
            }
            break;
        case 7:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::TextBlock>();
                this->mostFrequentBox(targetElement);
            }
            break;
        case 8:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::TextBlock>();
                this->ResultsBlock(targetElement);
            }
            break;
        case 9:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Button>();
                this->searchWordsButton(targetElement);
                targetElement.Click({ static_cast<D*>(this), &D::searchWordsClick});
            }
            break;
        case 10:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Button>();
                this->mostFrequentButton(targetElement);
                targetElement.Click({ static_cast<D*>(this), &D::mostFrequentClick});
            }
            break;
        case 11:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Button>();
                this->testButton(targetElement);
                targetElement.Click({ static_cast<D*>(this), &D::testGridClick});
            }
            break;
        case 12:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::TextBox>();
                this->UrlBox(targetElement);
            }
            break;
        case 13:
            {
                auto targetElement = target.as<::winrt::Windows::UI::Xaml::Controls::Button>();
                this->Button(targetElement);
                targetElement.Click({ static_cast<D*>(this), &D::ClickHandler});
            }
            break;
        }
        _contentLoaded = true;
    }

    template <typename D, typename ... I>
    void SearchUrlPageT<D, I...>::DisconnectUnloadedObject(int32_t)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects to disconnect." };
    }

    template <typename D, typename ... I>
    void SearchUrlPageT<D, I...>::UnloadObject(DependencyObject const&)
    {
        throw ::winrt::hresult_invalid_argument { L"No unloadable objects." };
    }


    template <typename D, typename... I>
    IComponentConnector SearchUrlPageT<D, I...>::GetBindingConnector(int32_t, IInspectable const&)
    {
        return nullptr;
    }

    template SearchUrlPageT<SearchUrlPage>;
}


#pragma warning(pop)


