// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#pragma once


namespace engine {
    class renderer {
    public:
        static void render();
    private:
        static renderer inst;

        renderer() = default;
        renderer(renderer&& src) = default;
        renderer(const renderer & src) = default;

        renderer& operator=(renderer&& src) = default;
        renderer& operator=(const renderer& src) = default;

        ~renderer() = default;
    };
}
