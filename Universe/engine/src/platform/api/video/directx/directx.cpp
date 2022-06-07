// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "directx.h"

#ifdef WINDOWS
#include <stdexcept>
#include "src/core/config.h"
#include "src/platform/window.h"


namespace engine
{
    directx::~directx() {
        clear_resource(immediate_context);

        release_resource(swap_chain);
        release_resource(immediate_context);
        release_resource(device);
    }
	bool directx::available() {
		return true;
	}
    void directx::create_device() {
        create_window();
        DXGI_SWAP_CHAIN_DESC swap_chain_data = create_swap_chain_data();
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            NULL,
            driver_type,
            NULL,
            0,
            &requested_feature_level,
            1,
            D3D11_SDK_VERSION,
            &swap_chain_data,
            &swap_chain,
            &device,
            &created_feature_level,
            &immediate_context);
        if (FAILED(result)) {
            throw std::invalid_argument("Failed to create device");
        }
    }
    void directx::create_window() {
        platform::window::create_window();
    }
    DXGI_SWAP_CHAIN_DESC directx::create_swap_chain_data() {
        DXGI_SWAP_CHAIN_DESC swap_chain_data;
        ZeroMemory(&swap_chain_data, sizeof(swap_chain_data));

        swap_chain_data.BufferCount = 1;
        swap_chain_data.BufferDesc.Width = config::video()->window_width;
        swap_chain_data.BufferDesc.Height = config::video()->window_height;
        swap_chain_data.BufferDesc.Format = dxgi_format;
        swap_chain_data.BufferDesc.RefreshRate.Numerator = config::video()->refresh_rate;
        swap_chain_data.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_data.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_data.OutputWindow = reinterpret_cast<HWND>(platform::window::id());
        swap_chain_data.SampleDesc.Count = 1;
        swap_chain_data.SampleDesc.Quality = 0;
        swap_chain_data.Windowed = TRUE;

        return swap_chain_data;
    }
    template<class type_name>
    void directx::clear_resource(type_name* resource_ptr) {
        if (resource_ptr) {
            resource_ptr->ClearState();
        }
    }
    template<class type_name>
    void directx::release_resource(type_name* resource_ptr) {
        if (resource_ptr) {
            resource_ptr->Release();
        }
    }
}
#else
namespace engine {
	bool directx::available() {
		return false;
	}
	void directx::create_device() {
	}
}
#endif
