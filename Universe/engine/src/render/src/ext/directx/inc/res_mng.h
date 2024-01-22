// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine::platform::render::directx
{
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
}
