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
//using t_swap_chain_desc = DXGI_SWAP_CHAIN_DESC;
//using t_hresult = HRESULT;
//
//const auto& f_c_device_and_swap_chain = D3D11CreateDeviceAndSwapChain;
//
//// gdi - graphics device instance
//class t_gdi {
//public:
//    t_gdi() = default;
//    t_gdi(t_gdi&& r_src) = default;
//    t_gdi(const t_gdi& cr_src) = default;
//    ~t_gdi() = default;
//
//public:
//    t_gdi& operator=(t_gdi&& r_src) = default;
//    t_gdi& operator=(const t_gdi& cr_src) = default;
//
//public:
//    void mf_c_gdi();
//    void mf_d_gdi();
//    // create shader
//    // create resource (mesh/model)
//    // set
//    // render
//    // device
//    // config
//private:
//    void mf_c_swap_chain_desc();
//    void mf_d_swap_chain_desc();
//    void mf_c_device_and_swap_chain();
//    void mf_d_device_and_swap_chain();
//    // depth stencil
//    // to file with namespace
//    void create_depth_stensil_surface();
//    void create_texture_2d();
//    void create_depth_stencil_data();
//    void create_depth_stencil_view();
//
//private:
//    t_gdi_cfg mo_device_cfg;
//    t_swap_chain_desc mo_swap_chain_desc;
//
//    // Context
//
//
//};
//
//t_device* f_c_device();
//
//class t_device {
//    t_device();
//    ~t_device();
//
//    void mf_c_device();
//    void mf_d_device();
//};
//
//
//class t_direcx_device {
//    //
//};
//
//#else
//
//#endif
