/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_PAG_DECODER_H
#define LIBPAG_CJ_CJ_PAG_DECODER_H

#include <pag/pag.h>
#include "cj_pag_layer_handle.h"

class CJPAGDecoder {
    public:
        explicit CJPAGDecoder(std::shared_ptr<pag::PAGDecoder> pagDecoder) : pagDecoder(pagDecoder) {
        }

        std::shared_ptr<pag::PAGDecoder> get() {
            return pagDecoder;
        }

        void clear() {
            pagDecoder = nullptr;
        }

    private:
        std::shared_ptr<pag::PAGDecoder> pagDecoder;
};

extern "C" {// cangjie [PAGDecoder] ffi
long long cj_PAGDecoder_makeFrom(const int64_t ptr, float maxFrameRate, float scale);
long long cj_PAGDecoder_width(const int64_t ptr);
long long cj_PAGDecoder_height(const int64_t ptr);
long long cj_PAGDecoder_numFrames(const int64_t ptr);
float cj_PAGDecoder_frameRate(const int64_t ptr);
bool cj_PAGDecoder_checkFrameChanged(const int64_t ptr, const int32_t index);
bool cj_PAGDecoder_readFrame(const int64_t ptr, const int32_t index, uint8_t* bytes, const int64_t rowBytes, const uint8_t colorType, const uint8_t alphaType);
void cj_PAGDecoder_nativeRelease(const int64_t ptr);
void cj_PAGDecoder_nativeFinalize(const int64_t ptr);
}

#endif //LIBPAG_CJ_CJ_PAG_DECODER_H
