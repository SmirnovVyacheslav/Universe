// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    template<class type_name>
    class lead_ptr {
        public:
            lead_ptr() = default;
            ~lead_ptr() = default;

            lead_ptr(lead_ptr&& src_ptr) = default;
            lead_ptr(const lead_ptr& src_ptr) = delete;

            lead_ptr& operator=(lead_ptr&& src_ptr) = default;
            lead_ptr& operator=(const lead_ptr& src_ptr) = delete;
        private:
            type_name* obj_ptr;
    };
    template<class type_name>
    class slave_ptr {

    };
}
