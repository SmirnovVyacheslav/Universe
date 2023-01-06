// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class object_id {
    public:
        static object_id inst;

        int get_object_id();
    private:
        int next_id;

        object_id() = default;
        object_id(object_id&& src) = default;
        object_id(const object_id & src) = default;

        object_id& operator=(object_id&& src) = default;
        object_id& operator=(const object_id& src) = default;

        ~object_id() = default;
    };
}
