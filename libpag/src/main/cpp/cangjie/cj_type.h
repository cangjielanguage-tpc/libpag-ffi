/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_TYPE_H
#define LIBPAG_CJ_CJ_TYPE_H

#include "cj_marker.h"
#include "../../external/include/pag/types.h"
#include <hilog/log.h>

extern "C" {

struct CJBytesArray {
    long long size;
    uint8_t *buf;
};

struct CJInt64Array {
    long long size;
    int64_t *buf;
};

struct CJFloat32Array {
    long long size;
    float *buf;
};

struct MarkersPAGLayer {
    long long size;
    CJMarker *markers;
};

struct CJPAGVideoRange {
    long long startTime;
    long long endTime;
    long long playDuration;
    bool reversed;
};

struct CJPAGVideoRangeArray {
    long long size;
    CJPAGVideoRange *buf;
};

struct CJPixelMap {
    long long size;
    uint8_t *buf;
    uint8_t alphaType;
    bool editable;
    uint8_t pixelFormat;
    int32_t height;
    int32_t width;
};
}

namespace pag {
extern "C" {
AlphaType getAlphaType(const uint8_t alphaType);
ColorType getColorType(const uint8_t colorType);
void free_CPointer_CJMarker(CJMarker *ptr);
void free_CPointer_CJPAGVideoRange(CJPAGVideoRange *ptr);
void free_CPointer_UInt8(uint8_t *ptr);
void free_CPointer_Int64(int64_t *ptr);
void free_CPointer_Float32(float *ptr);
void free_MarkersPAGLayer(MarkersPAGLayer ptr);
void free_CJPAGVideoRangeArray(CJPAGVideoRangeArray ptr);
void free_CJBytesArray(CJBytesArray ptr);
void free_CJPtrArray(CJInt64Array ptr);
}
} // namespace pag


/**
 * Describes how to interpret the alpha component of a pixel.
 * Corresponding to Cangjie's AlphaType and C++'s enum class AlphaType.
 */
typedef struct {
    /**
     * uninitialized.UInt8 = 0
     */
    uint8_t Unknown;
    /**
     * pixel is opaque.UInt8 = 1
     */
    uint8_t Opaque;
    /**
     * pixel components are premultiplied by alpha.UInt8 = 2
     */
    uint8_t Premultiplied;
    /**
     * pixel components are independent of alpha.UInt8 = 3
     */
    uint8_t Unpremultiplied;

} PAGAlphaType;

/**
 * Describes how pixel bits encode color. These values match up with the enum in Bitmap.Config on
 * Android platform.
 * Corresponding to PixelMapFormat for Cangjie and enum class ColorType for C++.
 */
typedef struct {
    /**
     * uninitialized.UInt8 = 0
     */
    uint8_t Unknown;
    /**
     * Each pixel is stored as a single translucency (alpha) channel. This is very useful for
     * storing masks efficiently, for instance. No color information is stored. With this
     * configuration, each pixel requires 1 byte of memory.UInt8 = 1
     */
    uint8_t ALPHA_8;
    /**
     * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
     * bits of precision (256 possible values). The channel order is: red, green, blue, alpha.UInt8 = 2
     */
    uint8_t RGBA_8888;
    /**
     * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
     * bits of precision (256 possible values). The channel order is: blue, green, red, alpha.UInt8 = 3
     */
    uint8_t BGRA_8888;
    /**
     * Each pixel is stored on 2 bytes, and only the RGB channels are encoded: red is stored with 5
     * bits of precision (32 possible values), green is stored with 6 bits of precision (64 possible
     * values), and blue is stored with 5 bits of precision.UInt8 = 4
     */
    uint8_t RGB_565;
    /**
     * Each pixel is stored as a single grayscale level. No color information is stored. With this
     * configuration, each pixel requires 1 byte of memory.UInt8 = 5
     */
    uint8_t Gray_8;
    /**
     * Each pixel is stored on 8 bytes. Each channel (RGB and alpha for translucency) is stored as a
     * half-precision floating point value. This configuration is particularly suited for wide-gamut
     * and HDR content.UInt8 = 6
     */
    uint8_t RGBA_F16;
    /**
     * Each pixel is stored on 4 bytes. Each RGB channel is stored with 10 bits of precision (1024
     * possible values). There is an additional alpha channel that is stored with 2 bits of precision
     * (4 possible values). This configuration is suited for wide-gamut and HDR content which does not
     * require alpha blending, such that the memory cost is the same as RGBA_8888 while enabling
     * higher color precision.UInt8 = 7
     */
    uint8_t RGBA_1010102;
} PAGColorType;
#endif // LIBPAG_CJ_CJ_TYPE_H
