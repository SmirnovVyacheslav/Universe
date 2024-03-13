// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "engine/def/platform.h"

#ifdef windows
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>
#endif


namespace engine::platform::render::directx
{
    #ifdef windows 

    template<typename T>
    void clear_resource(T* resource)
    {
        if (resource)
        {
            resource->ClearState();
        }
    }

    template<typename T>
    void release_resource(T* resource)
    {
        if (resource)
        {
            resource->Release();
        }
    }

    #endif
}
