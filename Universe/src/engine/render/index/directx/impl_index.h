// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "../api_index.h"

#include "engine/def/platform.h"

#ifdef windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::render::index::directx
{

#ifdef windows

    class impl : public obj
    {
    public:
        impl(array<uint16> data);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        array<uint16> data;
        ID3D11Buffer* buffer = nullptr;
    };

#endif

}
