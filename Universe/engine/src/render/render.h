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

        //void create_device(api);
        //void set_geometry(int id);
        //void start_render();
        //void stop_render();

    private:
        render() = default;
        ~render() = default;

        //arr device* device_inst;
        //arr ids;
    };
}
#endif
