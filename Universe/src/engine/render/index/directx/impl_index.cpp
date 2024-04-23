// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_index.h"

#include "engine/def/platform.h"
#include "engine/render/device/directx/impl_device.h"
#include "engine/var/error.h"


namespace engine::render::index::directx
{

#ifdef windows

    impl::impl(array<uint16> data) : data(data)
    {
        D3D11_BUFFER_DESC buffer_data;
        ZeroMemory(&buffer_data, sizeof(buffer_data));

        buffer_data.Usage = D3D11_USAGE_DEFAULT;
        buffer_data.ByteWidth = sizeof(WORD) * data.size();
        buffer_data.BindFlags = D3D11_BIND_INDEX_BUFFER;
        buffer_data.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA init_data;
        ZeroMemory(&init_data, sizeof(init_data));

        init_data.pSysMem = *data;

        HRESULT result = device::directx::device->CreateBuffer(&buffer_data, &init_data, &buffer);

        if (FAILED(result))
        {
            throw error("Failed to create index buffer");
        }
    }

    void impl::set()
    {
        device::directx::device_context->IASetIndexBuffer(buffer, DXGI_FORMAT_R16_UINT, 0);
    }

    impl::~impl()
    {
        device::directx::release(buffer);
    }

#endif

}
