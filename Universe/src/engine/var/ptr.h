// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "error.h"

#ifndef ENGINE_VAR_PTR
#define ENGINE_VAR_PTR

namespace engine
{
    template <typename T>
    class ptr
    {
    public:
        ptr() = default;
        ptr(ptr&& src) = delete;
        ptr(const ptr& src) = delete;

        template<typename... A>
        void init(A&&... args);
        void term();

        T* operator->();
        ptr& operator=(ptr&& src) = delete;
        ptr& operator=(const ptr& src) = delete;

        ~ptr();
    private:
        T* obj_ptr = nullptr;
    };

    template <typename T>
    class ref
    {
    public:
        ref(ptr<T>* obj_ptr);
        ref(ref&& src) = default;
        ref(const ref& src) = default;

        T* operator->();
        ref& operator=(ref&& src) = default;
        ref& operator=(const ref& src) = default;

        ~ref() = default;
    private:
        ptr<T>* obj_ptr = nullptr;
    };


    template<typename T>
    template<typename... A>
    void ptr<T>::init(A&&... args)
    {
        term();
        obj_ptr = new T(std::forward<A>(args)...);
    }

    template<typename T>
    void ptr<T>::term()
    {
        delete obj_ptr;
        obj_ptr = nullptr;
    }

    template<typename T>
    T* ptr<T>::operator->()
    {
        if (obj_ptr == nullptr)
        {
            throw error("Object was not initialized");
        }
        return obj_ptr;
    }

    template<typename T>
    ptr<T>::~ptr()
    {
        term();
    }


    template<typename T>
    ref<T>::ref(ptr<T>* obj_ptr) : obj_ptr(obj_ptr) {}

    template<typename T>
    T* ref<T>::operator->()
    {
        return obj_ptr->operator->();
    }
}

#endif
