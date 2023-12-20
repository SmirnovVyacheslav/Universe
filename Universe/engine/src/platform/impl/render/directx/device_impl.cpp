// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/impl/render/directx/device_impl.h"

#include "src/core/type/std.h"
#include "src/platform/api/view.h"


namespace engine::platform::render::directx
{
    #ifdef platform_windows

    device_impl::device_impl()
    {
        init_device();
        init_reder_target_view();
        init_view_port();
    }

    device_impl::~device_impl()
    {
        clear_resource(device_context);

        release_resource(render_target_view);
        release_resource(swap_chain);
        release_resource(device_context);
        release_resource(device);
    }

    void device_impl::draw()
    {
        device_context->ClearRenderTargetView(render_target_view, *background_color);

        swap_chain->Present(0, 0);
    }

    void device_impl::init_device()
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

    void device_impl::init_reder_target_view() {
        HRESULT result = 0;
        ID3D11Texture2D* back_buffer = NULL;

        result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to init back buffer");
        }

        result = device->CreateRenderTargetView(back_buffer, NULL, &render_target_view);
        back_buffer->Release();

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to init render target view");
        }

        device_context->OMSetRenderTargets(1, &render_target_view, 0);
    }

    void device_impl::init_view_port() {
        D3D11_VIEWPORT view_port;

        view_port.Width = static_cast<real32>(render_cfg.width);
        view_port.Height = static_cast<real32>(render_cfg.height);
        view_port.MinDepth = 0.0f;
        view_port.MaxDepth = 1.0f;
        view_port.TopLeftX = 0;
        view_port.TopLeftY = 0;

        device_context->RSSetViewports(1, &view_port);
    }

    template<typename T>
    void device_impl::clear_resource(T* resource)
    {
        if (resource)
        {
            resource->ClearState();
        }
    }

    template<typename T>
    void device_impl::release_resource(T* resource)
    {
        if (resource)
        {
            resource->Release();
        }
    }

    #endif
}
