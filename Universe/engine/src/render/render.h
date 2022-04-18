// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef RENDER_H
#define RENDER_H


namespace engine
{
    class render;
    class device;
    class window;


    static render inst;

    class render
    {
    public:
        void create_device(api);
        void set_geometry(int id);
        void start_render();
        void stop_render();

    private:
        arr device* device_inst;
        arr ids;

        render();
        ~render();
    };

    // To cpp
    render render::inst = render();

    class engine_mng_ui;
    using engine_mng_ptr = std::shared_ptr<engine_mng_ui>;


    class engine_mng_ui
    {
    public:
        const window_mng_ptr window_mng;

        static engine_mng_ptr create();

    protected:
        engine_mng_ui() = default;
        virtual ~engine_mng_ui() = default;
    };
}
#endif
