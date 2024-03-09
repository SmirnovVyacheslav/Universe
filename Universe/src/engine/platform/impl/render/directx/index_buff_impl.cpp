// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "engine/src/platform/impl/render/directx/index_buff_impl.h"

#include "engine/src/platform/impl/render/directx/term_resource.h"


namespace engine::platform::render::index_buff::directx
{
#ifdef platform_windows

    index_buff_impl::index_buff_impl(ID3D11Device* device, uint16* data) :
        device(device), data(data)
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

        HRESULT result = device->CreateBuffer(&buffer_data, &init_data, &index_buffer);
        
        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create index buffer");
        }
    }

    index_buff_impl::~index_buff_impl()
    {
        render::directx::release_resource(index_buffer);
        delete[] data;
    }

    ID3D11Buffer* index_buff_impl::get_data()
    {
        return index_buffer;
    }

#endif
}
