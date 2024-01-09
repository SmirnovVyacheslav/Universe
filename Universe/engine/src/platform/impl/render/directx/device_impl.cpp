// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/impl/render/directx/device_impl.h"

#include "src/core/type/std.h"
#include "src/core/type/matrix4.h"
#include "src/core/type/vector3.h"
#include "src/core/type/vertex.h"
#include "src/platform/api/view.h"
#include "src/platform/api/render/vertex_buff.h"
#include "src/platform/impl/render/directx/term_resource.h"
#include "src/platform/impl/render/directx/shader_impl.h"
#include "src/platform/impl/render/directx/vertex_buff_impl.h"
#include "src/platform/impl/render/directx/index_buff_impl.h"


namespace engine::platform::render::directx
{
    #ifdef platform_windows

    vector3 eye(0.0f, 1.0f, -5.0f);
    vector3 at(0.0f, 1.0f, 0.0f);
    vector3 up(0.0f, 1.0f, 0.0f);

    matrix4 world = matrix_rotation_y(3.14159f / 4.0f);
    matrix4 view = matrix_look_at(eye, at, up);
    matrix4 projection = matrix_projection(128 / static_cast<float>(256));


    device_impl::device_impl()
    {
        init_device();
        init_depth_stencil_view();
        init_render_target_view();
        init_view_port();

        set_primitive_topology();
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
        device_context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);

        UINT stride = sizeof(vertex);
        UINT offset = 0;
        vertex_buff::directx::vertex_buff_impl* vertex_buffer = dynamic_cast<vertex_buff::directx::vertex_buff_impl*>(vertex_buff::get(0));
        device_context->IASetVertexBuffers(0, 1, vertex_buffer->get_data(), &stride, &offset);

        index_buff::directx::index_buff_impl* index_buffer = dynamic_cast<index_buff::directx::index_buff_impl*>(index_buff::get(0));
        device_context->IASetIndexBuffer(index_buffer->get_data(), DXGI_FORMAT_R16_UINT, 0);

        /*local_constant_buffer cb;
        cb.mWorld = matrix_transpose(world);
        cb.mView = matrix_transpose(view);
        cb.mProjection = matrix_transpose(projection);
        immediate_context->UpdateSubresource(constant_buffer, 0, NULL, &cb, 0, 0);*/

        //immediate_context->VSSetShader(vertex_shader, NULL, 0);
        //immediate_context->VSSetConstantBuffers(0, 1, &constant_buffer);
        //immediate_context->PSSetShader(pixel_shader, NULL, 0);
        //immediate_context->PSSetConstantBuffers(0, 1, &constant_buffer);

        //immediate_context->DrawIndexed(36, 0, 0);

        swap_chain->Present(0, 0);
    }

    shader::shader* device_impl::init_shader(string file)
    {
        return new shader::directx::shader_impl(device, file);
    }

    vertex_buff::vertex_buff* device_impl::init_vertex_buff(vertex* data)
    {
        return new vertex_buff::directx::vertex_buff_impl(device, data);
    }

    index_buff::index_buff* device_impl::init_index_buff(uint16* data)
    {
        return new index_buff::directx::index_buff_impl(device, data);
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

    void device_impl::init_depth_stencil_view()
    {
        D3D11_TEXTURE2D_DESC depth_stencil_desc;
        ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));

        depth_stencil_desc.Width = render_cfg.width;
        depth_stencil_desc.Height = render_cfg.height;
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

    void device_impl::init_render_target_view()
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

    void device_impl::init_view_port()
    {
        D3D11_VIEWPORT view_port;

        view_port.Width = static_cast<real32>(render_cfg.width);
        view_port.Height = static_cast<real32>(render_cfg.height);
        view_port.MinDepth = 0.0f;
        view_port.MaxDepth = 1.0f;
        view_port.TopLeftX = 0;
        view_port.TopLeftY = 0;

        device_context->RSSetViewports(1, &view_port);
    }

    void device_impl::set_primitive_topology()
    {
        device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    #endif
}
