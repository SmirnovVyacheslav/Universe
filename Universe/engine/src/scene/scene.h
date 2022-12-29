// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once
#include "src/object/object.h"


namespace engine {
    class scene {
    public:
        static scene inst;

        void add_object();
        object* get_object();
    private:
        object* square;

        scene() = default;
        scene(scene&& src) = default;
        scene(const scene& src) = default;

        scene& operator=(scene&& src) = default;
        scene& operator=(const scene& src) = default;

        ~scene() = default;
    };
}
