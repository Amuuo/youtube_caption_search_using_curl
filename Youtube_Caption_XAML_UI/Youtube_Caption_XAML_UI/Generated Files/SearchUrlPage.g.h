﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.180227.3

#pragma once
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/Youtube_Caption_XAML_UI.h"

namespace winrt::Youtube_Caption_XAML_UI::implementation {

template <typename D, typename... I>
struct WINRT_EBO SearchUrlPage_base : implements<D, Youtube_Caption_XAML_UI::ISearchUrlPage, Windows::UI::Xaml::Controls::IControlOverrides, Windows::UI::Xaml::Controls::IControlOverrides6, Windows::UI::Xaml::Controls::IPageOverrides, Windows::UI::Xaml::IFrameworkElementOverrides, Windows::UI::Xaml::IFrameworkElementOverrides2, Windows::UI::Xaml::IUIElementOverrides, Windows::UI::Xaml::IUIElementOverrides7, Windows::UI::Xaml::IUIElementOverrides8, composing, I...>,
    impl::require<D, Windows::UI::Xaml::Controls::IControl, Windows::UI::Xaml::Controls::IControl2, Windows::UI::Xaml::Controls::IControl3, Windows::UI::Xaml::Controls::IControl4, Windows::UI::Xaml::Controls::IControl5, Windows::UI::Xaml::Controls::IControlProtected, Windows::UI::Xaml::Controls::IPage, Windows::UI::Xaml::Controls::IUserControl, Windows::UI::Xaml::IDependencyObject, Windows::UI::Xaml::IDependencyObject2, Windows::UI::Xaml::IFrameworkElement, Windows::UI::Xaml::IFrameworkElement2, Windows::UI::Xaml::IFrameworkElement3, Windows::UI::Xaml::IFrameworkElement4, Windows::UI::Xaml::IFrameworkElement6, Windows::UI::Xaml::IUIElement, Windows::UI::Xaml::IUIElement2, Windows::UI::Xaml::IUIElement3, Windows::UI::Xaml::IUIElement4, Windows::UI::Xaml::IUIElement5, Windows::UI::Xaml::IUIElement7, Windows::UI::Xaml::IUIElement8>,
    impl::base<D, Windows::UI::Xaml::Controls::Page, Windows::UI::Xaml::Controls::UserControl, Windows::UI::Xaml::Controls::Control, Windows::UI::Xaml::FrameworkElement, Windows::UI::Xaml::UIElement, Windows::UI::Xaml::DependencyObject>,
    Windows::UI::Xaml::Controls::IControlOverridesT<D>, Windows::UI::Xaml::Controls::IControlOverrides6T<D>, Windows::UI::Xaml::Controls::IPageOverridesT<D>, Windows::UI::Xaml::IFrameworkElementOverridesT<D>, Windows::UI::Xaml::IFrameworkElementOverrides2T<D>, Windows::UI::Xaml::IUIElementOverridesT<D>, Windows::UI::Xaml::IUIElementOverrides7T<D>, Windows::UI::Xaml::IUIElementOverrides8T<D>
{
    using base_type = SearchUrlPage_base;
    using class_type = Youtube_Caption_XAML_UI::SearchUrlPage;
    using implements_type = typename SearchUrlPage_base::implements_type;
    using implements_type::implements_type;
    using composable_base = Windows::UI::Xaml::Controls::Page;
    operator class_type() const noexcept
    {
        static_assert(std::is_same_v<typename impl::implements_default_interface<D>::type, impl::default_interface_t<class_type>>);
        class_type result{ nullptr };
        attach_abi(result, detach_abi(static_cast<impl::default_interface_t<class_type>>(*this)));
        return result;
    }

    hstring GetRuntimeClassName() const
    {
        return L"Youtube_Caption_XAML_UI.SearchUrlPage";
    }
    SearchUrlPage_base()
    {
        get_activation_factory<Windows::UI::Xaml::Controls::Page, Windows::UI::Xaml::Controls::IPageFactory>().CreateInstance(*this, this->m_inner);
    }
};

}

namespace winrt::Youtube_Caption_XAML_UI::factory_implementation {

template <typename D, typename T, typename... I>
struct WINRT_EBO SearchUrlPageT : implements<D, Windows::Foundation::IActivationFactory, I...>
{
    hstring GetRuntimeClassName() const
    {
        return L"Youtube_Caption_XAML_UI.SearchUrlPage";
    }

    Windows::Foundation::IInspectable ActivateInstance() const
    {
        return make<T>();
    }
};

}

#if defined(WINRT_FORCE_INCLUDE_SEARCHURLPAGE_XAML_G_H) || __has_include("SearchUrlPage.xaml.g.h")

#include "SearchUrlPage.xaml.g.h"

#else

namespace winrt::Youtube_Caption_XAML_UI::implementation
{
    template <typename D, typename... I>
    using SearchUrlPageT = SearchUrlPage_base<D, I...>;
}

#endif
