// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include <stdexcept>

#include "src/render/device/device.h"
#include "src/platform/definition.h"

#ifdef PLATFORM_WINDOWS
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>


namespace engine::render::device
{
    class device_directx_t : public device_t
    {
        abstract_impl(device_directx_t)

    public:
        device_directx_t(const cfg_t* cfg);
        device_directx_t(device_directx_t&& src) = delete;
        device_directx_t(const device_directx_t& src) = delete;

        device_directx_t& operator=(device_directx_t&& src) = delete;
        device_directx_t& operator=(const device_directx_t& src) = delete;

        ~device_directx_t() = default;

    private:
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;

        void create_device(const cfg_t* cfg);
    };


    device_t* device_t::initialize(const cfg_t& cfg)
    {
        return new device_directx_t(&cfg);
    }

    device_directx_t::device_directx_t(const cfg_t* cfg)
    {
        create_device(cfg);
    }

    void device_directx_t::create_device(const cfg_t* cfg)
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.BufferDesc.Width = cfg->width;
        swap_chain_desc.BufferDesc.Height = cfg->height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = cfg->refresh;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = reinterpret_cast<HWND>(cfg->window_handler);
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = TRUE;

        HRESULT result = D3D11CreateDeviceAndSwapChain
        (
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            0,
            NULL,
            0,
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &swap_chain,
            &device,
            NULL,
            &device_context
        );

        if (FAILED(result))
        {
            throw std::invalid_argument("Failed to create device");
        }
    }
}
#else
namespace engine
{
    class device_directx_t : public device_t
    {
    public:
        device_directx_t(const cfg_t* cfg);
        device_directx_t(device_directx_t&& src) = delete;
        device_directx_t(const device_directx_t& src) = delete;

        device_directx_t& operator=(device_directx_t&& src) = delete;
        device_directx_t& operator=(const device_directx_t& src) = delete;

        ~device_directx_t() = default;

    private:
        void create_device(const cfg_t* cfg);
    };


    device_t* device_t::initialize(const cfg_t& cfg)
    {
        return new device_directx_t(&cfg);
    }

    device_directx_t::device_directx_t(const cfg_t* cfg)
    {
        create_device(cfg);
    }

    void device_directx_t::create_device(const cfg_t* cfg)
    {
        throw std::invalid_argument("Failed to create device");
    }
}
#endif
