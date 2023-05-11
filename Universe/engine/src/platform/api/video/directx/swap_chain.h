//#pragma once
//// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
//#pragma once
//#include "src/core/data_type/string.h"
//#include "src/core/data_type/matrix_4.h"
//#include "src/platform/platform_def.h"
//#include "src/platform/api/video.h"
//
//#ifdef WINDOWS
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dcompiler.h>
//#include <windows.h>
//
//// t = type
//// r = reference
//// p = pointer
//// o = object
//// c = const
//// m = member
//// g = global
//// _c_ = construct
//// _d_ = destroy
//
////DIRECTX TYPES
////windows types
//using t_uint = UINT;
//using t_bool = BOOL;
//using t_dxgi_format = DXGI_FORMAT;
//using t_dxgi_usage = DXGI_USAGE;
//using t_swap_chain_desc = DXGI_SWAP_CHAIN_DESC;
//
//
//struct t_swap_chain_cfg {
//    t_uint buffer_count = 1;
//    t_uint buffer_width = 128;
//    t_uint buffer_height = 256;
//    t_dxgi_format buffer_format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    t_uint buffer_refresh_rate_numerator = 60;
//    t_uint buffer_refresh_rate_denominator = 1;
//    t_dxgi_usage buffer_usage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    t_uint buffer_sample_count = 1;
//    t_uint buffer_sample_quality = 0;
//    t_bool buffer_windowed = TRUE;
//};
//
//t_swap_chain_desc f_c_swap_chain_desc(HWND window_handler, swap_chain_config swap_chain_config_inst) {
//    t_swap_chain_desc o_swap_chain_desc;
//    ZeroMemory(&o_swap_chain_desc, sizeof(o_swap_chain_desc));
//
//    o_swap_chain_desc.BufferCount = swap_chain_config_inst.buffer_count;
//    o_swap_chain_desc.BufferDesc.Width = swap_chain_config_inst.buffer_width;
//    o_swap_chain_desc.BufferDesc.Height = swap_chain_config_inst.buffer_haight;
//    o_swap_chain_desc.BufferDesc.Format = swap_chain_config_inst.buffer_format;
//    o_swap_chain_desc.BufferDesc.RefreshRate.Numerator = swap_chain_config_inst.buffer_numerator;
//    o_swap_chain_desc.BufferDesc.RefreshRate.Denominator = swap_chain_config_inst.buffer_denominator;
//    o_swap_chain_desc.BufferUsage = swap_chain_config_inst.buffer_usage;
//    o_swap_chain_desc.OutputWindow = window_handler;
//    o_swap_chain_desc.SampleDesc.Count = swap_chain_config_inst.buffer_sample_count;
//    o_swap_chain_desc.SampleDesc.Quality = swap_chain_config_inst.buffer_sample_quality;
//    o_swap_chain_desc.Windowed = swap_chain_config_inst.buffer_windowed;
//
//    return o_swap_chain_desc;
//}
//
//void create_device_and_swap_chain(DXGI_SWAP_CHAIN_DESC swap_chain_descriptor, device_config device_config_inst)
//{
//    HRESULT result = D3D11CreateDeviceAndSwapChain(
//        device_config_inst.adapter,
//        device_config_inst.driver_type,
//        device_config_inst.software_rasterizer,
//        device_config_inst.runtime_layer_flags,
//        &device_config_inst.feature_levels,
//        device_config_inst.feature_levels_number,
//        device_config_inst.sdk_version,
//        &swap_chain_descriptor,
//        &swap_chain,
//        &device,
//        device_config_inst.supported_feature_level,
//        &immediate_context);
//
//    // Def failed func
//    if (result < 0) {
//        throw std::invalid_argument("Failed to initialize device");
//    }
//}
//
//// gdi - graphics device instance
//class t_gdi_cfg {
//public:
//    t_gdi_cfg() = default;
//    t_gdi_cfg(t_gdi_cfg&& r_src) = default;
//    t_gdi_cfg(const t_gdi_cfg& cr_src) = default;
//    ~t_gdi_cfg() = default;
//
//public:
//    t_gdi_cfg& operator=(t_gdi_cfg&& r_src) = default;
//    t_gdi_cfg& operator=(const t_gdi_cfg& cr_src) = default;
//
//public:
//    t_swap_chain_cfg mo_swap_chain_cfg;
//    t_device_cfg mo_device_cfg;
//    t_depth_stencil_cfg mo_depth_stencil_cfg;
//};
//
//#else
//
//#endif