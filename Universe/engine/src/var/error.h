// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#pragma once

#include <stdexcept>



namespace engine
{
    class error : public std::exception
    {
    public:
        error(const char* message);
        error(error&& src) = default;
        error(const error& src) = default;

        const char* what();

        error& operator=(error&& src) = default;
        error& operator=(const error& src) = default;
    private:
        const char* message;
    };
}
