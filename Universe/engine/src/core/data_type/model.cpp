// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.
#include "model.h"


namespace engine {
    std::istream& operator>>(std::istream& in_stream, model& model_obj) {
        return in_stream;
    }
    std::ostream& operator<<(std::ostream& out_stream, const model& model_obj) {
        return out_stream;
    }
}
