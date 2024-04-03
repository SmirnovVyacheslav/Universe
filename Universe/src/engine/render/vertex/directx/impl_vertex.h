// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include "../api_vertex.h"

#include "engine/def/platform.h"
#include "engine/var/vertex.h"

#ifdef windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::render::vertex::directx
{

#ifdef windows

    class impl : public obj
    {
    public:
        impl(engine::vertex* data);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        engine::vertex* data;
        ID3D11Buffer* buffer = nullptr;

        UINT offset = 0;
        UINT stride = sizeof(engine::vertex);
    };

#endif

}
