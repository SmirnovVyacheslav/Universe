// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/platform/impl/render/directx/shader_impl.h"


namespace engine::platform::render::shader::directx
{
    shader_impl::shader_impl(ID3D11Device* device) : device(device)
    {}
    
    shader_impl::~shader_impl()
    {
        //
    }

    void* shader_impl::init_vertex_shader(string file)
    {
        ID3D11VertexShader* vertex_shader = nullptr;
        ID3DBlob* vertex_blob = compile_shader_file(file, shader_vertex_entry, shader_vertex_model);

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

        return vertex_shader;
    }

    void* shader_impl::init_pixel_shader(string file)
    {
        ID3D11PixelShader* pixel_shader = nullptr;
        ID3DBlob* pixel_blob = compile_shader_file(file, shader_pixel_entry, shader_pixel_model);

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

        return pixel_shader;
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
        release_resource(error_blob);

        return output_blob;
    }

    void shader_impl::term_vertex_shader(void* vertex_shader)
    {
        ID3D11VertexShader* vertex_shader = reinterpret_cast<ID3D11VertexShader*>(vertex_shader);
        release_resource(vertex_shader);
    }

    void shader_impl::term_pixel_shader(void* pixel_shader)
    {
        ID3D11PixelShader* pixel_shader = reinterpret_cast<ID3D11PixelShader*>(pixel_shader);
        release_resource(pixel_shader);
    }

}