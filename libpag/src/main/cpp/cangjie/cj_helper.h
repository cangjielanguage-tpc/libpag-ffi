/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_HELPER_H
#define LIBPAG_CJ_CJ_HELPER_H

#include <pag/pag.h>
#include "cj_type.h"
#include "cj_string_util.h"
#include <tgfx/core/ImageInfo.h>

namespace pag {
extern "C" {
CJMarker* CreateMarker(const Marker* marker);
CJMarker* CreateMarkers(const std::vector<const Marker*>& markers);
float* CreateRect(const Rect& rect);
float* CreateMatrix(const Matrix& matrix);
Matrix GetMatrix(float* bytes);
long long MakeColorInt(uint32_t red, uint32_t green, uint32_t blue);
Color ToColor(int value);
CJPAGVideoRange* CreateVideoRanges(const std::vector<PAGVideoRange>& videoRanges);
CJPixelMap MakeSnapshot(std::shared_ptr<PAGSurface> surface);
}
}

#endif //LIBPAG_CJ_CJ_HELPER_H
