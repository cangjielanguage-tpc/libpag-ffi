/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_type.h"
#include <hilog/log.h>
namespace pag {
extern "C" {
AlphaType getAlphaType(const uint8_t alphaType) {
    if (alphaType == 0) { // not initialized.uint8_t Unknown = 0
        return AlphaType::Unknown;
    } else if (alphaType == 1) { // Pixels are opaque.uint8_t  Opaque = 1
        return AlphaType::Opaque;
    } else if (alphaType == 2) { // The pixel components are pre multiplied by alpha.uint8_t  Premultiplied = 2
        return AlphaType::Premultiplied;
    } else if (alphaType == 3) { // The pixel component is independent of alpha.uint8_t  Unpremultiplied = 3
        return AlphaType::Unpremultiplied;
    } else {
        return AlphaType::Unknown;
    }
}

ColorType getColorType(const uint8_t colorType) {
    if (colorType == 0) {
        return ColorType::Unknown;
    } else if (colorType == 1) {
        return ColorType::ALPHA_8;
    } else if (colorType == 2) {
        return ColorType::RGBA_8888;
    } else if (colorType == 3) {
        return ColorType::BGRA_8888;
    } else if (colorType == 4) {
        return ColorType::RGB_565;
    } else if (colorType == 6) {
        return ColorType::RGBA_F16;
    } else {
        return ColorType::Unknown;
    }
}

void free_CPointer_CJMarker(CJMarker *ptr) {
    if (ptr != nullptr) {
        /*
         * Each CJMarker. mComment (char *) in the array is released in Cangjie using LibC. free (mComment). Directly
         * release the array memory here.
         */
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_CJPAGVideoRange(CJPAGVideoRange *ptr) {
    if (ptr != nullptr) {
        /*
         * There are no member variables of CJPAGVideoRange in the array that need to be released. Directly release the
         * array memory here.
         */
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_UInt8(uint8_t *ptr) {
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_Int64(int64_t *ptr) {
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_Float32(float *ptr) {
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_MarkersPAGLayer(MarkersPAGLayer ptr) {
    CJMarker *markers = ptr.markers;
    if (markers != nullptr) {
        free(markers);
    }
}

void free_CJPAGVideoRangeArray(CJPAGVideoRangeArray ptr) {
    CJPAGVideoRange *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}

void free_CJBytesArray(CJBytesArray ptr) {
    uint8_t *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}

void free_CJPtrArray(CJInt64Array ptr) {
    int64_t *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}
}
} // namespace pag
