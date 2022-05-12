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

#include "src/platform/window_ui.h"


namespace engine
{
    struct ConstantBuffer
    {
        XMMATRIX mWorld;
        XMMATRIX mView;
        XMMATRIX mProjection;
    };


    D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_HARDWARE;
    D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;

    ID3D11Device* d3dDevice = nullptr;
    ID3D11DeviceContext* immediateContext = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;

    ID3D11Texture2D* depthStencil = nullptr;
    ID3D11DepthStencilView* depthStencilView = nullptr;

    ID3D11InputLayout* vertexLayout = nullptr;

    ID3D11Buffer* constantBuffer = nullptr;
    ConstantBuffer          localConstantBuffer;

    //============Создание поверхности для Z-буфера============
    ID3D11DepthStencilState* pDSState;
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

    //================D3D11_RASTERIZER_DESC rasterDesc;==========
    D3D11_RASTERIZER_DESC rasterDesc;
    ID3D11RasterizerState* m_rasterState;

    // HWND hWnd;
    int  wndWidth = 800;
    int  wndHeight = 600;

    XMMATRIX                mWorld;
    XMMATRIX                g_World;
    XMMATRIX                g_View;
    XMMATRIX                g_Projection;

    ID3D11VertexShader* g_pVertexShader = NULL;
    ID3D11PixelShader* g_pPixelShader = NULL;


    void createDevice();
    bool createShader();
    bool compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut);
}
#endif
#endif
