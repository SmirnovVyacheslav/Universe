// Copyright: (C) 2022-2023 Vyacheslav Smirnov. All rights reserved.
#include "class_name.h"


namespace engine {
    template <typename T>
    string class_name() {
        return typeid(T).name();
    };
}
