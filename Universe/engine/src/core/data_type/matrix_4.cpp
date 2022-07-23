// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.
#include "matrix_4.h"


namespace engine {
    const int_32 matrix_size = 4;


    matrix_4::matrix_4() {
    }
    matrix_4::matrix_4(vector_4 row_1, vector_4 row_2, vector_4 row_3, vector_4 row_4) :
        row_1(row_1), row_2(row_2), row_3(row_3), row_4(row_4) {
    }
    vector_4& matrix_4::operator[](const int_32 index) {
        return data[(matrix_size + index % matrix_size) % matrix_size];
    }
    const vector_4& matrix_4::operator[](const int_32 index) const {
        return data[(matrix_size + index % matrix_size) % matrix_size];
    }
}