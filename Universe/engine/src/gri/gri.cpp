// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "gri.h"

#include "src/gdi/gdi.h"
#include "src/gdi/gdi_cfg.h"

#include "src/core/config.h"
#include "src/platform/window.h"


namespace engine
{
    class t_gri_impl: public t_gri
    {
        public:    static t_gri_impl* mp_inst;

        public:    t_gri_impl();
        public:    t_gri_impl(t_gri_impl&& r_src) = delete;
        public:    t_gri_impl(const t_gri_impl& cr_src) = delete;
        public:    ~t_gri_impl();

        public:    t_gri_impl& operator=(t_gri_impl&& r_src) = delete;
        public:    t_gri_impl& operator=(const t_gri_impl& cr_src) = delete;

              t_gdi* mp_gdi = nullptr;
              t_gdi_cfg mo_gdi_cfg;
    };
    t_gri_impl* t_gri_impl::mp_inst = nullptr;


    void t_gri::smf_c_gri()
    {
        smf_d_gri();
        t_gri_impl::mp_inst = new t_gri_impl;
    }
    void t_gri::smf_d_gri()
    {
        delete t_gri_impl::mp_inst;
    }


    t_gri_impl::t_gri_impl()
    {
        platform::window::create_window();
        mo_gdi_cfg.mp_window_handler = reinterpret_cast<void*>(platform::window::id());
        mp_gdi = t_gdi::smf_c_gdi(&mo_gdi_cfg);
    }
    t_gri_impl::~t_gri_impl()
    {
        delete mp_gdi;
    }
}
