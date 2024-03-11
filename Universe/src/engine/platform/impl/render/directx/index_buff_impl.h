// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/core/def/abstract_class.h"
#include "engine/core/def/class_format.h"
#include "engine/platform/api/render/index_buff.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::index_buff::directx
{
    #ifdef platform_windows

    class index_buff_impl : public index_buff
    {
        abstract_impl(index_buff_impl)
        ____________________public____________________
        index_buff_impl(ID3D11Device* device, uint16* data);
        index_buff_impl(index_buff_impl&& src) = delete;
        index_buff_impl(const index_buff_impl& src) = delete;

        ID3D11Buffer* get_data();

        index_buff_impl& operator=(index_buff_impl&& src) = delete;
        index_buff_impl& operator=(const index_buff_impl& src) = delete;

        ~index_buff_impl();
        ____________________private___________________
        uint16* data;

        ID3D11Device* device = nullptr;
        ID3D11Buffer* index_buffer = nullptr;
    };

    #endif
}
