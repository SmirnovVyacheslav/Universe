// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/impl/render/directx/device_impl.h"

#include "src/platform/api/view.h"


namespace engine::platform::render::directx
{
    #ifdef platform_windows

    device_impl::device_impl()
    {
        create_device();
    }

    device_impl::~device_impl()
    {
        //
    }

    void device_impl::create_device()
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.BufferDesc.Width = render_cfg.width;
        swap_chain_desc.BufferDesc.Height = render_cfg.height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = render_cfg.refresh;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = reinterpret_cast<HWND>(view::id());
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = render_cfg.windowed;

        HRESULT result = D3D11CreateDeviceAndSwapChain
        (
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            0,
            NULL,
            0,
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &swap_chain,
            &device,
            NULL,
            &device_context
        );

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create device");
        }
    }

    #endif
}
