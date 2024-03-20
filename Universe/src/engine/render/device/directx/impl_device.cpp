// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "impl_device.h"

#include "engine/def/platform.h"
#include "engine/platform/api/view.h"


namespace engine::render::device::directx
{

#ifdef windows

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* device_context = nullptr;
    IDXGISwapChain* swap_chain = nullptr;
    ID3D11Texture2D* depth_stencil = nullptr;
    ID3D11DepthStencilView* depth_stencil_view = nullptr;
    ID3D11RenderTargetView* render_target_view = nullptr;


    impl::impl() : settings_obj(settings::get())
    {
        init_device();
        init_depth_stencil_view();
        init_render_target_view();
        init_view_port();

        set_primitive_topology();
    }

    void impl::draw()
    {
        device_context->ClearRenderTargetView(render_target_view, *background_color);
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

        /*UINT stride = sizeof(vertex);
        UINT offset = 0;
        vertex_buff::directx::vertex_buff_impl* vertex_buffer = dynamic_cast<vertex_buff::directx::vertex_buff_impl*>(vertex_buff::get(0));
        device_context->IASetVertexBuffers(0, 1, vertex_buffer->get_data(), &stride, &offset);

        index_buff::directx::index_buff_impl* index_buffer = dynamic_cast<index_buff::directx::index_buff_impl*>(index_buff::get(0));
        device_context->IASetIndexBuffer(index_buffer->get_data(), DXGI_FORMAT_R16_UINT, 0);

        shader::directx::shader_impl* shader_inst = dynamic_cast<shader::directx::shader_impl*>(shader::get(0));
        shader_inst->update(world, view, projection);
        shader_inst->set();

        device_context->DrawIndexed(36, 0, 0);*/

        swap_chain->Present(0, 0);
    }

    impl::~impl()
    {
        clear(device_context);

        release(render_target_view);
        release(swap_chain);
        release(device_context);
        release(device);
        
        device = nullptr;
        device_context = nullptr;
        swap_chain = nullptr;
        depth_stencil = nullptr;
        depth_stencil_view = nullptr;
        render_target_view = nullptr;
    }

    void impl::init_device()
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.BufferDesc.Width = settings_obj.width;
        swap_chain_desc.BufferDesc.Height = settings_obj.height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = settings_obj.refresh;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = reinterpret_cast<HWND>(platform::view::id());
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = settings_obj.windowed;

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

    void impl::init_depth_stencil_view()
    {
        D3D11_TEXTURE2D_DESC depth_stencil_desc;
        ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));

        depth_stencil_desc.Width = settings_obj.width;
        depth_stencil_desc.Height = settings_obj.height;
        depth_stencil_desc.MipLevels = 1;
        depth_stencil_desc.ArraySize = 1;
        depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_stencil_desc.SampleDesc.Count = 1;
        depth_stencil_desc.SampleDesc.Quality = 0;
        depth_stencil_desc.Usage = D3D11_USAGE_DEFAULT;
        depth_stencil_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depth_stencil_desc.CPUAccessFlags = 0;
        depth_stencil_desc.MiscFlags = 0;

        HRESULT result = device->CreateTexture2D(&depth_stencil_desc, NULL, &depth_stencil);
        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create depth stencil");
        }

        D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
        ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));

        depth_stencil_view_desc.Format = depth_stencil_desc.Format;
        depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depth_stencil_view_desc.Texture2D.MipSlice = 0;

        result = device->CreateDepthStencilView(depth_stencil, &depth_stencil_view_desc, &depth_stencil_view);
        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create depth stencil view");
        }
    }

    void impl::init_render_target_view()
    {
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

        device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
    }

    void impl::init_view_port()
    {
        D3D11_VIEWPORT view_port;

        view_port.Width = static_cast<fp32>(settings_obj.width);
        view_port.Height = static_cast<fp32>(settings_obj.height);
        view_port.MinDepth = 0.0f;
        view_port.MaxDepth = 1.0f;
        view_port.TopLeftX = 0;
        view_port.TopLeftY = 0;

        device_context->RSSetViewports(1, &view_port);
    }

    void impl::set_primitive_topology()
    {
        device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

#endif

}
