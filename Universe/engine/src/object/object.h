// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class object {
    public:
        object();
        object(object&& src) = default;
        object(const object & src) = delete;

        object& operator=(object&& src) = default;
        object& operator=(const object& src) = delete;

        ~object() = default;
    private:
        int id;
    };
}
