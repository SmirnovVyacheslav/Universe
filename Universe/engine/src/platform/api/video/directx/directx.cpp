// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "directx.h"

#ifdef WINDOWS
#include <stdexcept>
#include "src/core/config.h"
#include "src/platform/window.h"


namespace engine
{
    directx::~directx() {
        clear_resource(immediate_context);

        release_resource(constant_buffer);
        release_resource(vertex_buffer);
        release_resource(index_buffer);
        release_resource(vertex_layout);
        release_resource(vertex_shader);
        release_resource(pixel_shader);

        release_resource(render_target_view);
        release_resource(swap_chain);
        release_resource(immediate_context);
        release_resource(device);
    }
    bool directx::available() {
        return true;
    }
    void directx::create_device() {
        create_window();
        DXGI_SWAP_CHAIN_DESC swap_chain_data = create_swap_chain_data();
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            NULL,
            driver_type,
            NULL,
            0,
            &requested_feature_level,
            1,
            D3D11_SDK_VERSION,
            &swap_chain_data,
            &swap_chain,
            &device,
            &created_feature_level,
            &immediate_context);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create device");
        }

        create_render_target();
        create_depth_stencil();
        create_depth_stencil_view();
        setup_view_port();

        immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        create_vertex_shader();
        create_pixel_shader();
    }
    void directx::render() {
        immediate_context->ClearRenderTargetView(render_target_view, background_color);
        swap_chain->Present(0, 0);
    }
    void directx::create_window() {
        platform::window::create_window();
    }
    void directx::create_render_target() {
        ID3D11Texture2D* back_buffer = NULL;

        HRESULT result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to get back buffer");
        }

        result = device->CreateRenderTargetView(back_buffer, NULL, &render_target_view);
        back_buffer->Release();
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to get back buffer");
        }

        immediate_context->OMSetRenderTargets(1, &render_target_view, 0);
    }
    DXGI_SWAP_CHAIN_DESC directx::create_swap_chain_data() {
        DXGI_SWAP_CHAIN_DESC swap_chain_data;
        ZeroMemory(&swap_chain_data, sizeof(swap_chain_data));

        swap_chain_data.BufferCount = 1;
        swap_chain_data.BufferDesc.Width = config::video()->window_width;
        swap_chain_data.BufferDesc.Height = config::video()->window_height;
        swap_chain_data.BufferDesc.Format = dxgi_format;
        swap_chain_data.BufferDesc.RefreshRate.Numerator = config::video()->refresh_rate;
        swap_chain_data.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_data.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_data.OutputWindow = reinterpret_cast<HWND>(platform::window::id());
        swap_chain_data.SampleDesc.Count = 1;
        swap_chain_data.SampleDesc.Quality = 0;
        swap_chain_data.Windowed = TRUE;

        return swap_chain_data;
    }
    void directx::create_depth_stencil() {
        D3D11_TEXTURE2D_DESC depth_stencil_data;
        ZeroMemory(&depth_stencil_data, sizeof(depth_stencil_data));

        depth_stencil_data.Width = config::video()->window_width;
        depth_stencil_data.Height = config::video()->window_height;
        depth_stencil_data.MipLevels = 1;
        depth_stencil_data.ArraySize = 1;
        depth_stencil_data.Format = depth_stencil_format;
        depth_stencil_data.SampleDesc.Count = 1;
        depth_stencil_data.SampleDesc.Quality = 0;
        depth_stencil_data.Usage = D3D11_USAGE_DEFAULT;
        depth_stencil_data.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depth_stencil_data.CPUAccessFlags = 0;
        depth_stencil_data.MiscFlags = 0;

        HRESULT result = device->CreateTexture2D(&depth_stencil_data, NULL, &depth_stencil);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create depth stencil source");
        }
    }
    void directx::create_depth_stencil_view() {
        D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_data;
        ZeroMemory(&depth_stencil_view_data, sizeof(depth_stencil_view_data));

        depth_stencil_view_data.Format = depth_stencil_format;
        depth_stencil_view_data.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depth_stencil_view_data.Texture2D.MipSlice = 0;

        HRESULT result = device->CreateDepthStencilView(depth_stencil, &depth_stencil_view_data, &depth_stencil_view);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create depth stencil view");
        }

        immediate_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
    }
    void directx::setup_view_port() {
        D3D11_VIEWPORT view_port;

        view_port.Width = static_cast<float>(config::video()->window_width);
        view_port.Height = static_cast<float>(config::video()->window_height);
        view_port.MinDepth = 0.0f;
        view_port.MaxDepth = 1.0f;
        view_port.TopLeftX = 0;
        view_port.TopLeftY = 0;

        immediate_context->RSSetViewports(1, &view_port);
    }
    void directx::create_vertex_shader() {
        ID3DBlob* vertex_blob = compile_shader_from_file(shader_path, vertex_shader_entry_point, vertex_shader_model);

        HRESULT result = device->CreateVertexShader(vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(), NULL, &vertex_shader);
        if (FAILED(result)) {
            vertex_blob->Release();
            throw std::invalid_argument("Failed to create vertex shader");
        }

        create_vertex_layout(vertex_blob);
        vertex_blob->Release();
    }
    void directx::create_pixel_shader() {
        ID3DBlob* pixel_blob = compile_shader_from_file(shader_path, pixel_shader_entry_point, pixel_shader_model);

        HRESULT result = device->CreatePixelShader(pixel_blob->GetBufferPointer(), pixel_blob->GetBufferSize(), NULL, &pixel_shader);
        pixel_blob->Release();
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create pixel shader");
        }
    }
    void directx::create_vertex_layout(ID3DBlob* vertex_blob) {
        D3D11_INPUT_ELEMENT_DESC layout[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT layout_size = ARRAYSIZE(layout);

        HRESULT result = device->CreateInputLayout(layout,
                                                   layout_size,
                                                   vertex_blob->GetBufferPointer(),
                                                   vertex_blob->GetBufferSize(),
                                                   &vertex_layout);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create input layout");
        }

        immediate_context->IASetInputLayout(vertex_layout);
    }
    ID3DBlob* directx::compile_shader_from_file(string path, string shader_entry_point, string shader_model) {
        ID3DBlob* error_blob = nullptr;
        ID3DBlob* output_blob = nullptr;
        DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;

        HRESULT result = D3DX11CompileFromFile(path.w_str().c_str(),
                                               NULL,
                                               NULL,
                                               shader_entry_point.s_str().c_str(),
                                               shader_model.s_str().c_str(),
                                               shader_flags,
                                               0,
                                               NULL,
                                               &output_blob,
                                               &error_blob,
                                               NULL);
        if (FAILED(result)) {
            if (error_blob) {
                OutputDebugStringA(static_cast<char*>(error_blob->GetBufferPointer()));
                error_blob->Release();
            }
            throw std::invalid_argument("Failed to compiler shader");
        }
        if (error_blob) error_blob->Release();
        return output_blob;
    }
    template<class type_name>
    void directx::clear_resource(type_name* resource_ptr) {
        if (resource_ptr) {
            resource_ptr->ClearState();
        }
    }
    template<class type_name>
    void directx::release_resource(type_name* resource_ptr) {
        if (resource_ptr) {
            resource_ptr->Release();
        }
    }
}
#else
namespace engine {
    bool directx::available() {
        return false;
    }
    void directx::create_device() {
    }
}
#endif
