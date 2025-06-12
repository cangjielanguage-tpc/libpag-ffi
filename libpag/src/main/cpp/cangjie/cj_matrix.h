/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_MATRIX_H
#define LIBPAG4CJ_CJ_MATRIX_H

#include <pag/pag.h>
#include "cj_type.h"

class CJMatrix {
    public:
        explicit CJMatrix(std::shared_ptr<pag::Matrix> matrix) : matrix(matrix) {
        }

        std::shared_ptr<pag::Matrix> get() {
            return matrix;
        }

        void clear() {
            matrix = nullptr;
        }

    private:
        std::shared_ptr<pag::Matrix> matrix;
};

#endif //LIBPAG4CJ_CJ_MATRIX_H
