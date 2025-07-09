/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#pragma once

#include "cj_type.h"
#include <hilog/log.h>
#include <multimedia/image_framework/image/pixelmap_native.h>
#include <pag/pag.h>
#include <rendering/editing/StillImage.h>
#include <tgfx/core/Bitmap.h>
#include <tgfx/core/ColorType.h>
#include <tgfx/core/Image.h>
#include <tgfx/core/ImageInfo.h>

namespace pag {
class CJPAGImage {
public:
    explicit CJPAGImage(std::shared_ptr<PAGImage> pagImage) : pagImage(pagImage) {}

    virtual ~CJPAGImage();

    std::shared_ptr<PAGImage> get() {
        std::lock_guard lock_guard(locker);
        return pagImage;
    }

    void clear() {
        std::lock_guard lock_guard(locker);
        pagImage = nullptr;
    }

private:
    std::shared_ptr<pag::PAGImage> pagImage;
    std::mutex locker;
};

extern "C" {
int64_t cj_PAGImage_FromPath(const char *path);
int64_t cj_PAGImage_FromBytes(uint8_t *bytes, size_t length);
int64_t cj_PAGImage_width(const int64_t ptr);
int64_t cj_PAGImage_height(const int64_t ptr);
void cj_PAGImage_matrix(const int64_t ptr, float values[9]);
void cj_PAGImage_setMatrix(const int64_t ptr, float values[9]);
int32_t cj_PAGImage_scaleMode(const int64_t ptr);
void cj_PAGImage_setScaleMode(const int64_t ptr, int32_t mode);
void cj_PAGImage_release(const int64_t ptr);
int64_t cj_PAGImage_FromPixelMap(CJPixelMap pixelMap);
}
}