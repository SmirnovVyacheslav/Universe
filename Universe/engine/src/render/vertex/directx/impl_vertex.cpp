// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/render/vertex/directx/impl_vertex.h"
#include "src/render/device/directx/impl.h"


namespace engine::render::vertex::directx
{

#ifdef platform_windows

    impl::impl(engine::vertex* data) : data(data)
    {
        D3D11_BUFFER_DESC buffer_data;
        ZeroMemory(&buffer_data, sizeof(buffer_data));

        buffer_data.Usage = D3D11_USAGE_DEFAULT;
        buffer_data.ByteWidth = sizeof(engine::vertex) * 8;
        buffer_data.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffer_data.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA init_data;
        ZeroMemory(&init_data, sizeof(init_data));

        init_data.pSysMem = data;

        HRESULT result = device->CreateBuffer(&buffer_data, &init_data, &buffer);

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create vertex buffer");
        }
    }

    impl::~impl()
    {
        device::directx::release(buffer);
        delete[] data;
    }

    ID3D11Buffer** impl::get_data()
    {
        return &buffer;
    }

#endif

}
