/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_image.h"

namespace pag {

CJPAGImage::~CJPAGImage() { clear(); }

extern "C" {
int64_t cj_PAGImage_FromPath(const char *path) {
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

int64_t cj_PAGImage_FromBytes(uint8_t *bytes, size_t length) {
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

int64_t cj_PAGImage_width(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_width", "Pointer is null.");
        return -1;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_width", "Invalid handler or internal image.");
        return -1;
    }
    return instance->get()->width();
}

int64_t cj_PAGImage_height(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_height", "Pointer is null");
        return -1;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_height", "Invalid handler or internal image.");
        return -1;
    }
    return instance->get()->height();
}

void cj_PAGImage_matrix(const int64_t ptr, float values[9]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_matrix", "Pointer is null");
        return;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (instance && instance->get()) {
        Matrix matrix = instance->get()->matrix();
        matrix.get9(values);
    } else {
        Matrix matrix = {};
        matrix.setIdentity();
        matrix.get9(values);
    }
}

void cj_PAGImage_setMatrix(const int64_t ptr, float values[9]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setMatrix", "Pointer is null");
        return;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (instance && instance->get()) {
        Matrix matrix = {};
        matrix.setAll(values[0], values[1], values[2], values[3], values[4], values[5], 0, 0, 1);
        instance->get()->setMatrix(matrix);
    } else {
        OH_LOG_Print(LOG_APP, LOG_WARN, LOG_DOMAIN, "cj_PAGImage_setMatrix", "Invalid instance");
    }
}

int32_t cj_PAGImage_scaleMode(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_scaleMode", "Pointer is null");
        return -1;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (!instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_scaleMode", "Invalid instance");
        return -1;
    }
    return instance->get()->scaleMode();
}

void cj_PAGImage_setScaleMode(const int64_t ptr, int32_t mode) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setScaleMode", "Pointer is null");
        return;
    }
    CJPAGImage *instance = (CJPAGImage *)ptr;
    if (!instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_setScaleMode", "Invalid instance");
        return;
    }
    return instance->get()->setScaleMode(mode);
}

void cj_PAGImage_release(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_release", "Pointer is null");
        return;
    }
    CJPAGImage *pagImage = (CJPAGImage *)ptr;
    if (pagImage) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_release", "Invalid instance");
        return;
    }
    delete pagImage;
}

ColorType ToTGFXColorType(int ohPixelFormat) {
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
    }
    return ColorType::Unknown;
}

//TODO:FromPixelMap有问题
// int64_t cj_PAGImage_FromPixelMap(const int64_t ptr, CJPixelMap pixelMap) {
//     auto rowSize=0;
//    auto imageInfo = tgfx::ImageInfo::Make(static_cast<int>(pixelMap.width), static_cast<int>(pixelMap.height),
//                                    ToTGFXColorType(pixelMap.pixelFormat),
//                                    pixelMap.alphaType, rowSize);

//  bool alphaOnly =
//      imageInfo.colorType() == ColorType::ALPHA_8 || imageInfo.colorType() == ColorType::Gray_8;
//
//  Bitmap bitmap = {};
//  if (!bitmap.allocPixels(imageInfo.width(), imageInfo.height(), alphaOnly)) {
//    LOGE("OHOSBitmap::CopyBitmap() Bitmap Failed to allocPixels");
//    return {};
//  }
//  void* pixel;
//  errorCode = OH_PixelMap_AccessPixels(pixelmap, &pixel);
//  if (errorCode != IMAGE_RESULT_SUCCESS) {
//    LOGE("OHOSBitmap::CopyBitmap() OH_PixelMap_AccessPixels failed");
//    return {};
//  }
//  bitmap.writePixels(imageInfo, pixel);
//  OH_PixelMap_UnAccessPixels(pixelmap);
//  return bitmap;
//
//    
//  auto bitmap = tgfx::OHOSPixelMap::CopyBitmap(env, args[0]);
//  auto image = tgfx::Image::MakeFrom(bitmap);
//  if (image == nullptr) {
//    return nullptr;
//  }
//  auto pagImage = pag::StillImage::MakeFrom(std::move(image));
//  return JPAGImage::ToJs(env, pagImage);


//    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, "cj_PAGImage_FromPath", "path:%{public}s", path);
//    // 检查字符串指针是否为 NULL 或者字符串是否为空
//    if (path == nullptr || path[0] == '\0') {
//        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "Path is null or the string is empty.");
//        return 0;
//    }
//    std::shared_ptr<PAGImage> surface = PAGImage::FromPath(path);
//    if (!surface) {
//        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "surface is null");
//        return 0;
//    }
//    CJPAGImage *handler = new CJPAGImage(surface);
//    if (handler == NULL) {
//        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImage_FromPath", "Pointer is null.");
//        return 0;
//    }
//    return (int64_t)handler;
//}
}
} // namespace pag
