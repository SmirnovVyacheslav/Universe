// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_s_impl_vertex.h"


namespace engine::render::vertex::directx
{

#ifdef windows

    impl::impl(array<engine::vertex> data) : data(data)
    {
        D3D11_BUFFER_DESC buffer_data;
        ZeroMemory(&buffer_data, sizeof(buffer_data));

        buffer_data.Usage = D3D11_USAGE_DEFAULT;
        buffer_data.ByteWidth = sizeof(engine::vertex) * data.size();
        buffer_data.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffer_data.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA init_data;
        ZeroMemory(&init_data, sizeof(init_data));

        init_data.pSysMem = *data;

        HRESULT result = device::directx::device->CreateBuffer(&buffer_data, &init_data, &buffer);

        if (FAILED(result))
        {
            throw error("Failed to create vertex buffer");
        }
    }

    void impl::set()
    {
        device::directx::device_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    }

    impl::~impl()
    {
        device::directx::release(buffer);
    }

#endif

}
