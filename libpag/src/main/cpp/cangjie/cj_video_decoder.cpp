/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_video_decoder.h"

extern "C" {
void cj_VideoDecoder_registerSoftwareDecoderFactory(const int64_t factory) {
    pag::PAGVideoDecoder::RegisterSoftwareDecoderFactory(reinterpret_cast<pag::SoftwareDecoderFactory *>(factory));
}

void cj_VideoDecoder_setMaxHardwareDecoderCount(const int32_t maxCount) {
    pag::PAGVideoDecoder::SetMaxHardwareDecoderCount(maxCount);
}
}
