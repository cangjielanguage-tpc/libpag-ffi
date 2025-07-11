/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#pragma once

#include "../../../third_party/tgfx/src/utils/UniqueID.h"
#include "../../external/include/rendering/PAGAnimator.h"
#include "../../external/platform/GPUDrawable.h"
#include "cj_helper.h"
#include "cj_pag_layer_handle.h"
#include <hilog/log.h>

namespace pag {
class CJPAGView : public PAGAnimator::Listener {
public:
    explicit CJPAGView(const std::string &id) : id(std::move(id)), player(new PAGPlayer()) {}

    virtual ~CJPAGView();

    void onAnimationStart(PAGAnimator *) override;

    void onAnimationCancel(PAGAnimator *) override;

    void onAnimationEnd(PAGAnimator *) override;

    void onAnimationRepeat(PAGAnimator *) override;

    void onAnimationUpdate(PAGAnimator *animator) override;

    void release();

    std::shared_ptr<PAGPlayer> getPlayer() {
        std::lock_guard lock_guard(locker);
        return player;
    }

    std::shared_ptr<PAGAnimator> getAnimator() {
        std::lock_guard lock_guard(locker);
        return animator;
    }

    std::string id;
    int64_t g_jView = 0;
    std::shared_ptr<PAGAnimator> animator = nullptr;
    typedef void (*stateCallback)(uint8_t, int64_t);
    stateCallback playingStateCallback = nullptr;
    typedef void (*progressCallback)(int64_t);
    progressCallback playingProgressCallback = nullptr;

private:
    std::shared_ptr<PAGPlayer> player;
    std::mutex locker;
};

extern "C" {
int64_t cj_PAGViewController_createJPAGView();
void cj_PAGViewController_destroyJPAGView(const char *id);
void cj_PAGViewController_setComposition(const int64_t jView, const int64_t ptrComposition, bool isNull);
void cj_PAGViewController_play(const int64_t jView);
CJBytesArray cj_PAGViewController_uniqueID(const int64_t jView);
void cj_PAGViewController_update(const int64_t jView);
void cj_PAGViewController_pause(const int64_t jView);
bool cj_PAGViewController_isPlaying(const int64_t jView);
bool cj_PAGViewController_isSync(const int64_t jView);
void cj_PAGViewController_setSync(const int64_t jView, bool isSync);
int32_t cj_PAGViewController_repeatCount(const int64_t jView);
void cj_PAGViewController_setRepeatCount(const int64_t jView, int32_t repeatCount);
bool cj_PAGViewController_videoEnabled(const int64_t jView);
void cj_PAGViewController_setVideoEnabled(const int64_t jView, bool value);
bool cj_PAGViewController_cacheEnabled(const int64_t jView);
void cj_PAGViewController_setCacheEnabled(const int64_t jView, bool value);
bool cj_PAGViewController_useDiskCache(const int64_t jView);
void cj_PAGViewController_setUseDiskCache(const int64_t jView, bool value);
float cj_PAGViewController_cacheScale(const int64_t jView);
void cj_PAGViewController_setCacheScale(const int64_t jView, float value);
float cj_PAGViewController_maxFrameRate(const int64_t jView);
void cj_PAGViewController_setMaxFrameRate(const int64_t jView, float value);
int32_t cj_PAGViewController_scaleMode(const int64_t jView);
void cj_PAGViewController_setScaleMode(const int64_t jView, int32_t value);
void cj_PAGViewController_matrix(const int64_t jView, float values[9]);
void cj_PAGViewController_setMatrix(const int64_t jView, float values[9]);
int64_t cj_PAGViewController_duration(const int64_t jView);
double cj_PAGViewController_getProgress(const int64_t jView);
void cj_PAGViewController_setProgress(const int64_t jView, double value);
int32_t cj_PAGViewController_currentFrame(const int64_t jView);
bool cj_PAGViewController_flush(const int64_t jView);
void cj_PAGViewController_freeCache(const int64_t jView);
void cj_PAGViewController_SetSurfaceId(const int64_t jView, int64_t surfaceId);
void cj_PAGViewController_ChangeSurface(const int64_t jView);
CJInt64Array cj_PAGViewController_getLayersUnderPoint(const int64_t jView, float x, float y);
void cj_PAGViewController_getBounds(const int64_t ptrCJPAGPlayer, const int64_t ptrCJPAGLayerHandle, float values[4]);
CJPixelMap cj_PAGViewController_makeSnapshot(const int64_t ptr);
void cj_PAGViewController_release(const int64_t jView);
}
}