// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/core/data_type/string.h"
#include "src/core/data_type/matrix_4.h"
#include "src/platform/platform_def.h"
#include "src/platform/api/video.h"

#ifdef WINDOWS
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>


namespace engine {
    class directx : public video_api {
    public:
        directx() = default;
        directx(directx&& src) = default;
        directx(const directx & src) = default;

        bool available();
        void create_device();
        void* create_vertex_shader(string shader_code);
        void* create_pixel_shader(string shader_code);
        void destroy_vertex_shader(void* shader_obj);
        void destroy_pixel_shader(void* shader_obj);
        void render();

        directx& operator=(directx&& src) = default;
        directx& operator=(const directx& src) = default;

        ~directx();
    private:
        struct local_constant_buffer {
            matrix_4 mWorld;
            matrix_4 mView;
            matrix_4 mProjection;
        };
        matrix_4 world;
        matrix_4 view;
        matrix_4 projection;


        DXGI_FORMAT dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
        DXGI_FORMAT depth_stencil_format = DXGI_FORMAT_D24_UNORM_S8_UINT;

        D3D_FEATURE_LEVEL created_feature_level = D3D_FEATURE_LEVEL_11_0;
        D3D_FEATURE_LEVEL requested_feature_level = D3D_FEATURE_LEVEL_11_0;
        D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;

        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* immediate_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;
        ID3D11RenderTargetView* render_target_view = nullptr;
        ID3D11Texture2D* depth_stencil = nullptr;
        ID3D11DepthStencilView* depth_stencil_view = nullptr;

        ID3D11InputLayout* vertex_layout = nullptr;
        ID3D11Buffer* vertex_buffer = nullptr;
        ID3D11Buffer* index_buffer = nullptr;
        ID3D11Buffer* constant_buffer = nullptr;

        string shader_path = u8"engine\\src\\shader\\shader.fx";
        string vertex_shader_entry_point = u8"VS";
        string vertex_shader_model = u8"vs_4_0";
        string pixel_shader_entry_point = u8"PS";
        string pixel_shader_model = u8"ps_4_0";


        float background_color[4] = { 0.0f, 0.9f, 0.5f, 1.0f };

        void create_window();
        void create_render_target();
        DXGI_SWAP_CHAIN_DESC create_swap_chain_data();
        void create_depth_stencil();
        void create_depth_stencil_view();
        void setup_view_port();
        void create_vertex_layout(ID3DBlob* vertex_blob);
        void create_vertex_buffer();
        void create_index_buffer();
        void create_shader_constant_buffer();
        void set_transformation_matrix();
        ID3DBlob* compile_shader_from_file(string path, string shader_entry_point, string shader_model);
        ID3DBlob* compile_shader_from_string(string shader_code, string shader_entry_point, string shader_model);
        template<class type_name>
        void clear_resource(type_name* resource_ptr);
        template<class type_name>
        void release_resource(type_name* resource_ptr);
    };
}
#else
namespace engine {
    class directx : public video_api {
    public:
        directx() = default;
        directx(directx&& src) = default;
        directx(const directx & src) = default;

        bool available();
        void create_device();

        directx& operator=(directx&& src) = default;
        directx& operator=(const directx& src) = default;

        ~directx() = default;
    };
}
#endif
