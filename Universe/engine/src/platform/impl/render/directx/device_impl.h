// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
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

    public:
        device_impl();
        device_impl(device_impl&& src) = delete;
        device_impl(const device_impl& src) = delete;

        device_impl& operator=(device_impl&& src) = delete;
        device_impl& operator=(const device_impl& src) = delete;

        ~device_impl();

    private:
        render_config render_cfg;

        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;

        void create_device();
    };

    #else

    class device_impl : public device
    {
        abstract_impl(device_impl)

    public:
        device_impl() = default;
        device_impl(device_impl&& src) = delete;
        device_impl(const device_impl& src) = delete;

        device_impl& operator=(device_impl&& src) = delete;
        device_impl& operator=(const device_impl& src) = delete;

        ~device_impl() = default;
    };

    #endif
}
