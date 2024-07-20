// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

#include "ipf/iph_error.h"


#ifndef ENGINE_ERROR
#define ENGINE_ERROR

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

#endif
