// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/core/def/class_format.h"
#include "src/platform/api/render/vertex_buff.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::vertex_buff::directx
{
#ifdef platform_windows

    class vertex_buff_impl : public vertex_buff
    {
        abstract_impl(vertex_buff_impl)
        ____________________public____________________
        vertex_buff_impl(ID3D11Device* device, vertex* data);
        vertex_buff_impl(vertex_buff_impl&& src) = delete;
        vertex_buff_impl(const vertex_buff_impl& src) = delete;

        ID3D11Buffer** get_data();

        vertex_buff_impl& operator=(vertex_buff_impl&& src) = delete;
        vertex_buff_impl& operator=(const vertex_buff_impl& src) = delete;

        ~vertex_buff_impl();
        ____________________private___________________
        vertex* data;

        ID3D11Device* device = nullptr;
        ID3D11Buffer* vertex_buffer = nullptr;
    };

#endif
}
