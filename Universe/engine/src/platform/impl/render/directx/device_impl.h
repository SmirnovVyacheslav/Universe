// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/core/def/class_format.h"
#include "src/core/type/std.h"
#include "src/core/type/vector4.h"
#include "src/platform/api/render.h"
#include "src/platform/impl/render/device.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::directx
{
    #ifdef platform_windows

    class device_impl : public device
    {
        abstract_impl(device_impl)
        ____________________public____________________
        device_impl();
        device_impl(device_impl&& src) = delete;
        device_impl(const device_impl& src) = delete;

        void draw();

        device_impl& operator=(device_impl&& src) = delete;
        device_impl& operator=(const device_impl& src) = delete;

        ~device_impl();
        ____________________private___________________
        render_config render_cfg;
        vector4 background_color[4] = { { 0.0f, 0.9f, 0.5f, 1.0f } };
        // real32 background_color[4] = {0.0f, 0.9f, 0.5f, 1.0f};

        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;
        ID3D11RenderTargetView* render_target_view = nullptr;

        void init_device();
        void init_reder_target_view();
        void init_view_port();

        template<typename T>
        void clear_resource(T* resource);
        template<typename T>
        void release_resource(T* resource);
    };

    #else

    class device_impl : public device
    {
        abstract_impl(device_impl)
        ____________________public____________________
        device_impl() = default;
        device_impl(device_impl&& src) = delete;
        device_impl(const device_impl& src) = delete;

        device_impl& operator=(device_impl&& src) = delete;
        device_impl& operator=(const device_impl& src) = delete;

        ~device_impl() = default;
    };

    #endif
}
