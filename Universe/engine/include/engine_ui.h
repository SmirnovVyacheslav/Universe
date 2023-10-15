// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine::ui
{
    class engine_ui
    {
    public:
        engine_ui();
        engine_ui(engine_ui&& src) = default;
        engine_ui(const engine_ui& src) = default;

        engine_ui& operator=(engine_ui&& src) = default;
        engine_ui& operator=(const engine_ui& src) = default;

        ~engine_ui();
    };
}
