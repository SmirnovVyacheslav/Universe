// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "device_obj.h"

#include "engine/def/platform.h"
#include "engine/render/model/obj_model.h"
#include "engine/render/settings.h"
#include "engine/var/matrix4.h"
#include "engine/var/vector3.h"
#include "engine/var/vector4.h"

#ifdef windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif

#ifndef ENGINE_RENDER_DEVICE_IMPL_DIRECTX
#define ENGINE_RENDER_DEVICE_IMPL_DIRECTX

namespace engine::render::device::directx
{

#ifdef windows

    extern ID3D11Device* device;
    extern ID3D11DeviceContext* device_context;
    extern IDXGISwapChain* swap_chain;
    extern ID3D11Texture2D* depth_stencil;
    extern ID3D11DepthStencilView* depth_stencil_view;
    extern ID3D11RenderTargetView* render_target_view;

    extern ID3D11BlendState* blend_state_on;
    extern ID3D11BlendState* blend_state_off;


    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void draw(model::obj& model_obj);
        void enable_alpha_blend();
        void disable_alpha_blend();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        settings::obj settings_obj;
        vector4 background_color[4] = { { 0.0f, 0.9f, 0.5f, 1.0f } };

        void init_device();
        void init_depth_stencil_view();
        void init_render_target_view();
        void init_view_port();
        void init_blend_state();

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

#endif
