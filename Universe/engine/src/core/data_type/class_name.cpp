// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "class_name.h"


namespace engine {
    template <typename T> string class_name() {
        return typeid(T).name();
    };
}
