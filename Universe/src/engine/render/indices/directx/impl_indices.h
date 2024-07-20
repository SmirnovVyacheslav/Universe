// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_impl_indices.h"


#ifndef ENGINE_RENDER_INDICES_DIRECTX_IMPL
#define ENGINE_RENDER_INDICES_DIRECTX_IMPL

namespace engine::render::indices::directx
{

#ifdef windows

    class impl : public obj
    {
    public:
        impl(array<uint16> data);
        impl(impl&& src) = delete;
        impl(const impl& src) = delete;

        void set();
        int32 size();

        impl& operator=(impl&& src) = delete;
        impl& operator=(const impl& src) = delete;

        ~impl();
    private:
        array<uint16> data;
        ID3D11Buffer* buffer = nullptr;
    };

#endif

}

#endif
