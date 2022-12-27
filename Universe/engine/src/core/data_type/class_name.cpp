// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "class_name.h"


namespace engine {
    template <class type_name>
    string class_name() {
        return typeid(type_name).name();
    };
}
