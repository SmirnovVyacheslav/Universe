// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "src/object/object.h"


namespace engine
{
    class scene
    {
    public:
        static scene inst;

        void add_object();
        object* get_object();

    private:
        scene() = default;
        ~scene() = default;

        object* square;
    };
}
#endif
