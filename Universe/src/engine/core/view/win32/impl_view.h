// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_impl_view.h"


#ifndef ENGINE_CORE_VIEW_WIN32_IMPL
#define ENGINE_CORE_VIEW_WIN32_IMPL

namespace engine::core::view
{
#ifdef windows

    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void* id();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        HWND hwnd;

        LPCTSTR window_name = L"Engine";
        LPCTSTR window_class_name = L"window_class_engine";
    };

#endif
}

#endif
