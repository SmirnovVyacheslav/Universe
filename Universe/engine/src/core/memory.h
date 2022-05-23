// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef MEMORY_H
#define MEMORY_H


namespace engine
{
    template<class type_name>
    class lead_ptr
    {
    public:
        explicit lead_ptr() = default;
        ~lead_ptr() = default;

    private:
        type_name* obj;
    };


    template<class type_name>
    class slave_ptr
    {

    };
}
#endif
