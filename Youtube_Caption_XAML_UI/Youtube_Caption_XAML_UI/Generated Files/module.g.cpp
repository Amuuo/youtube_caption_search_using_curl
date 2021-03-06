﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.180227.3

#include "pch.h"
#ifndef WINRT_SUPPRESS_MODULE_EXPORTS

#include "MainPage.h"
#include "SearchPage2.h"
#include "SearchUrlPage.h"


HRESULT __stdcall WINRT_CanUnloadNow()
{
#ifdef _WRL_MODULE_H_
    if (!::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().Terminate())
    {
        return S_FALSE;
    }
#endif

    if (winrt::get_module_lock())
    {
        return S_FALSE;
    }

    winrt::clear_factory_cache();
    return S_OK;
}

HRESULT __stdcall WINRT_GetActivationFactory(HSTRING classId, void** factory)
{
    try
    {
        *factory = nullptr;
        wchar_t const* const name = WindowsGetStringRawBuffer(classId, nullptr);

        if (0 == wcscmp(name, L"Youtube_Caption_XAML_UI.MainPage"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::Youtube_Caption_XAML_UI::factory_implementation::MainPage>());
            return S_OK;
        }

        if (0 == wcscmp(name, L"Youtube_Caption_XAML_UI.SearchPage2"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::Youtube_Caption_XAML_UI::factory_implementation::SearchPage2>());
            return S_OK;
        }

        if (0 == wcscmp(name, L"Youtube_Caption_XAML_UI.SearchUrlPage"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::Youtube_Caption_XAML_UI::factory_implementation::SearchUrlPage>());
            return S_OK;
        }

#ifdef _WRL_MODULE_H_
        return ::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().GetActivationFactory(classId, reinterpret_cast<::IActivationFactory**>(factory));
#else
        return winrt::hresult_class_not_available().to_abi();
#endif
    }
    catch (...)
    {
        return winrt::to_hresult();
    }
}

#endif
