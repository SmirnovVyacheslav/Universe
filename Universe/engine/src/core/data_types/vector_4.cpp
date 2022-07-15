// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "vector_4.h"


namespace engine {
    vector_4_tmp::vector_4_tmp(real_32 x, real_32 y, real_32 z, real_32 w) : x(x), y(y), z(z), w(w) {
    }
    real_32& vector_4_tmp::operator[](const int_32 index) {
        return data[index];
    }
}
