/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_type.h"
#include <hilog/log.h>

namespace pag {
extern "C" {
AlphaType getAlphaType(const uint8_t alphaType)
{
    switch (static_cast<AlphaType>(alphaType)) {
        case AlphaType::Unknown: // not initialized.uint8_t Unknown = 0
            return AlphaType::Unknown;
        case AlphaType::Opaque: // Pixels are opaque.uint8_t  Opaque = 1
            return AlphaType::Opaque;
        case AlphaType::Premultiplied: // The pixel components are pre multiplied by alpha.uint8_t  Premultiplied = 2
            return AlphaType::Premultiplied;
        case AlphaType::Unpremultiplied: // The pixel component is independent of alpha.uint8_t  Unpremultiplied = 3
            return AlphaType::Unpremultiplied;
        default:
            return AlphaType::Unknown;
    }
}

ColorType getColorType(const uint8_t colorType)
{
    switch (static_cast<ColorType>(colorType)) {
        case ColorType::Unknown:
            return ColorType::Unknown;
        case ColorType::ALPHA_8:
            return ColorType::ALPHA_8;
        case ColorType::RGBA_8888:
            return ColorType::RGBA_8888;
        case ColorType::BGRA_8888:
            return ColorType::BGRA_8888;
        case ColorType::RGB_565:
            return ColorType::RGB_565;
        case ColorType::RGBA_F16:
            return ColorType::RGBA_F16;
        default:
            return ColorType::Unknown;
    }
}

void free_CPointer_CJMarker(CJMarker *ptr)
{
    if (ptr != nullptr) {
        /*
         * Each CJMarker. mComment (CJBytesArray) in the array is released in Cangjie using free_CJBytesArray free 
         * (mComment). Directly release the array memory here.
         */
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_CJPAGVideoRange(CJPAGVideoRange *ptr)
{
    if (ptr != nullptr) {
        /*
         * There are no member variables of CJPAGVideoRange in the array that need to be released. Directly release the
         * array memory here.
         */
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_UInt8(uint8_t *ptr)
{
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_Int64(int64_t *ptr)
{
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_CPointer_Float32(float *ptr)
{
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

void free_MarkersPAGLayer(MarkersPAGLayer ptr)
{
    CJMarker *markers = ptr.markers;
    if (markers != nullptr) {
        free(markers);
    }
}

void free_CJPAGVideoRangeArray(CJPAGVideoRangeArray ptr)
{
    CJPAGVideoRange *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}

void free_CJBytesArray(CJBytesArray ptr)
{
    if (ptr.size == 0) {
        return;
    }
    uint8_t *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}

void free_CJPtrArray(CJInt64Array ptr)
{
    int64_t *buf = ptr.buf;
    if (buf != nullptr) {
        free(buf);
    }
}
}
} // namespace pag
