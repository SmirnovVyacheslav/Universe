// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/src/render/index/directx/impl.h"
#include "engine/src/render/device/directx/impl_device.h"


namespace engine::render::index::directx
{

#ifdef platform_windows

    impl::impl(uint16* data) : data(data)
    {
        D3D11_BUFFER_DESC buffer_data;
        ZeroMemory(&buffer_data, sizeof(buffer_data));

        buffer_data.Usage = D3D11_USAGE_DEFAULT;
        buffer_data.ByteWidth = sizeof(WORD) * 36;
        buffer_data.BindFlags = D3D11_BIND_INDEX_BUFFER;
        buffer_data.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA init_data;
        ZeroMemory(&init_data, sizeof(init_data));

        init_data.pSysMem = data;

        HRESULT result = device->CreateBuffer(&buffer_data, &init_data, &buffer);

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create index buffer");
        }
    }

    impl::~impl()
    {
        device::directx::release(buffer);
        delete[] data;
    }

    ID3D11Buffer* impl::get_data()
    {
        return buffer;
    }

#endif

}
