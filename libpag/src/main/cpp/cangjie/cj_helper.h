/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_HELPER_H
#define LIBPAG_CJ_CJ_HELPER_H
#include "cj_string_util.h"
#include "cj_type.h"
#include <hilog/log.h>
#include <pag/pag.h>
#include <tgfx/core/ImageInfo.h>

namespace pag {
extern "C" {
CJMarker *CreateMarker(const Marker *marker);
CJMarker *CreateMarkers(const std::vector<const Marker *> &markers);
float *CreateRect(const Rect &rect);
float *CreateMatrix(const Matrix &matrix);
Matrix GetMatrix(float *bytes);
long long MakeColorInt(uint32_t red, uint32_t green, uint32_t blue);
Color ToColor(int value);
CJPAGVideoRange *CreateVideoRanges(const std::vector<PAGVideoRange> &videoRanges);
CJPixelMap MakeSnapshot(std::shared_ptr<PAGSurface> surface);
void safe_memcpy(void *dest, uint32_t dest_size, const void *src, uint32_t src_size);
}
CJBytesArray stringToCJBytesArray(const std::string &str);
std::string CJBytesArraytoString(const CJBytesArray &bytes);

enum class AnimationState : int {
    Start = 0,
    Cancel = 1,
    End = 2,
    Repeat = 3
};

enum LayerTypeCode : int8_t {
    LAYER_TYPE_UNKNOWN = 0,
    LAYER_TYPE_NULL = 1,
    LAYER_TYPE_SOLID = 2,
    LAYER_TYPE_TEXT = 3,
    LAYER_TYPE_SHAPE = 4,
    LAYER_TYPE_IMAGE = 5,
    LAYER_TYPE_PRECOMPOSE = 6,
    LAYER_TYPE_CAMERA = 7,
};
} // namespace pag
#endif // LIBPAG_CJ_CJ_HELPER_H
