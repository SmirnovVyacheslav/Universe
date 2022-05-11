// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "src/resource/mesh.h"


namespace engine
{
    class object
    {
    public:
        object();
        ~object() = default;

    private:
        int id;
        mesh square;
    };
}
#endif
