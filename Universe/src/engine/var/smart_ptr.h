// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_smart_ptr.h"


#ifndef ENGINE_SMART_PTR
#define ENGINE_SMART_PTR

namespace engine
{
    template<typename T>
    class lead_ptr;
    template<typename T>
    class slave_ptr;


    template<typename T>
    class lead_ptr
    {
    public:
        lead_ptr() = default;
        lead_ptr(lead_ptr&& src) = default;
        lead_ptr(const lead_ptr & src) = delete;

        template<typename... A>
        void initialize(A&&... args);
        template<typename D, typename... A>
        void initialize_derivative(A&&... args);
        slave_ptr<T>& create_slave_ptr();

        lead_ptr& operator=(lead_ptr&& src) = default;
        lead_ptr& operator=(const lead_ptr& src) = delete;
        T* operator->();
        T& operator*();

        ~lead_ptr();
    private:
        T* obj_ptr = nullptr;
        array<slave_ptr<T>*> slave_ptr_array;

        void add_slave_ptr(slave_ptr<T>* ptr);
        void update_slave_ptr(slave_ptr<T>* old_ptr, slave_ptr<T>* new_ptr);
        void destroy_slave_ptr(slave_ptr<T>* ptr);
        void terminate();

        friend class slave_ptr<T>;
    };

    template<typename T>
    class slave_ptr
    {
    public:
        slave_ptr();
        slave_ptr(slave_ptr&& src);
        slave_ptr(const slave_ptr& src);

        slave_ptr& operator=(slave_ptr&& src);
        slave_ptr& operator=(const slave_ptr& src);
        T* operator->();

        ~slave_ptr();
    private:
        lead_ptr<T>* obj_ptr = nullptr;

        slave_ptr(lead_ptr<T>* obj_ptr);

        friend class lead_ptr<T>;
    };

    template<typename T>
    template<typename... A>
    void lead_ptr<T>::initialize(A&&... args)
    {
        if (obj_ptr != nullptr)
        {
            terminate();
        }
        obj_ptr = new T(std::forward<A>(args)...);
    }

    template<typename T>
    template<typename D, typename... A>
    void lead_ptr<T>::initialize_derivative(A&&... args)
    {
        if (obj_ptr != nullptr)
        {
            terminate();
        }
        obj_ptr = new D(std::forward<A>(args)...);
    }

    template<typename T>
    void lead_ptr<T>::terminate()
    {
        for (int32 i = 0; i < slave_ptr_array.size(); ++i)
        {
            if (slave_ptr_array[i] != nullptr)
            {
                slave_ptr_array[i]->obj_ptr = nullptr;
            }
        }
        delete obj_ptr;
        obj_ptr = nullptr;
    }

    template<typename T>
    slave_ptr<T>& lead_ptr<T>::create_slave_ptr()
    {
        if (obj_ptr == nullptr)
        {
            throw error("Main object was not initialized");
        }
        slave_ptr_array.append(new slave_ptr(this));
        return *slave_ptr_array[-1];
    }

    template<typename T>
    void lead_ptr<T>::destroy_slave_ptr(slave_ptr<T>* ptr)
    {
        slave_ptr_array[slave_ptr_array.find_index(ptr)] = nullptr;
    }

    template<typename T>
    void lead_ptr<T>::add_slave_ptr(slave_ptr<T>* ptr)
    {
        slave_ptr_array.append(ptr);
    }

    template<typename T>
    void lead_ptr<T>::update_slave_ptr(slave_ptr<T>* old_ptr, slave_ptr<T>* new_ptr)
    {
        slave_ptr_array[slave_ptr_array.find_index(old_ptr)] = new_ptr;
    }

    template<typename T>
    T* lead_ptr<T>::operator->()
    {
        if (obj_ptr == nullptr)
        {
            throw error("Main object was not initialized");
        }
        return obj_ptr;
    }

    template<typename T>
    T& lead_ptr<T>::operator*()
    {
        if (obj_ptr == nullptr)
        {
            throw error("Main object was not initialized");
        }
        return *obj_ptr;
    }

    template<typename T>
    lead_ptr<T>::~lead_ptr()
    {
        terminate();
    }


    template<typename T>
    slave_ptr<T>::slave_ptr() : obj_ptr(nullptr) {}

    template<typename T>
    slave_ptr<T>::slave_ptr(lead_ptr<T>* obj_ptr) : obj_ptr(obj_ptr) {}

    template<typename T>
    slave_ptr<T>::slave_ptr(slave_ptr&& src)
    {
        obj_ptr = src.obj_ptr;
        obj_ptr->update_slave_ptr(&src, this);
        src.obj_ptr = nullptr;
    }

    template<typename T>
    slave_ptr<T>::slave_ptr(const slave_ptr& src)
    {
        obj_ptr = src.obj_ptr;
        obj_ptr->add_slave_ptr(this);
    }

    template<typename T>
    slave_ptr<T>& slave_ptr<T>::operator=(slave_ptr&& src)
    {
        if (this != &src)
        {
            if (obj_ptr != nullptr)
            {
                obj_ptr->destroy_slave_ptr(this);
            }
            obj_ptr = src.obj_ptr;
            obj_ptr->update_slave_ptr(&src, this);
            src.obj_ptr = nullptr;
        }
        return *this;
    }

    template<typename T>
    slave_ptr<T>& slave_ptr<T>::operator=(const slave_ptr& src)
    {
        if (this != &src)
        {
            if (obj_ptr != nullptr)
            {
                obj_ptr->destroy_slave_ptr(this);
            }
            obj_ptr = src.obj_ptr;
            obj_ptr->add_slave_ptr(this);
        }
        return *this;
    }

    template<typename T>
    T* slave_ptr<T>::operator->()
    {
        if (obj_ptr == nullptr)
        {
            throw error("Main object was deleted");
        }
        return obj_ptr->operator->();
    }

    template<typename T>
    slave_ptr<T>::~slave_ptr()
    {
        obj_ptr->destroy_slave_ptr(this);
        obj_ptr = nullptr;
    }
}

#endif
