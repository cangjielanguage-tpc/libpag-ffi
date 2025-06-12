/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#pragma once

#include "cj_pag_layer_handle.h"
#include "cj_pag_surface.h"
#include <hilog/log.h>

namespace pag {
class CJPAGPlayer {
public:
    explicit CJPAGPlayer(std::shared_ptr<pag::PAGPlayer> pagPlayer) : pagPlayer(pagPlayer) {}

    virtual ~CJPAGPlayer();

    std::shared_ptr<pag::PAGPlayer> get() {
        std::lock_guard lock_guard(locker);
        return pagPlayer;
    }

    void clear() {
        std::lock_guard lock_guard(locker);
        pagPlayer = nullptr;
    }

private:
    std::shared_ptr<pag::PAGPlayer> pagPlayer;
    std::mutex locker;
};

extern "C" {
int64_t cj_PAGPlayer_createPAGPlayer();
void cj_PAGPlayer_setComposition(const int64_t ptrPlayer, const int64_t ptrComposition);
void cj_PAGPlayer_setSurface(const int64_t ptrPlayer, const int64_t ptrSurface);
bool cj_PAGPlayer_videoEnabled(const int64_t ptr);
void cj_PAGPlayer_setVideoEnabled(const int64_t ptr, bool value);
bool cj_PAGPlayer_cacheEnabled(const int64_t ptr);
void cj_PAGPlayer_setCacheEnabled(const int64_t ptr, bool value);
bool cj_PAGPlayer_useDiskCache(const int64_t ptr);
void cj_PAGPlayer_setUseDiskCache(const int64_t ptr, bool value);
float cj_PAGPlayer_cacheScale(const int64_t ptr);
void cj_PAGPlayer_setCacheScale(const int64_t ptr, float value);
float cj_PAGPlayer_maxFrameRate(const int64_t ptr);
void cj_PAGPlayer_setMaxFrameRate(const int64_t ptr, float value);
int32_t cj_PAGPlayer_scaleMode(const int64_t ptr);
void cj_PAGPlayer_setScaleMode(const int64_t ptr, int32_t value);
void cj_PAGPlayer_matrix(const int64_t ptr, float values[9]);
void cj_PAGPlayer_setMatrix(const int64_t ptr, float values[9]);
double cj_PAGPlayer_duration(const int64_t ptr);
double cj_PAGPlayer_getProgress(const int64_t ptr);
void cj_PAGPlayer_setProgress(const int64_t ptr, double value);
int64_t cj_PAGPlayer_currentFrame(const int64_t ptr);
void cj_PAGPlayer_prepare(const int64_t ptr);
bool cj_PAGPlayer_flush(const int64_t ptr);
void cj_PAGPlayer_getBounds(const int64_t ptrCJPAGPlayer, const int64_t ptrCJPAGLayerHandle, float values[4]);
CJInt64Array cj_PAGPlayer_getLayersUnderPoint(const int64_t ptr, float surfaceX, float surfaceY);
bool cj_PAGPlayer_hitTestPoint(const int64_t ptrCJPAGPlayer, const int64_t ptrCJPAGLayerHandle, float surfaceX,
                               float surfaceY, bool pixelHitTest);
void cj_PAGPlayer_release(const int64_t ptr);
}
}