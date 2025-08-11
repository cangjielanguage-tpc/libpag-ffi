/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_PAG_DECODER_H
#define LIBPAG_CJ_CJ_PAG_DECODER_H

#include "cj_pag_layer_handle.h"
#include <pag/pag.h>

class CJPAGDecoder {
public:
    explicit CJPAGDecoder(std::shared_ptr<pag::PAGDecoder> pagDecoder) : pagDecoder(pagDecoder) {}

    std::shared_ptr<pag::PAGDecoder> get()
    { 
        std::lock_guard<std::mutex> autoLock(locker);
        return pagDecoder; 
    }

    void clear()
    { 
        std::lock_guard<std::mutex> autoLock(locker);
        pagDecoder = nullptr;
    }

private:
    std::shared_ptr<pag::PAGDecoder> pagDecoder;
    std::mutex locker;
};

extern "C" { // cangjie [PAGDecoder] ffi
long long cj_PAGDecoder_makeFrom(const int64_t ptr, float maxFrameRate, float scale);
long long cj_PAGDecoder_width(const int64_t ptr);
long long cj_PAGDecoder_height(const int64_t ptr);
long long cj_PAGDecoder_numFrames(const int64_t ptr);
float cj_PAGDecoder_frameRate(const int64_t ptr);
bool cj_PAGDecoder_checkFrameChanged(const int64_t ptr, int64_t index);
void cj_PAGDecoder_nativeRelease(const int64_t ptr);
void cj_PAGDecoder_nativeFinalize(const int64_t ptr);
CJPixelMap cj_PAGDecoder_readFrame(const int64_t ptr, int64_t index);
}

#endif // LIBPAG_CJ_CJ_PAG_DECODER_H
