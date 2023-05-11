// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/gdi_cfg.h"


namespace engine {
    class t_device {
    protected:
        t_device() = default;
    public:
        virtual ~t_device() = default;
        virtual void mf_c_device() = 0;
        virtual void mf_d_device() = 0;

    public:
        t_device(t_device&& r_src) = delete;
        t_device(const t_device& cr_src) = delete;
        t_device& operator=(t_device&& r_src) = delete;
        t_device& operator=(const t_device& cr_src) = delete;
    };


    t_device* gf_c_device(const t_gdi_cfg& cr_dgi_cfg);
}
