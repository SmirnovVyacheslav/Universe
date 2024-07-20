// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_device.h"


#ifndef ENGINE_RENDER_DEVICE_DIRECTX_IMPL
#define ENGINE_RENDER_DEVICE_DIRECTX_IMPL

namespace engine::render::device::directx
{

#ifdef windows

    extern ID3D11Device* device;
    extern ID3D11DeviceContext* device_context;
    extern IDXGISwapChain* swap_chain;
    extern ID3D11Texture2D* depth_stencil;
    extern ID3D11DepthStencilView* depth_stencil_view;
    extern ID3D11RenderTargetView* render_target_view;


    class impl : public obj
    {
    public:
        impl();
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void draw(model::obj& model_obj);

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
