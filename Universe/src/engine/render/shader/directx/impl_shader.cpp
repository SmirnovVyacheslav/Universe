// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/ips_impl_shader.h"


namespace engine::render::shader::directx
{

#ifdef windows

    impl::impl(string file) : file(file)
    {
        init_vertex_shader(file);
        init_pixel_shader(file);
        init_constant_buff();
    }

    void impl::set()
    {
        camera::obj& camera_obj = camera::get();

        cb.world = matrix_transpose(camera_obj.world());
        cb.view = matrix_transpose(camera_obj.view());
        cb.projection = matrix_transpose(camera_obj.projection());
        device::directx::device_context->UpdateSubresource(constant_buff, 0, NULL, &cb, 0, 0);

        device::directx::device_context->VSSetShader(vertex_shader, NULL, 0);
        device::directx::device_context->VSSetConstantBuffers(0, 1, &constant_buff);
        device::directx::device_context->PSSetShader(pixel_shader, NULL, 0);
        device::directx::device_context->PSSetConstantBuffers(0, 1, &constant_buff);
    }

    impl::~impl()
    {
        term_pixel_shader();
        term_vertex_shader();
    }

    void impl::init_vertex_shader(string file)
    {
        ID3DBlob* vertex_blob = compile_shader_file(file, vertex_entry, vertex_model);

        HRESULT result = device::directx::device->CreateVertexShader
        (
            vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(),
            NULL,
            &vertex_shader
        );

        if (FAILED(result))
        {
            vertex_blob->Release();
            throw error("Failed to create vertex shader");
        }

        init_vertex_layout(vertex_blob);
        vertex_blob->Release();
    }

    void impl::init_pixel_shader(string file)
    {
        ID3DBlob* pixel_blob = compile_shader_file(file, pixel_entry, pixel_model);

        HRESULT result = device::directx::device->CreatePixelShader
        (
            pixel_blob->GetBufferPointer(),
            pixel_blob->GetBufferSize(),
            NULL,
            &pixel_shader
        );

        pixel_blob->Release();
        if (FAILED(result))
        {
            throw error("Failed to create pixel shader");
        }
    }

    void impl::init_vertex_layout(ID3DBlob* vertex_blob)
    {
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT layout_size = ARRAYSIZE(layout);

        HRESULT result = device::directx::device->CreateInputLayout
        (
            layout,
            layout_size,
            vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(),
            &vertex_layout
        );

        if (FAILED(result))
        {
            throw error("Failed to create input layout");
        }

        device::directx::device_context->IASetInputLayout(vertex_layout);
    }

    void impl::init_constant_buff() {
        D3D11_BUFFER_DESC buffer_data;
        ZeroMemory(&buffer_data, sizeof(buffer_data));

        buffer_data.Usage = D3D11_USAGE_DEFAULT;
        buffer_data.ByteWidth = sizeof(constant_buff_cpu);
        buffer_data.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        buffer_data.CPUAccessFlags = 0;

        HRESULT result = device::directx::device->CreateBuffer(&buffer_data, NULL, &constant_buff);
        if (FAILED(result))
        {
            throw error("Failed to create shader constant buffer");
        }
    }

    ID3DBlob* impl::compile_shader_file(string file, string entry, string model)
    {
        ID3DBlob* error_blob = nullptr;
        ID3DBlob* output_blob = nullptr;
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;

        HRESULT result = D3DX11CompileFromFile
        (
            file.w_str().c_str(),
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
            throw error("Failed to compile shader");
        }
        if (error_blob)
        {
            error_blob->Release();
        }

        return output_blob;
    }

    ID3DBlob* impl::compile_shader_code(string code, string entry, string model)
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
            throw error("Failed to compile shader");
        }

        device::directx::release(error_blob);

        return output_blob;
    }

    void impl::term_vertex_shader()
    {
        device::directx::release(vertex_layout);
        device::directx::release(vertex_shader);
    }

    void impl::term_pixel_shader()
    {
        device::directx::release(pixel_shader);
    }

#endif

}
