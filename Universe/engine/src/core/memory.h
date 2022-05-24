// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    template<class type_name>
    class lead_ptr {
        public:
            lead_ptr() = default;
            ~lead_ptr() = default;

            lead_ptr(lead_ptr&& src) = default;
            lead_ptr(const lead_ptr& src) = delete;

            lead_ptr& operator=(lead_ptr&& src) = default;
            lead_ptr& operator=(const lead_ptr& src) = delete;
        private:
            type_name* obj_ptr;
    };
    template<class type_name>
    class slave_ptr {
        friend class lead_ptr<type_name>;
        public:
            ~slave_ptr() = default;

            slave_ptr(slave_ptr&& src) = default;
            slave_ptr(const slave_ptr& src) = default;

            slave_ptr& operator=(slave_ptr&& src) = default;
            slave_ptr& operator=(const slave_ptr& src) = default;
        private:
            slave_ptr() = default;
    };
}
