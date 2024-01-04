// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/impl/render/directx/shader_impl.h"

#include "src/platform/impl/render/directx/term_resource.h"


namespace engine::platform::render::shader::directx
{
    #ifdef platform_windows

    shader_impl::shader_impl(ID3D11Device* device, string file) : device(device), file(file)
    {
        init_vertex_shader(file);
        init_pixel_shader(file);
    }
    
    shader_impl::~shader_impl()
    {
        term_pixel_shader();
        term_vertex_shader();
    }

    void shader_impl::init_vertex_shader(string file)
    {
        ID3DBlob* vertex_blob = compile_shader_file(file, vertex_entry, vertex_model);

        HRESULT result = device->CreateVertexShader
        (
            vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(),
            NULL,
            &vertex_shader
        );

        if (FAILED(result))
        {
            vertex_blob->Release();
            throw std::invalid_argument("Failed to create vertex shader");
        }

        init_vertex_layout(vertex_blob);
        vertex_blob->Release();
    }

    void shader_impl::init_pixel_shader(string file)
    {
        ID3DBlob* pixel_blob = compile_shader_file(file, pixel_entry, pixel_model);

        HRESULT result = device->CreatePixelShader
        (
            pixel_blob->GetBufferPointer(),
            pixel_blob->GetBufferSize(),
            NULL,
            &pixel_shader
        );

        pixel_blob->Release();
        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create pixel shader");
        }
    }

    void shader_impl::init_vertex_layout(ID3DBlob* vertex_blob)
    {
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT layout_size = ARRAYSIZE(layout);

        HRESULT result = device->CreateInputLayout
        (
            layout,
            layout_size,
            vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(),
            &vertex_layout
        );

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create input layout");
        }
    }

    ID3DBlob* shader_impl::compile_shader_file(string path, string entry, string model)
    {
        ID3DBlob* error_blob = nullptr;
        ID3DBlob* output_blob = nullptr;
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;

        HRESULT result = D3DX11CompileFromFile
        (
            path.w_str().c_str(),
            NULL,
            NULL,
            entry.s_str().c_str(),
            model.s_str().c_str(),
            flags,
            0,
            NULL,
            &output_blob,
            &error_blob,
            NULL
        );
        if (FAILED(result))
        {
            if (error_blob)
            {
                OutputDebugStringA(static_cast<char*>(error_blob->GetBufferPointer()));
                error_blob->Release();
            }
            throw std::invalid_argument("Failed to compile shader");
        }
        if (error_blob)
        {
            error_blob->Release();
        }

        return output_blob;
    }

    ID3DBlob* shader_impl::compile_shader_code(string code, string entry, string model)
    {
        ID3DBlob* error_blob = nullptr;
        ID3DBlob* output_blob = nullptr;
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;

        HRESULT result = D3DCompile
        (
            code.s_str().c_str(),
            code.s_str().length(),
            nullptr,
            nullptr,
            nullptr,
            entry.s_str().c_str(),
            model.s_str().c_str(),
            flags,
            0,
            &output_blob,
            &error_blob
        );

        if (FAILED(result))
        {
            if (error_blob)
            {
                OutputDebugStringA(static_cast<char*>(error_blob->GetBufferPointer()));
                error_blob->Release();
            }
            throw std::invalid_argument("Failed to compile shader");
        }

        render::directx::release_resource(error_blob);

        return output_blob;
    }

    void shader_impl::term_vertex_shader()
    {
        render::directx::release_resource(vertex_layout);
        render::directx::release_resource(vertex_shader);
    }

    void shader_impl::term_pixel_shader()
    {
        render::directx::release_resource(pixel_shader);
    }

    #endif
}
