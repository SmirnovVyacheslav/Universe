// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "gdi.h"

#include "src/gdi/device.h"

        // create shader
        // create resource (mesh/model)
        // set
        // render
        // device
        // config


namespace engine
{
    class t_gdi_impl : public t_gdi
    {
        public:    t_gdi_impl(const t_gdi_cfg* cr_gdi_cfg);
        public:    t_gdi_impl(t_gdi_impl&& r_src) = delete;
        public:    t_gdi_impl(const t_gdi_impl& cr_src) = delete;
        public:    ~t_gdi_impl();

        public:    t_gdi_impl& operator=(t_gdi_impl&& r_src) = delete;
        public:    t_gdi_impl& operator=(const t_gdi_impl& cr_src) = delete;

        private:   t_device* mp_direct_x;
    };


    t_gdi* t_gdi::smf_c_gdi(const t_gdi_cfg* cr_gdi_cfg)
    {
        return new t_gdi_impl(cr_gdi_cfg);
    }
    //void t_gdi::smf_d_gdi()
    //{
    //    //
    //}


    t_gdi_impl::t_gdi_impl(const t_gdi_cfg* cr_gdi_cfg) {
        mp_direct_x = t_device::smf_c_directx(*cr_gdi_cfg);
    }
    t_gdi_impl::~t_gdi_impl() {
        delete mp_direct_x;
    }
}
