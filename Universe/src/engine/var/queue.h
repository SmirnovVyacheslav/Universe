// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "error.h"
#include <queue>

#ifndef ENGINE_VAR_QUEUE
#define ENGINE_VAR_QUEUE

namespace engine
{
    template <typename t>
    class queue
    {
    public:
        queue()                 = default;
        queue(queue&& src)      = delete;
        queue(const queue& src) = delete;

        void add(t& item)
        {
            q.push(item);
        }
        t get()
        {
            if (q.empty())
            {
                throw error("Queue is empty");
            }

            t item = q.front();
            q.pop();
            return item;
        }

        operator bool()
        {
            return !q.empty();
        }

        queue& operator=(queue&& src)      = delete;
        queue& operator=(const queue& src) = delete;

        ~queue() = default;
    private:
        std::queue<t> q;
    };
}

#endif
