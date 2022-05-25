// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "array.h"


namespace engine {
    template<class type_name>
    class lead_ptr;
    template<class type_name>
    class slave_ptr;


    template<class type_name>
    class lead_ptr {
        public:
            template<class... type_args>
            lead_ptr(const type_args&... args);
            ~lead_ptr();

            lead_ptr(lead_ptr&& src) = default;
            lead_ptr(const lead_ptr& src) = delete;

            type_name* operator->();
            lead_ptr& operator=(lead_ptr&& src) = default;
            lead_ptr& operator=(const lead_ptr& src) = delete;

            slave_ptr<type_name>& create_slave_ptr();
            void destroy_slave_ptr(const slave_ptr<type_name>* ptr);
        private:
            type_name* obj_ptr;
            array< slave_ptr<type_name>* > slave_ptr_list;
    };
    template<class type_name>
    class slave_ptr {
        friend class lead_ptr<type_name>;
        public:
            ~slave_ptr() = default;

            slave_ptr(slave_ptr&& src) = default;
            slave_ptr(const slave_ptr& src) = default;

            type_name* operator->();
            slave_ptr& operator=(slave_ptr&& src) = default;
            slave_ptr& operator=(const slave_ptr& src) = default;
        private:
            lead_ptr<type_name>* obj_ptr;

            slave_ptr(const lead_ptr<type_name>* obj_ptr);
    };


    template<class type_name>
    template<class... type_args>
    lead_ptr<type_name>::lead_ptr(const type_args&... args) {
        obj_ptr = new type_name(args...);
    }
    template<class type_name>
    lead_ptr<type_name>::~lead_ptr() {
        for (size_t i = 0; i < slave_ptr_list.size(); ++i) {
            if (slave_ptr_list[i] != nullptr) {
                slave_ptr_list[i]->obj_ptr = nullptr;
            }
        }
        delete obj_ptr;
    }
    template<class type_name>
    type_name* lead_ptr<type_name>::operator->() {
        return obj_ptr;
    }
    template<class type_name>
    slave_ptr<type_name>& lead_ptr<type_name>::create_slave_ptr() {
        slave_ptr_list.append(new slave_ptr(this));
        return *slave_ptr_list[-1];
    }
    template<class type_name>
    void lead_ptr<type_name>::destroy_slave_ptr(const slave_ptr<type_name>* ptr) {
        slave_ptr_list[slave_ptr_list.find_index(ptr)] = nullptr;
    }


    template<class type_name>
    slave_ptr<type_name>::slave_ptr(const lead_ptr<type_name>* obj_ptr) :
        obj_ptr(obj_ptr) {
    }
    template<class type_name>
    slave_ptr<type_name>::~slave_ptr() {
        obj_ptr->destroy_slave_ptr(this);
    }
    template<class type_name>
    type_name* slave_ptr<type_name>::operator->() {
        return obj_ptr;
    }
}
