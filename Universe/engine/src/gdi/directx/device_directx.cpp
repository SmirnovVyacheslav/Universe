// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include <stdexcept>

#include "src/gdi/device.h"
#include "src/platform/definition.h"

#ifdef PLATFORM_WINDOWS
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>


namespace engine
{
    class device_directx_t : public t_device
    {
    public:
        device_directx_t(const t_gdi_cfg* gdi_cfg);
        device_directx_t(device_directx_t&& src) = delete;
        device_directx_t(const device_directx_t& src) = delete;

        device_directx_t& operator=(device_directx_t&& src) = delete;
        device_directx_t& operator=(const device_directx_t& src) = delete;

        ~device_directx_t() = default;

    private:
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;

        void create_device(const t_gdi_cfg* gdi_cfg);
    };


    t_device* t_device::smf_c_directx(const t_gdi_cfg& cr_dgi_cfg)
    {
        return new device_directx_t(&cr_dgi_cfg);
    }

    device_directx_t::device_directx_t(const t_gdi_cfg* gdi_cfg)
    {
        create_device(gdi_cfg);
    }

    void device_directx_t::create_device(const t_gdi_cfg* gdi_cfg)
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.BufferDesc.Width = gdi_cfg->mo_width;
        swap_chain_desc.BufferDesc.Height = gdi_cfg->mo_height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = gdi_cfg->mo_refresh;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = reinterpret_cast<HWND>(gdi_cfg->mp_window_handler);
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
    class device_directx_t : public t_device
    {
    public:
        device_directx_t(const t_gdi_cfg* gdi_cfg);
        device_directx_t(device_directx_t&& src) = delete;
        device_directx_t(const device_directx_t& src) = delete;

        device_directx_t& operator=(device_directx_t&& src) = delete;
        device_directx_t& operator=(const device_directx_t& src) = delete;

        ~device_directx_t() = default;

    private:
        void create_device(const t_gdi_cfg* gdi_cfg);
    };


    t_device* t_device::smf_c_directx(const t_gdi_cfg& cr_dgi_cfg)
    {
        return new device_directx_t(&cr_dgi_cfg);
    }

    device_directx_t::device_directx_t(const t_gdi_cfg* gdi_cfg)
    {
        create_device(gdi_cfg);
    }

    void device_directx_t::create_device(const t_gdi_cfg* gdi_cfg)
    {
        throw std::invalid_argument("Failed to create device");
    }
}
#endif
