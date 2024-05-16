// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "def/incl_h_queue.h"


#ifndef ENGINE_EVENT
#define ENGINE_EVENT

namespace engine
{
    template <typename T>
    class queue
    {
    public:
        queue() = default;
        queue(queue&& src) = delete;
        queue(const queue& src) = delete;

        void add(T& item);
        T& get();

        queue& operator=(queue&& src) = delete;
        queue& operator=(const queue& src) = delete;

        ~queue() = default;
    private:
        T item;
    };


    template <typename T>
    void queue<T>::add(T& item)
    {
        this->item = item;
    }

    template <typename T>
    T& queue<T>::get()
    {
        return item;
    }
}

#endif
