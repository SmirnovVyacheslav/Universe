// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/def/abstract_class.h"
#include "src/core/def/class_format.h"
#include "src/platform/api/render/shader.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::shader::directx
{
#ifdef platform_windows

    class shader_impl : public shader
    {
        abstract_impl(shader_impl)
        ____________________public____________________
        shader_impl(ID3D11Device* device);
        shader_impl(shader_impl&& src) = delete;
        shader_impl(const shader_impl& src) = delete;

        shader_impl& operator=(shader_impl&& src) = delete;
        shader_impl& operator=(const shader_impl& src) = delete;

        ~shader_impl();
        ____________________private___________________
        void* init_vertex_shader(string file);
        void* init_pixel_shader(string file);
        void term_vertex_shader(void* vertex_shader);
        void term_pixel_shader(void* pixel_shader);
            
        ID3D11Device* device = nullptr;
        //ID3D11InputLayout* vertex_layout = nullptr;
        ID3D11VertexShader* vertex_shader = nullptr;
        ID3D11PixelShader* pixel_shader = nullptr;

        string vertex_entry = u8"VS";
        string vertex_model = u8"vs_4_0";
        string pixel_entry = u8"PS";
        string pixel_model = u8"ps_4_0";

        ID3DBlob* compile_shader_file(string path, string entry, string model);
        ID3DBlob* compile_shader_code(string code, string entry, string model);

        template<typename T>
        void clear_resource(T* resource);
        template<typename T>
        void release_resource(T* resource);
    };

    #endif
}
