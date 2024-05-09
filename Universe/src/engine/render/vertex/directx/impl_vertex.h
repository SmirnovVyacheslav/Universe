// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_impl_vertex.h"


#ifndef ENGINE_RENDER_VERTEX_DIRECTX_IMPL
#define ENGINE_RENDER_VERTEX_DIRECTX_IMPL

namespace engine::render::vertex::directx
{

#ifdef windows

    class impl : public obj
    {
    public:
        impl(array<engine::vertex> data);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        array<engine::vertex> data;
        ID3D11Buffer* buffer = nullptr;

        UINT offset = 0;
        UINT stride = sizeof(engine::vertex);
    };

#endif

}

#endif
