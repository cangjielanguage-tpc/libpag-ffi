/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_image.h"

namespace pag {

CJPAGImage::~CJPAGImage() { clear(); }

extern "C" {
int64_t cj_PAGImage_FromPath(const char *path)
{
    if (path == nullptr || path[0] == '\0') {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "Path is null or the string is empty.");
        return 0;
    }
    std::shared_ptr<PAGImage> surface = PAGImage::FromPath(path);
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "surface is null");
        return 0;
    }
    CJPAGImage *handler = new CJPAGImage(surface);
    if (!handler) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "Pointer is null.");
        return 0;
    }
    return (int64_t)handler;
}

int64_t cj_PAGImage_FromBytes(uint8_t *bytes, size_t length)
{
    if (bytes == nullptr || length == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromBytes", "bytes is null or the length is zero.");
        return 0;
    }
    std::shared_ptr<PAGImage> surface = PAGImage::FromBytes(bytes, length);
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromBytes", "surface is null");
        return 0;
    }
    CJPAGImage *handler = new CJPAGImage(surface);
    if (!handler) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromBytes", "handler is null.");
        return 0;
    }
    return (int64_t)handler;
}

int64_t cj_PAGImage_width(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_width", "Pointer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_width", "Invalid handler or internal image.");
        return -1;
    }
    return instance->get()->width();
}

int64_t cj_PAGImage_height(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_height", "Pointer is null");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_height", "Invalid handler or internal image.");
        return -1;
    }
    return instance->get()->height();
}

void cj_PAGImage_matrix(const int64_t ptr, float values[9])
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_matrix", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (instance && instance->get()) {
        Matrix matrix = instance->get()->matrix();
        matrix.get9(values);
    } else {
        Matrix matrix = {};
        matrix.setIdentity();
        matrix.get9(values);
    }
}

void cj_PAGImage_setMatrix(const int64_t ptr, float values[9])
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setMatrix", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (instance && instance->get()) {
        Matrix matrix = {};
        float scaleX = values[0];
        float skewX = values[1];
        float transX = values[2];
        float skewY = values[3];
        float scaleY = values[4];
        float transY = values[5];
        constexpr float MATRIX_HX = 0.0f;
        constexpr float MATRIX_HY = 0.0f;
        constexpr float MATRIX_W = 1.0f;
        matrix.setAll(scaleX, skewX, transX, skewY, scaleY, transY, MATRIX_HX, MATRIX_HY, MATRIX_W);
        instance->get()->setMatrix(matrix);
    } else {
        OH_LOG_Print(LOG_APP, LOG_WARN, LOG_DOMAIN, "cj_PAGImage_setMatrix", "Invalid instance");
    }
}

int32_t cj_PAGImage_scaleMode(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_scaleMode", "Pointer is null");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (!instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_scaleMode", "Invalid instance");
        return -1;
    }
    return instance->get()->scaleMode();
}

void cj_PAGImage_setScaleMode(const int64_t ptr, int32_t mode)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setScaleMode", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *instance = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (!instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setScaleMode", "Invalid instance");
        return;
    }
    return instance->get()->setScaleMode(mode);
}

void cj_PAGImage_release(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_release", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGImage *pagImage = reinterpret_cast<CJPAGImage *>(ptrInt);
    if (!pagImage) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_release", "Invalid instance");
        return;
    }
    delete pagImage;
}

ColorType ToTGFXColorType(int ohPixelFormat)
{
    switch (ohPixelFormat) {
        case PIXEL_FORMAT_RGBA_8888:
            return ColorType::RGBA_8888;
        case PIXEL_FORMAT_BGRA_8888:
            return ColorType::BGRA_8888;
        case PIXEL_FORMAT_ALPHA_8:
            return ColorType::ALPHA_8;
        case PIXEL_FORMAT_RGBA_F16:
            return ColorType::RGBA_F16;
        case PIXEL_FORMAT_RGB_565:
            return ColorType::RGB_565;
        default:
            return ColorType::Unknown;
    }
}

int64_t cj_PAGImage_FromPixelMap(CJPixelMap pixelMap)
{
    auto imageInfo = tgfx::ImageInfo::Make(static_cast<int>(pixelMap.width), static_cast<int>(pixelMap.height),
                                           tgfx::ColorType::BGRA_8888, tgfx::AlphaType::Premultiplied,
                                           static_cast<int>(pixelMap.size / pixelMap.height));
    bool alphaOnly =
        (imageInfo.colorType() == tgfx::ColorType::ALPHA_8) || (imageInfo.colorType() == tgfx::ColorType::Gray_8);
    tgfx::Bitmap bitmap;
    if (!bitmap.allocPixels(imageInfo.width(), imageInfo.height(), alphaOnly)) {
        return -1;
    }
    bitmap.writePixels(imageInfo, pixelMap.buf);
    auto image = tgfx::Image::MakeFrom(bitmap);
    if (!image) {
        return -1;
    }
    auto pagImage = pag::StillImage::MakeFrom(std::move(image));
    if (!pagImage) {
        return -1;
    }
    auto handler = new CJPAGImage(pagImage);
    if (!handler) {
        return -1;
    }
    return reinterpret_cast<int64_t>(handler);
}
}
} // namespace pag
