// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "src/platform/platform_def.h"

#pragma once
#ifdef WINDOWS
#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include <windows.h>

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <xnamath.h>

#include "src/platform/window.h"
#include "src/resource/mesh.h"
#include "src/scene/scene.h"


namespace engine
{
    class directx
    {
    public:
        directx() = default;
        ~directx() = default;

        void create_device();
        void create_window();

    private:
        HWND window_handler;

        std::int32_t window_width = 800;
        std::int32_t window_height = 600;

        std::int32_t refresh_rate = 60;

        DXGI_FORMAT dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ID3D11Device* d3dDevice = nullptr;
        ID3D11DeviceContext* immediateContext = nullptr;
        IDXGISwapChain* swapChain = nullptr;
    };
    
    struct ConstantBuffer
    {
        XMMATRIX mWorld;
        XMMATRIX mView;
        XMMATRIX mProjection;
    };


    void createDevice();
    bool createShader();
    void setGeometry();
    bool compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut);
    void do_render();
}
#endif
#endif
