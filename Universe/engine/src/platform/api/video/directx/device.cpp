// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include <stdexcept>

#include "device.h"

#ifdef WINDOWS
#include "src/core/config.h"
#include "src/platform/window.h"

// t = type
// r = reference
// p = pointer
// o = object
// c = const
// m = member
// g = global
// f_c_ = function construct
// f_d_ = function destroy
// t_i_ = implementation

class t_i_device : public t_device {
    ID3D11Device* mp_device = nullptr;
    ID3D11DeviceContext* mp_device_context = nullptr;
    IDXGISwapChain* mp_swap_chain = nullptr;
    ID3D11RenderTargetView* mp_render_target_view = nullptr;
    ID3D11DepthStencilView* mp_depth_stencil_view = nullptr;
};


struct t_depth_stencil_cfg {
    // Depth stencil surface data
    UINT depth_stencil_width = 128;
    UINT depth_stencil_height = 256;
    UINT depth_stencil_map_levels = 1;
    UINT depth_stencil_array_size = 1;
    DXGI_FORMAT depth_stencil_format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    // DXGI_SAMPLE_DESC
    UINT depth_stencil_dxgi_sample_count = 1;
    UINT depth_stencil_dxgi_sample_quality = 0;
    //
    D3D11_USAGE depth_stencil_usage = D3D11_USAGE_DEFAULT;
    UINT depth_stencil_bind_flags = D3D11_BIND_DEPTH_STENCIL;
    UINT depth_stencil_cpu_access_falgs = 0;
    UINT depth_stencil_misc_flags = 0;
    // Depth stencil view data
    DXGI_FORMAT depth_stencil_view_fromat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    D3D11_DSV_DIMENSION depth_stencil_view_dimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    // D3D11_TEX2D_DSV subresource
    UINT depth_stencil_textrue_2d_mip_slice = 0;
};


void initialize_device(HWND window_handler) {
    swap_chain_config swap_chain_config_inst = create_swap_chain_config();
    DXGI_SWAP_CHAIN_DESC swap_chain_descriptor = create_swap_chain_descriptor(window_handler, swap_chain_config_inst);
    device_config device_config_inst = create_device_config();

    create_device_and_swap_chain(swap_chain_descriptor, device_config_inst);
}


ID3D11Texture2D* get_back_buffer() {
    ID3D11Texture2D* back_buffer = NULL;
    HRESULT result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to get back buffer");
    }
    return back_buffer;
}
void release_back_buffer(ID3D11Texture2D* back_buffer) {
    back_buffer->Release();
}
void create_render_target_view(ID3D11Texture2D* back_buffer) {
    HRESULT result = device->CreateRenderTargetView(back_buffer, NULL, &render_target_view);
    back_buffer->Release();
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to get back buffer");
    }
}

ID3D11Texture2D* create_texture_2d(D3D11_TEXTURE2D_DESC description, D3D11_SUBRESOURCE_DATA initial_data) {
    ID3D11Texture2D* texture = nullptr;
    HRESULT result = device->CreateTexture2D(&description, &initial_data, &texture);
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to create depth stencil source");
    }
    return texture;
}


//
D3D11_TEXTURE2D_DESC create_depth_stensil_surface() {
    D3D11_TEXTURE2D_DESC depth_stencil_surface;
    ZeroMemory(&depth_stencil_surface, sizeof(depth_stencil_surface));

    depth_stencil_surface.Width = depth_stencil_width;
    depth_stencil_surface.Height = depth_stencil_height;
    depth_stencil_surface.MipLevels = depth_stencil_map_levels;
    depth_stencil_surface.ArraySize = depth_stencil_array_size;
    depth_stencil_surface.Format = depth_stencil_format;
    depth_stencil_surface.SampleDesc.Count = depth_stencil_dxgi_sample_count;
    depth_stencil_surface.SampleDesc.Quality = depth_stencil_dxgi_sample_quality;
    depth_stencil_surface.Usage = depth_stencil_usage;
    depth_stencil_surface.BindFlags = depth_stencil_bind_flags;
    depth_stencil_surface.CPUAccessFlags = depth_stencil_cpu_access_falgs;
    depth_stencil_surface.MiscFlags = depth_stencil_misc_flags;

    return depth_stencil_surface;
}
D3D11_DEPTH_STENCIL_VIEW_DESC create_depth_stencil_data() {
    D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_data;
    ZeroMemory(&depth_stencil_view_data, sizeof(depth_stencil_view_data));

    depth_stencil_view_data.Format = depth_stencil_view_fromat;
    depth_stencil_view_data.ViewDimension = depth_stencil_view_dimension;
    depth_stencil_view_data.Texture2D.MipSlice = depth_stencil_textrue_2d_mip_slice;

    return depth_stencil_view_data;
}
void create_depth_stencil_view(ID3D11Texture2D* depth_stencil_surface, D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_data) {
    HRESULT result = device->CreateDepthStencilView(depth_stencil_surface, &depth_stencil_view_data, &depth_stencil_view);
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to create depth stencil view");
    }
}

void set_render_target_view() {
    // bind
    immediate_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
}

// viewport data
FLOAT view_port_width = 128;
FLOAT view_port_height = 256;
FLOAT view_port_min_depth = 0.0f;
FLOAT view_port_max_depth = 1.0f;
FLOAT view_port_top_left_x = 0;
FLOAT view_port_top_left_y = 0;
D3D11_VIEWPORT create_viewport() {
    D3D11_VIEWPORT view_port;

    view_port.Width = view_port_width;
    view_port.Height = view_port_height;
    view_port.MinDepth = view_port_min_depth;
    view_port.MaxDepth = view_port_max_depth;
    view_port.TopLeftX = view_port_top_left_x;
    view_port.TopLeftY = view_port_top_left_y;

    return view_port;
}
void set_viewport(D3D11_VIEWPORT view_port) {
    immediate_context->RSSetViewports(1, &view_port);
}

void t_device::mf_c_device() {
    //from up
    // 
    struct t_swap_chain_cfg {
        t_uint buffer_count = 1;
        t_uint buffer_width = 128;
        t_uint buffer_height = 256;
        t_dxgi_format buffer_format = DXGI_FORMAT_R8G8B8A8_UNORM;
        t_uint buffer_refresh_rate_numerator = 60;
        t_uint buffer_refresh_rate_denominator = 1;
        t_dxgi_usage buffer_usage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        t_uint buffer_sample_count = 1;
        t_uint buffer_sample_quality = 0;
        t_bool buffer_windowed = TRUE;
    };

    struct t_device_cfg {
        IDXGIAdapter* adapter = nullptr;
        D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;
        HMODULE software_rasterizer = nullptr;
        UINT runtime_layer_flags = 0;
        D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
        UINT feature_levels_number = 1;
        UINT sdk_version = D3D11_SDK_VERSION;
        D3D_FEATURE_LEVEL* supported_feature_level = nullptr;
    };

    t_swap_chain_desc o_swap_chain_desc;
    ZeroMemory(&o_swap_chain_desc, sizeof(o_swap_chain_desc));

    o_swap_chain_desc.BufferCount = swap_chain_config_inst.buffer_count;
    o_swap_chain_desc.BufferDesc.Width = swap_chain_config_inst.buffer_width;
    o_swap_chain_desc.BufferDesc.Height = swap_chain_config_inst.buffer_haight;
    o_swap_chain_desc.BufferDesc.Format = swap_chain_config_inst.buffer_format;
    o_swap_chain_desc.BufferDesc.RefreshRate.Numerator = swap_chain_config_inst.buffer_numerator;
    o_swap_chain_desc.BufferDesc.RefreshRate.Denominator = swap_chain_config_inst.buffer_denominator;
    o_swap_chain_desc.BufferUsage = swap_chain_config_inst.buffer_usage;
    o_swap_chain_desc.OutputWindow = window_handler;
    o_swap_chain_desc.SampleDesc.Count = swap_chain_config_inst.buffer_sample_count;
    o_swap_chain_desc.SampleDesc.Quality = swap_chain_config_inst.buffer_sample_quality;
    o_swap_chain_desc.Windowed = swap_chain_config_inst.buffer_windowed;

    HRESULT result = D3D11CreateDeviceAndSwapChain(
        device_config_inst.adapter,
        device_config_inst.driver_type,
        device_config_inst.software_rasterizer,
        device_config_inst.runtime_layer_flags,
        &device_config_inst.feature_levels,
        device_config_inst.feature_levels_number,
        device_config_inst.sdk_version,
        &swap_chain_descriptor,
        &swap_chain,
        &device,
        device_config_inst.supported_feature_level,
        &immediate_context);

    // Def failed func
    if (result < 0) {
        throw std::invalid_argument("Failed to initialize device");
    }
}


#else

#endif
