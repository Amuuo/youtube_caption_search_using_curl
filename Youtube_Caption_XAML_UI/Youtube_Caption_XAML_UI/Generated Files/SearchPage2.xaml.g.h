﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#pragma once


namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    using IInspectable = ::winrt::Windows::Foundation::IInspectable;

    template <typename D, typename ... I>
    class SearchPage2T : public ::winrt::Youtube_Caption_XAML_UI::implementation::SearchPage2_base<D,
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector,
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector2,
        I...>
    {
    public:
        void InitializeComponent();
        void Connect(int32_t connectionId, IInspectable const& target);
        ::winrt::Windows::UI::Xaml::Markup::IComponentConnector GetBindingConnector(int32_t connectionId, IInspectable const& target);
        void UnloadObject(::winrt::Windows::UI::Xaml::DependencyObject const& dependencyObject);
        void DisconnectUnloadedObject(int32_t connectionId);

        ::winrt::Windows::UI::Xaml::Controls::Grid mainGrid()
        {
            return _mainGrid;
        }
        void mainGrid(::winrt::Windows::UI::Xaml::Controls::Grid value)
        {
            _mainGrid = value;
        }
        
    private:
        bool _contentLoaded{false};

        ::winrt::Windows::UI::Xaml::Controls::Grid _mainGrid{nullptr};
    };
}

