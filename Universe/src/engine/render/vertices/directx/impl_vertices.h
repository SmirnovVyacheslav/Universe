// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_vertices.h"


#ifndef ENGINE_RENDER_VERTICES_DIRECTX_IMPL
#define ENGINE_RENDER_VERTICES_DIRECTX_IMPL

namespace engine::render::vertices::directx
{

#ifdef windows

    class impl : public obj
    {
    public:
        impl(array<vertex> data);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        array<vertex> data;
        ID3D11Buffer* buffer = nullptr;

        UINT offset = 0;
        UINT stride = sizeof(vertex);
    };

#endif

}

#endif
