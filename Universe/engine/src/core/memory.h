// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include <stdexcept>
#include "array.h"


namespace engine {
    template<class type_name>
    class lead_ptr;
    template<class type_name>
    class slave_ptr;


    template<class type_name>
    class lead_ptr {
        friend class lead_ptr<type_name>;
        public:
            lead_ptr() = default;
            ~lead_ptr();
            lead_ptr(lead_ptr&& src) = default;
            lead_ptr(const lead_ptr & src) = delete;

            template<class... type_args>
            void initialize(const type_args&... args);
            slave_ptr<type_name>& create_slave_ptr();

            type_name* operator->();
            lead_ptr& operator=(lead_ptr&& src) = default;
            lead_ptr& operator=(const lead_ptr& src) = delete;
        private:
            type_name* obj_ptr = nullptr;
            array< slave_ptr<type_name>* > slave_ptr_list;

            void destroy_slave_ptr(const slave_ptr<type_name>* ptr);
            void add_slave_ptr(const slave_ptr<type_name>* ptr);
            void update_slave_ptr(const slave_ptr<type_name>* old_ptr, const slave_ptr<type_name>* new_ptr);
    };
    template<class type_name>
    class slave_ptr {
        friend class lead_ptr<type_name>;
        public:
            ~slave_ptr();
            slave_ptr(slave_ptr&& src);
            slave_ptr(const slave_ptr& src);

            type_name* operator->();
            slave_ptr& operator=(slave_ptr&& src);
            slave_ptr& operator=(const slave_ptr& src);
        private:
            lead_ptr<type_name>* obj_ptr;

            slave_ptr(lead_ptr<type_name>* obj_ptr);
    };


    template<class type_name>
    lead_ptr<type_name>::~lead_ptr() {
        for (std::int32_t i = 0; i < slave_ptr_list.size(); ++i) {
            if (slave_ptr_list[i] != nullptr) {
                slave_ptr_list[i]->obj_ptr = nullptr;
            }
        }
        delete obj_ptr;
    }
    template<class type_name>
    template<class... type_args>
    void lead_ptr<type_name>::initialize(const type_args&... args) {
        if (obj_ptr != nullptr) {
            delete obj_ptr;
        }
        obj_ptr = new type_name(args...);
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
    void lead_ptr<type_name>::add_slave_ptr(const slave_ptr<type_name>* ptr) {
        slave_ptr_list.append(ptr);
    }
    template<class type_name>
    void lead_ptr<type_name>::update_slave_ptr(const slave_ptr<type_name>* old_ptr, const slave_ptr<type_name>* new_ptr) {
        slave_ptr_list[slave_ptr_list.find_index(old_ptr)] = new_ptr;
    }
    template<class type_name>
    type_name* lead_ptr<type_name>::operator->() {
        return obj_ptr;
    }


    template<class type_name>
    slave_ptr<type_name>::slave_ptr(lead_ptr<type_name>* obj_ptr) :
        obj_ptr(obj_ptr) {
    }
    template<class type_name>
    slave_ptr<type_name>::~slave_ptr() {
        obj_ptr->destroy_slave_ptr(this);
    }
    template<class type_name>
    slave_ptr<type_name>::slave_ptr(slave_ptr&& src) {
        obj_ptr = src.obj_ptr;
        obj_ptr->update_slave_ptr(&src, this);
        src.obj_ptr = nullptr;
    }
    template<class type_name>
    slave_ptr<type_name>::slave_ptr(const slave_ptr& src) {
        obj_ptr = src.obj_ptr;
        obj_ptr->add_slave_ptr(this);
    }
    template<class type_name>
    type_name* slave_ptr<type_name>::operator->() {
        if (obj_ptr == nullptr) {
            throw std::invalid_argument("Main object was deleted");
        }
        return obj_ptr;
    }
    template<class type_name>
    slave_ptr<type_name>& slave_ptr<type_name>::operator=(slave_ptr&& src) {
        if (this != &src) {
            obj_ptr = src.obj_ptr;
            obj_ptr->update_slave_ptr(&src, this);
            src.obj_ptr = nullptr;
        }
        return *this;
    }
    template<class type_name>
    slave_ptr<type_name>& slave_ptr<type_name>::operator=(const slave_ptr& src) {
        if (this != &src) {
            obj_ptr = src.obj_ptr;
            obj_ptr->add_slave_ptr(this);
        }
        return *this;
    }
}
