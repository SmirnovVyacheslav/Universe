// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "src/gdi/device.h"
#include "src/gdi/gdi_cfg.h"


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
    };


    t_device* t_device::smf_c_direct_x(const t_gdi_cfg& cr_dgi_cfg)
    {
        return new dx_device(&cr_dgi_cfg);
    }


    dx_device::dx_device(const t_gdi_cfg* cr_gdi_cfg)
    {
        //
    }
}
