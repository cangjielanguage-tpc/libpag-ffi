/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_decoder.h"

namespace pag {
extern "C" { // cangjie [PAGDecoder] ffi

long long cj_PAGDecoder_makeFrom(const int64_t ptr, float maxFrameRate, float scale) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_makeFrom", "Pointer is null");
        return 0;
    }
    CJPAGLayerHandle *instance = (CJPAGLayerHandle *)ptr;
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
    CJPAGDecoder cjPAGDecoder = CJPAGDecoder(decoder);
    CJPAGDecoder *ptrCJPAGDecoder = &cjPAGDecoder;
    return (int64_t)ptrCJPAGDecoder;
}

long long cj_PAGDecoder_width(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_width", "Pointer is null");
        return 0;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    long long width = instance->get()->width();
    return width;
}

long long cj_PAGDecoder_height(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_height", "Pointer is null");
        return 0;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    long long height = instance->get()->height();
    return height;
}

long long cj_PAGDecoder_numFrames(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_numFrames", "Pointer is null");
        return 0;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    long long numFrames = instance->get()->numFrames();
    return numFrames;
}

float cj_PAGDecoder_frameRate(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_frameRate", "Pointer is null");
        return 0;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    float frameRate = instance->get()->frameRate();
    return frameRate;
}

bool cj_PAGDecoder_checkFrameChanged(const int64_t ptr, const int32_t index) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_checkFrameChanged", "Pointer is null");
        return false;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    bool flag = instance->get()->checkFrameChanged(index);
    return flag;
}

bool cj_PAGDecoder_readFrame(const int64_t ptr, const int32_t index, uint8_t *bytes, const int64_t rowBytes,
                             const uint8_t colorType, const uint8_t alphaType) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_readFrame", "Pointer is null");
        return false;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    pag::ColorType ct = pag::getColorType(colorType);
    pag::AlphaType at = pag::getAlphaType(alphaType);
    bool flag = instance->get()->readFrame(index, bytes, rowBytes, ct, at);
    return flag;
}

void cj_PAGDecoder_nativeRelease(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_nativeRelease", "Pointer is null");
        return;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    if (instance != nullptr) {
        instance->clear();
    }
}

void cj_PAGDecoder_nativeFinalize(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGDecoder_nativeFinalize", "Pointer is null");
        return;
    }
    CJPAGDecoder *instance = (CJPAGDecoder *)ptr;
    if (instance != nullptr) {
        delete instance;
    }
}
}
} // namespace pag
