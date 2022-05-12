// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef RENDER_H
#define RENDER_H


namespace engine
{
    class render
    {
    public:
        static render inst;

        void start_render();

    private:
        render() = default;
        ~render() = default;
    };
}
#endif
