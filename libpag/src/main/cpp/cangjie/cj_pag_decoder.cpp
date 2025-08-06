/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_decoder.h"

namespace pag {
extern "C" { // cangjie [PAGDecoder] ffi
long long cj_PAGDecoder_makeFrom(const int64_t ptr, float maxFrameRate, float scale)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_makeFrom", "Pointer is null");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (instance == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "PAGDecoder",
                     "[cj_PAGDecoder_makeFrom]- CJPAGLayerHandle is nullptr!");
        return 0;
    }
    std::shared_ptr<pag::PAGComposition> composition = std::static_pointer_cast<pag::PAGComposition>(instance->get());
    auto decoder = pag::PAGDecoder::MakeFrom(std::move(composition), maxFrameRate, scale);
    if (decoder == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "PAGDecoder",
                     "[cj_PAGDecoder_makeFrom]-PAGDecoder::MakeFrom() Failed to create a PAGDecoder!");
        return 0;
    }
    CJPAGDecoder *ptrCJPAGDecoder = new CJPAGDecoder(decoder);
    return (int64_t)ptrCJPAGDecoder;
}

long long cj_PAGDecoder_width(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_width", "Pointer is null");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    long long width = instance->get()->width();
    return width;
}

long long cj_PAGDecoder_height(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_height", "Pointer is null");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    long long height = instance->get()->height();
    return height;
}

long long cj_PAGDecoder_numFrames(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_numFrames", "Pointer is null");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    long long numFrames = instance->get()->numFrames();
    return numFrames;
}

float cj_PAGDecoder_frameRate(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_frameRate", "Pointer is null");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    float frameRate = instance->get()->frameRate();
    return frameRate;
}

bool cj_PAGDecoder_checkFrameChanged(const int64_t ptr, int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_checkFrameChanged", "Pointer is null");
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    bool flag = instance->get()->checkFrameChanged(index);
    return flag;
}

CJPixelMap cj_PAGDecoder_readFrame(const int64_t ptr, int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_readFrame", "Pointer is null");
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    if (!instance || !instance->get()) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    auto decoder = instance->get();
    tgfx::ImageInfo imageInfo = tgfx::ImageInfo::Make(decoder->width(), decoder->height(), tgfx::ColorType::BGRA_8888,
                                                      tgfx::AlphaType::Premultiplied);
    auto pixels = ByteData::Make(imageInfo.byteSize());
    if (pixels == nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    if (!decoder->readFrame(index, pixels->data(), imageInfo.rowBytes(), ColorType::BGRA_8888,
                            AlphaType::Premultiplied)) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    int32_t width = imageInfo.width();
    int32_t height = imageInfo.height();
    uint8_t pixelFormat = 3; // PIXEL_FORMAT_BGRA_8888;
    uint8_t alphaType = 2;   // OHOS_PIXEL_MAP_ALPHA_TYPE_PREMUL;
    bool editable = true;

    uint8_t *bytes = pixels->data();
    // Return the byte size of the pixel.
    int size = pixels->length();

    uint8_t *buf = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        buf[i] = bytes[i];
    }
    return CJPixelMap{size, buf, alphaType, editable, pixelFormat, height, width};
}

void cj_PAGDecoder_nativeRelease(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_nativeRelease", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    if (instance != nullptr) {
        instance->clear();
        delete instance;
    }
}

void cj_PAGDecoder_nativeFinalize(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_nativeFinalize", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGDecoder *instance = reinterpret_cast<CJPAGDecoder *>(ptrInt);
    if (instance != nullptr) {
        delete instance;
    }
}
}
} // namespace pag
