// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/def/platform.h"
#include "engine/core/def/abstract_class.h"
#include "engine/core/def/class_format.h"
#include "engine/var/std.h"
#include "engine/var/string.h"
#include "engine/var/vector4.h"
#include "engine/var/vertex.h"
#include "engine/platform/api/render.h"
#include "engine/platform/api/render/shader.h"
#include "engine/platform/api/render/vertex_buff.h"
#include "engine/platform/api/render/index_buff.h"
#include "engine/platform/impl/render/device.h"

#ifdef windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::directx
{
    #ifdef windows 

    class device_impl : public device
    {
        abstract_impl(device_impl)
    public:
        device_impl();
        device_impl(device_impl&& src) = delete;
        device_impl(const device_impl& src) = delete;

        void draw();
        shader::shader* init_shader(string file);
        vertex_buff::vertex_buff* init_vertex_buff(vertex* data);
        index_buff::index_buff* init_index_buff(uint16* data);

        device_impl& operator=(device_impl&& src) = delete;
        device_impl& operator=(const device_impl& src) = delete;

        ~device_impl();
    private:
        render_config render_cfg;
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