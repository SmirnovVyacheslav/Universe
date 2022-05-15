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
#include "src/resource/mesh.h"
#include "src/scene/scene.h"


namespace engine
{
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
