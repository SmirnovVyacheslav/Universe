// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "gri.h"


namespace engine
{
    class t_gri_impl: public t_gri
    {
        public:    static t_gri_impl* mp_inst;

        public:    t_gri_impl() = default;
        public:    t_gri_impl(t_gri_impl&& r_src) = delete;
        public:    t_gri_impl(const t_gri_impl& cr_src) = delete;
        public:    ~t_gri_impl() = default;

        public:    t_gri_impl& operator=(t_gri_impl&& r_src) = delete;
        public:    t_gri_impl& operator=(const t_gri_impl& cr_src) = delete;
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
}
