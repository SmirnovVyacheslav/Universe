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
    class dx_device : public t_device
    {
        public:    dx_device(const t_gdi_cfg* cr_gdi_cfg);
        public:    dx_device(dx_device&& r_src) = delete;
        public:    dx_device(const dx_device& cr_src) = delete;
        public:    ~dx_device() = default;

        public:    dx_device& operator=(dx_device&& r_src) = delete;
        public:    dx_device& operator=(const dx_device& cr_src) = delete;

              ID3D11Device* mp_device = nullptr;
              ID3D11DeviceContext* mp_device_context = nullptr;
              IDXGISwapChain* mp_swap_chain = nullptr;
              ID3D11RenderTargetView* mp_render_target_view = nullptr;
              ID3D11DepthStencilView* mp_depth_stencil_view = nullptr;
    };


    t_device* t_device::smf_c_direct_x(const t_gdi_cfg& cr_dgi_cfg)
    {
        return new dx_device(&cr_dgi_cfg);
    }


    dx_device::dx_device(const t_gdi_cfg* cr_gdi_cfg)
    {
        DXGI_SWAP_CHAIN_DESC swap_chain_data;
        ZeroMemory(&swap_chain_data, sizeof(swap_chain_data));

        swap_chain_data.BufferCount = 1;
        swap_chain_data.BufferDesc.Width = 128;
        swap_chain_data.BufferDesc.Height = 256;
        swap_chain_data.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_data.BufferDesc.RefreshRate.Numerator = 60;
        swap_chain_data.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_data.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_data.OutputWindow = reinterpret_cast<HWND>(cr_gdi_cfg->mp_window_handler);
        swap_chain_data.SampleDesc.Count = 1;
        swap_chain_data.SampleDesc.Quality = 0;
        swap_chain_data.Windowed = TRUE;


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
            &swap_chain_data,
            &mp_swap_chain,
            &mp_device,
            &created_feature_level,
            &mp_device_context);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create device");
        }
    }
}
