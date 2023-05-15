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
        private:   t_device* mp_direct_x;
    };


    void t_gdi::smf_c_gdi(const t_gdi_cfg* cr_gdi_cfg)
    {
        //
    }
    void t_gdi::smf_d_gdi()
    {
        //
    }
}
