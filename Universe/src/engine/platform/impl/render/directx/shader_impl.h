// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/src/core/def/abstract_class.h"
#include "engine/src/core/def/class_format.h"
#include "engine/src/var/matrix4.h"
#include "engine/src/platform/api/render/shader.h"

#ifdef platform_windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::shader::directx
{
    #ifdef platform_windows

    struct constant_buff_cpu
    {
        matrix4 world;
        matrix4 view;
        matrix4 projection;
    };

    class shader_impl : public shader
    {
        abstract_impl(shader_impl)
        ____________________public____________________
        shader_impl(ID3D11Device* device, ID3D11DeviceContext* device_context, string file);
        shader_impl(shader_impl&& src) = delete;
        shader_impl(const shader_impl& src) = delete;

        void update(matrix4 world, matrix4 view, matrix4 projection);
        void set();

        shader_impl& operator=(shader_impl&& src) = delete;
        shader_impl& operator=(const shader_impl& src) = delete;

        ~shader_impl();
        ____________________private___________________
        string file;

        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        ID3D11VertexShader* vertex_shader = nullptr;
        ID3D11PixelShader* pixel_shader = nullptr;
        ID3D11InputLayout* vertex_layout = nullptr;
        ID3D11Buffer* constant_buff = nullptr;

        constant_buff_cpu cb;

        string vertex_entry = u8"VS";
        string vertex_model = u8"vs_4_0";
        string pixel_entry = u8"PS";
        string pixel_model = u8"ps_4_0";

        void init_vertex_shader(string file);
        void init_pixel_shader(string file);
        void init_vertex_layout(ID3DBlob* vertex_blob);
        void init_constant_buff();

        void term_vertex_shader();
        void term_pixel_shader();

        ID3DBlob* compile_shader_file(string path, string entry, string model);
        ID3DBlob* compile_shader_code(string code, string entry, string model);
    };

    #endif
}
