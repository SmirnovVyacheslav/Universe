// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/render/src/device/inc/api.h"
#include "src/render/src/settings/inc/api.h"
#include "src/core/type/vector3.h"
#include "src/core/type/matrix4.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::render::device::directx
{

#ifdef platform_windows

    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void draw();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        settings::obj settings_obj;
        vector4 background_color[4] = { { 0.0f, 0.9f, 0.5f, 1.0f } };

        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;
        ID3D11Texture2D* depth_stencil = nullptr;
        ID3D11DepthStencilView* depth_stencil_view = nullptr;
        ID3D11RenderTargetView* render_target_view = nullptr;

        void init_device();
        void init_depth_stencil_view();
        void init_render_target_view();
        void init_view_port();

        void set_primitive_topology();
    };

    template<typename T>
    void clear(T* res)
    {
        if (res)
        {
            res->ClearState();
        }
    }

    template<typename T>
    void release(T* res)
    {
        if (res)
        {
            res->Release();
        }
    }

#else

    class impl : public obj
    {
    public:
        impl() = default;
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void draw() {};

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl() = default;
    };

#endif

}
