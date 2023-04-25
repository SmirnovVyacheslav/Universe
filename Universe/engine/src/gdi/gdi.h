// Copyright: (C) 2023 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/gdi/device.h"
#include "src/gdi/gdi_cfg.h"


namespace engine {
    class t_gdi {
        public:
        t_gdi() = default;
        t_gdi(t_gdi&& r_src) = delete;
        t_gdi(const t_gdi& cr_src) = delete;
        ~t_gdi() = default;

        public:
        t_gdi& operator=(t_gdi&& r_src) = delete;
        t_gdi& operator=(const t_gdi& cr_src) = delete;

        public:
        void mf_c_gdi(const t_gdi_cfg* cr_gdi_cfg);
        void mf_d_gdi();
        // create shader
        // create resource (mesh/model)
        // set
        // render
        // device
        // config
 
        private:
        t_device* mp_device;
        t_gdi_cfg* mp_gdi_cfg;
    };
}
