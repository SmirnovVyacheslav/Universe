// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/gdi/device.h"
#include "src/gdi/gdi_cfg.h"

#include <stdexcept>


#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <windows.h>

namespace engine
{
    class t_device_directx : public t_device
    {
        public:    t_device_directx(const t_gdi_cfg* cr_gdi_cfg);
        public:    t_device_directx(t_device_directx&& r_src) = delete;
        public:    t_device_directx(const t_device_directx& cr_src) = delete;
        public:    ~t_device_directx() = default;

        public:    t_device_directx& operator=(t_device_directx&& r_src) = delete;
        public:    t_device_directx& operator=(const t_device_directx& cr_src) = delete;

        private:   ID3D11Device* mp_device = nullptr;
        private:   ID3D11DeviceContext* mp_device_context = nullptr;
        private:   IDXGISwapChain* mp_swap_chain = nullptr;
        private:   ID3D11RenderTargetView* mp_render_target_view = nullptr;
        private:   ID3D11DepthStencilView* mp_depth_stencil_view = nullptr;
    };


    t_device* t_device::smf_c_directx(const t_gdi_cfg& cr_dgi_cfg)
    {
        return new t_device_directx(&cr_dgi_cfg);
    }


    t_device_directx::t_device_directx(const t_gdi_cfg* cr_gdi_cfg)
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

        swap_chain_desc.BufferCount = 1;
        swap_chain_desc.BufferDesc.Width = cr_gdi_cfg->mo_width;
        swap_chain_desc.BufferDesc.Height = cr_gdi_cfg->mo_height;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = cr_gdi_cfg->mo_refresh;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = reinterpret_cast<HWND>(cr_gdi_cfg->mp_window_handler);
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = TRUE;


        D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;
        D3D_FEATURE_LEVEL created_feature_level = D3D_FEATURE_LEVEL_11_0;
        D3D_FEATURE_LEVEL requested_feature_level = D3D_FEATURE_LEVEL_11_0;
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            NULL,
            driver_type,
            NULL,
            0,
            &requested_feature_level,
            1,
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &mp_swap_chain,
            &mp_device,
            &created_feature_level,
            &mp_device_context);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create device");
        }
    }
}
