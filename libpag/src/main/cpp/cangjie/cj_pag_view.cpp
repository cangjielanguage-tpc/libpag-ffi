/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_view.h"

namespace pag {
static std::unordered_map<std::string, std::shared_ptr<CJPAGView>> ViewMap = {};

void CJPAGView::onAnimationStart(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Start), g_jView);
    }
}

void CJPAGView::onAnimationCancel(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Cancel), g_jView);
    }
}

void CJPAGView::onAnimationEnd(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::End), g_jView);
    }
}

void CJPAGView::onAnimationRepeat(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Repeat), g_jView);
    }
}

void CJPAGView::onAnimationUpdate(PAGAnimator *animator)
{
    std::lock_guard lock_guard(locker);
    if (playingProgressCallback) {
        playingProgressCallback(g_jView);
    }
    if (player) {
        player->setProgress(animator->progress());
        player->flush();
    }
}

void CJPAGView::release()
{
    std::lock_guard lock_guard(locker);
    if (playingProgressCallback) {
        playingProgressCallback = nullptr;
    }
    if (playingStateCallback) {
        playingStateCallback = nullptr;
    }
    if (animator) {
        animator = nullptr;
    }
    if (player) {
        player->setSurface(nullptr);
        player = nullptr;
    }
}

CJPAGView::~CJPAGView() { release(); }

extern "C" {
int64_t cj_PAGViewController_createJPAGView()
{
    std::string id = "PAGView" + std::to_string(tgfx::UniqueID::Next());
    auto cView = std::make_shared<CJPAGView>(id);
    cView->animator = PAGAnimator::MakeFrom(cView);
    ViewMap.emplace(id, cView);
    return reinterpret_cast<int64_t>(cView.get());
}

void cj_PAGViewController_destroyJPAGView(const char *id)
{
    if (id == nullptr || id[0] == '\0') {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_destroyJPAGView", "id is null or empty.");
        return;
    }
    ViewMap.erase(id);
}

bool cj_PAGViewController_flush(const int64_t jView)
{
    if (jView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_flush", "Pointer is null");
        return false;
    }
    bool flushResult = false;
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_flush", "view is null");
        return flushResult;
    }
    auto player = view->getPlayer();
    if (player) {
        flushResult = player->flush();
    }
    return flushResult;
}

void cj_PAGViewController_update(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_update", "view is null");
        return;
    }
    auto animator = view->getAnimator();
    if (animator) {
        animator->update();
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_update", "animator is null");
    }
}

void cj_PAGViewController_setProgress(const int64_t jView, double value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setProgress", "view is null");
        return;
    }
    auto animator = view->getAnimator();
    auto player = view->getPlayer();
    if (player && animator) {
        player->setProgress(value);
        animator->setProgress(value);
        animator->update();
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setProgress", "player or animator is null");
    }
}

double cj_PAGViewController_getProgress(const int64_t jView)
{
    if (jView == 0) {
        return 0.0;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getProgress", "view is null");
        return 0.0;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getProgress", "animator is null");
        return 0.0;
    }
    return animator->progress();
}

void cj_PAGViewController_setComposition(const int64_t jView, const int64_t ptrComposition, bool isNull)
{
    if (jView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setComposition", "Pointer is null");
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    intptr_t ptrCompositionInt = static_cast<intptr_t>(ptrComposition);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrCompositionInt);
    auto layer = instance->get();
    auto player = view->getPlayer();
    auto animator = view->getAnimator();
    if (!player || !animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setComposition",
                     "player or animator is null");
        return;
    }
    if (isNull) {
        player->setComposition(nullptr);
        animator->setDuration(0);
        return;
    }
    if (layer && layer->layerType() == LayerType::PreCompose) {
        auto composition = std::static_pointer_cast<PAGComposition>(layer);
        player->setComposition(composition);
        animator->setProgress(player->getProgress());
        animator->setDuration(layer->duration());
    }
}

void cj_PAGViewController_setRepeatCount(const int64_t jView, int32_t repeatCount)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setRepeatCount", "view is null");
        return;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setRepeatCount", "animator is null");
        return;
    }
    animator->setRepeatCount(repeatCount);
}

int32_t cj_PAGViewController_repeatCount(const int64_t jView)
{
    if (jView == 0) {
        return 0;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_repeatCount", "view is null");
        return 0;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_repeatCount", "animator is null");
        return 0;
    }
    return animator->repeatCount();
}

void cj_PAGViewController_play(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_play", "view is null");
        return;
    }
    auto player = view->getPlayer();
    auto animator = view->getAnimator();
    if (!player || !animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_play", "player or animator is null");
        return;
    }
    player->prepare();
    animator->start();
}

void cj_PAGViewController_pause(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_pause", "view is null");
        return;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_pause", "animator is null");
        return;
    }
    animator->cancel();
}

bool cj_PAGViewController_isPlaying(const int64_t jView)
{
    if (jView == 0) {
        return false;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_isPlaying", "view is null");
        return false;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_isPlaying", "animator is null");
        return false;
    }
    return animator->isRunning();
}

CJBytesArray cj_PAGViewController_uniqueID(const int64_t jView)
{
    if (jView == 0) {
        return {0, nullptr};
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_uniqueID", "view is null");
        return {0, nullptr};
    }
    std::string str = view->id;
    CJBytesArray result = stringToCJBytesArray(str);
    return result;
}

void cj_PAGViewController_setSync(const int64_t jView, bool isSync)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setSync", "view is null");
        return;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setSync", "animator is null");
        return;
    }
    animator->setSync(isSync);
}

bool cj_PAGViewController_isSync(const int64_t jView)
{
    if (jView == 0) {
        return false;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_isSync", "view is null");
        return false;
    }
    auto animator = view->getAnimator();
    if (!animator) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_isSync", "animator is null");
        return false;
    }
    return animator->isSync();
}

void cj_PAGViewController_setVideoEnabled(const int64_t jView, bool value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setVideoEnabled", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setVideoEnabled", "player is null");
        return;
    }
    player->setVideoEnabled(value);
}

bool cj_PAGViewController_videoEnabled(const int64_t jView)
{
    if (jView == 0) {
        return false;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_videoEnabled", "view is null");
        return false;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_videoEnabled", "player is null");
        return false;
    }
    return player->videoEnabled();
}

void cj_PAGViewController_setCacheEnabled(const int64_t jView, bool value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setCacheEnabled", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setCacheEnabled", "player is null");
        return;
    }
    player->setCacheEnabled(value);
}

bool cj_PAGViewController_cacheEnabled(const int64_t jView)
{
    if (jView == 0) {
        return false;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_cacheEnabled", "view is null");
        return false;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_cacheEnabled", "player is null");
        return false;
    }
    return player->cacheEnabled();
}

void cj_PAGViewController_setCacheScale(const int64_t jView, float value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setCacheScale", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setCacheScale", "player is null");
        return;
    }
    player->setCacheScale(value);
}

float cj_PAGViewController_cacheScale(const int64_t jView)
{
    if (jView == 0) {
        return 1.0;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_cacheScale", "view is null");
        return 1.0;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_cacheScale", "player is null");
        return 1.0;
    }
    return player->cacheScale();
}

void cj_PAGViewController_setMaxFrameRate(const int64_t jView, float value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setMaxFrameRate", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setMaxFrameRate", "player is null");
        return;
    }
    player->setMaxFrameRate(value);
}

float cj_PAGViewController_maxFrameRate(const int64_t jView)
{
    constexpr float DEFAULT_MAX_FRAME_RATE = 60.0f;
    if (jView == 0) {
        return DEFAULT_MAX_FRAME_RATE;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_maxFrameRate", "view is null");
        return DEFAULT_MAX_FRAME_RATE;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_maxFrameRate", "player is null");
        return DEFAULT_MAX_FRAME_RATE;
    }
    return player->maxFrameRate();
}

void cj_PAGViewController_setScaleMode(const int64_t jView, int32_t value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setScaleMode", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setScaleMode", "player is null");
        return;
    }
    player->setScaleMode(value);
}

int32_t cj_PAGViewController_scaleMode(const int64_t jView)
{
    int scaleMode = PAGScaleMode::LetterBox;
    if (jView == 0) {
        return scaleMode;
    }

    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_scaleMode", "view is null");
        return scaleMode;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_scaleMode", "player is null");
        return scaleMode;
    }
    scaleMode = player->scaleMode();
    return scaleMode;
}

void cj_PAGViewController_setMatrix(const int64_t jView, float values[9])
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setMatrix", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setMatrix", "player is null");
        return;
    }
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
    player->setMatrix(matrix);
}

void cj_PAGViewController_matrix(const int64_t jView, float values[9])
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_matrix", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (player) {
        Matrix matrix = player->matrix();
        matrix.get9(values);
    } else {
        Matrix matrix = {};
        matrix.setIdentity();
        matrix.get9(values);
    }
}

int32_t cj_PAGViewController_currentFrame(const int64_t jView)
{
    if (jView == 0) {
        return 0;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_currentFrame", "view is null");
        return 0;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_currentFrame", "player is null");
        return 0;
    }
    return player->currentFrame();
}

CJInt64Array cj_PAGViewController_getLayersUnderPoint(const int64_t jView, float x, float y)
{
    if (jView == 0) {
        return {0, nullptr};
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getLayersUnderPoint", "view is null");
        return {0, nullptr};
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getLayersUnderPoint", "player is null");
        return {0, nullptr};
    }
    std::vector<std::shared_ptr<PAGLayer>> pagLayers = player->getLayersUnderPoint(x, y);
    if (pagLayers.empty()) {
        return {0, nullptr};
    }
    long long size = pagLayers.size();
    int64_t *arr = new int64_t[size];
    for (size_t i = 0; i < pagLayers.size(); i++) {
        std::shared_ptr<PAGLayer> pagLayer = pagLayers[i];
        if (!pagLayer) {
            delete[] arr;
            return {0, nullptr};
        }
        CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagLayer);
        arr[i] = (int64_t)cjlayer;
    }
    return CJInt64Array{size, arr};
}

void cj_PAGViewController_getBounds(const int64_t jView, const int64_t ptrCJPAGLayerHandle, float values[4])
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getBounds", "view is null");
        return;
    }
    auto player = view->getPlayer();
    intptr_t ptrCJPAGLayerHandleInt = static_cast<intptr_t>(ptrCJPAGLayerHandle);
    CJPAGLayerHandle *layerHandle = reinterpret_cast<CJPAGLayerHandle *>(ptrCJPAGLayerHandleInt);
    if (!player || !layerHandle || !layerHandle->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_getBounds", "layerHandle or player is null");
        return;
    }
    std::shared_ptr<pag::PAGLayer> layer = layerHandle->get();
    layer->setVisible(false);
    Rect rect = player->getBounds(layer);
    constexpr int INDEX_LEFT = 0;
    constexpr int INDEX_TOP = 1;
    constexpr int INDEX_RIGHT = 2;
    constexpr int INDEX_BOTTOM = 3;
    values[INDEX_LEFT] = rect.left;
    values[INDEX_TOP] = rect.top;
    values[INDEX_RIGHT] = rect.right;
    values[INDEX_BOTTOM] = rect.bottom;
}

void cj_PAGViewController_freeCache(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_freeCache", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_freeCache", "player is null");
        return;
    }
    auto surface = player->getSurface();
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_freeCache", "surface is null");
        return;
    }
    surface->freeCache();
}

bool cj_PAGViewController_useDiskCache(const int64_t jView)
{
    if (jView == 0) {
        return false;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_useDiskCache", "view is null");
        return false;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_useDiskCache", "player is null");
        return false;
    }
    return player->useDiskCache();
}

void cj_PAGViewController_setUseDiskCache(const int64_t jView, bool value)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setUseDiskCache", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setUseDiskCache", "player is null");
        return;
    }
    player->setUseDiskCache(value);
}

int64_t cj_PAGViewController_duration(const int64_t jView)
{
    if (jView == 0) {
        return 0;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setUseDiskCache", "view is null");
        return 0;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_setUseDiskCache", "player is null");
        return 0;
    }
    return player->duration();
}

void cj_PAGViewController_SetSurfaceId(const int64_t jView, int64_t surfaceId)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_SetSurfaceId", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_SetSurfaceId", "player is null");
        return;
    }
    OHNativeWindow *window = nullptr;
    OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &window);
    auto drawable = pag::GPUDrawable::FromWindow(window);
    player->setSurface(pag::PAGSurface::MakeFrom(drawable));
}

void cj_PAGViewController_ChangeSurface(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_ChangeSurface", "view is null");
        return;
    }
    auto player = view->getPlayer();
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_ChangeSurface", "player is null");
        return;
    }
    auto surface = player->getSurface();
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_ChangeSurface", "surface is null");
        return;
    }
    surface->updateSize();
}

void cj_PAGViewController_release(const int64_t jView)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_release", "view is null");
        return;
    }
    view->release();
}

void cj_PAGViewController_onAnimatorStateChange(const int64_t jView, CJPAGView::stateCallback callback)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_onAnimatorStateChange", "view is null");
        return;
    }
    view->g_jView = jView;
    view->playingStateCallback = callback;
}

void cj_PAGViewController_onAnimatorProgress(const int64_t jView, CJPAGView::progressCallback callback)
{
    if (jView == 0) {
        return;
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGViewController_onAnimatorProgress", "view is null");
        return;
    }
    view->g_jView = jView;
    view->playingProgressCallback = callback;
}

CJPixelMap cj_PAGViewController_makeSnapshot(const int64_t jView)
{
    if (jView == 0) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    intptr_t viewPtrInt = static_cast<intptr_t>(jView);
    CJPAGView *view = reinterpret_cast<CJPAGView *>(viewPtrInt);
    auto player = view->getPlayer();
    if (player == nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    auto surface = player->getSurface();
    return MakeSnapshot(surface);
}
}
} // namespace pag
