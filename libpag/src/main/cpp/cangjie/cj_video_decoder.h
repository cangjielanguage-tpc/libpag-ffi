/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_VIDEO_DECODER_H
#define LIBPAG4CJ_CJ_VIDEO_DECODER_H
#include <pag/pag.h>

extern "C" {
void cj_VideoDecoder_registerSoftwareDecoderFactory(const int64_t factory);
void cj_VideoDecoder_setMaxHardwareDecoderCount(const int32_t maxCount);
}
#endif // LIBPAG4CJ_CJ_VIDEO_DECODER_H
