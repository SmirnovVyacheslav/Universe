﻿// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
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
            ~directx();

            bool available();
            void create_device();
            void render();
        private:
            DXGI_FORMAT dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;

            D3D_FEATURE_LEVEL created_feature_level;
            D3D_FEATURE_LEVEL requested_feature_level = D3D_FEATURE_LEVEL_11_0;
            D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;

            ID3D11Device* device = nullptr;
            ID3D11DeviceContext* immediate_context = nullptr;
            IDXGISwapChain* swap_chain = nullptr;
            ID3D11RenderTargetView* render_target_view = nullptr;

            float background_color[4] = { 0.0f, 0.9f, 0.5f, 1.0f };

            void create_window();
            void create_render_target();
            DXGI_SWAP_CHAIN_DESC create_swap_chain_data();
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
        ~directx() = default;

        bool available();
        void create_device();
    };
}
#endif
