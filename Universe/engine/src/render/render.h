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

        //void set_api();
        //void create_device();
        //void compile_shader();
        //void set_geometry(int id);

    private:
        render() = default;
        ~render() = default;

        //arr device* device_inst;
        //arr ids;
    };
}
#endif
