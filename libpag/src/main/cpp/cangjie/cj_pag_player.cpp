/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_player.h"

namespace pag {

CJPAGPlayer::~CJPAGPlayer() { clear(); }

extern "C" {
int64_t cj_PAGPlayer_createPAGPlayer() {
    std::shared_ptr<PAGPlayer> player = std::make_shared<PAGPlayer>();
    CJPAGPlayer *handler = new CJPAGPlayer(player);
    return (int64_t)handler;
}

void cj_PAGPlayer_setComposition(const int64_t ptrPlayer, const int64_t ptrComposition) {
    if (ptrPlayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setComposition", "Invalid pointer");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptrPlayer;
    CJPAGLayerHandle *instance = (CJPAGLayerHandle *)ptrComposition;
    if (!instance) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setComposition", "Instance is null.");
        return;
    }
    auto composition = instance->get();
    if (!composition) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setComposition", "Composition is null.");
        return;
    }
    if (composition->layerType() != LayerType::PreCompose) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setComposition",
                     "Invalid composition type: not PreCompose.");
        return;
    }
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setComposition", "player or player->get() is null.");
        return;
    }
    player->get()->setComposition(std::static_pointer_cast<PAGComposition>(composition));
}

void cj_PAGPlayer_setSurface(const int64_t ptrPlayer, const int64_t ptrSurface) {
    if (ptrPlayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setSurface", "Invalid pointer");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptrPlayer;
    if (ptrSurface == 0) {
        player->get()->setSurface(nullptr);
        return;
    }
    CJPAGSurface *surface = (CJPAGSurface *)ptrSurface;
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setSurface", "Surface pointer is invalid.");
        return;
    }
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setSurface", "player or player->get() is null.");
        return;
    }
    player->get()->setSurface(surface->get());
}

bool cj_PAGPlayer_videoEnabled(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_videoEnabled", "ptr is null.");
        return false;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_videoEnabled", "player or player->get() is null.");
        return false;
    }
    return player->get()->videoEnabled();
}

void cj_PAGPlayer_setVideoEnabled(const int64_t ptr, bool value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setVideoEnabled", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setVideoEnabled",
                     "player or player->get() is null.");
        return;
    }
    player->get()->setVideoEnabled(value);
}

bool cj_PAGPlayer_cacheEnabled(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_cacheEnabled", "ptr is null.");
        return false;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_cacheEnabled", "player or player->get() is null.");
        return false;
    }
    return player->get()->cacheEnabled();
}

void cj_PAGPlayer_setCacheEnabled(const int64_t ptr, bool value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setCacheEnabled", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setCacheEnabled",
                     "player or player->get() is null.");
        return;
    }
    player->get()->setCacheEnabled(value);
}

bool cj_PAGPlayer_useDiskCache(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_useDiskCache", "ptr is null.");
        return false;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_useDiskCache", "player or player->get() is null.");
        return false;
    }
    return player->get()->useDiskCache();
}

void cj_PAGPlayer_setUseDiskCache(const int64_t ptr, bool value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setUseDiskCache", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setUseDiskCache",
                     "player or player->get() is null.");
        return;
    }
    player->get()->setUseDiskCache(value);
}

float cj_PAGPlayer_cacheScale(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_cacheScale", "ptr is null.");
        return 0.0;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_cacheScale", "player or player->get() is null.");
        return 0.0;
    }
    return player->get()->cacheScale();
}

void cj_PAGPlayer_setCacheScale(const int64_t ptr, float value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setCacheScale", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setCacheScale", "player or player->get() is null.");
        return;
    }

    player->get()->setCacheScale(value);
}

float cj_PAGPlayer_maxFrameRate(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_maxFrameRate", "ptr is null.");
        return 0.0;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_maxFrameRate", "player or player->get() is null.");
        return 0.0;
    }
    return player->get()->maxFrameRate();
}

void cj_PAGPlayer_setMaxFrameRate(const int64_t ptr, float value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setMaxFrameRate", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setMaxFrameRate",
                     "player or player->get() is null.");
        return;
    }
    player->get()->setMaxFrameRate(value);
}

int32_t cj_PAGPlayer_scaleMode(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_scaleMode", "ptr is null.");
        return -1;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_scaleMode", "player or player->get() is null.");
        return -1;
    }
    return player->get()->scaleMode();
}

void cj_PAGPlayer_setScaleMode(const int64_t ptr, int32_t value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setScaleMode", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setScaleMode", "player or player->get() is null.");
        return;
    }
    player->get()->setScaleMode(value);
}

void cj_PAGPlayer_matrix(const int64_t ptr, float values[9]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_matrix", "Pointer is null");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (player && player->get()) {
        Matrix matrix = player->get()->matrix();
        matrix.get9(values);
    } else {
        Matrix matrix = {};
        matrix.setIdentity();
        matrix.get9(values);
    }
}

void cj_PAGPlayer_setMatrix(const int64_t ptr, float values[9]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setMatrix", "Pointer is null");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setMatrix", "player or player->get() is null.");
        return;
    }
    if (player && player->get()) {
        Matrix matrix = {};
        matrix.setAll(values[0], values[1], values[2], values[3], values[4], values[5], 0, 0, 1);
        player->get()->setMatrix(matrix);
    }
}

double cj_PAGPlayer_duration(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_duration", "ptr is null.");
        return 0.0;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_duration", "player or player->get() is null.");
        return 0.0;
    }
    return player->get()->duration();
}

double cj_PAGPlayer_getProgress(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getProgress", "ptr is null.");
        return 0.0;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getProgress", "player or player->get() is null.");
        return 0.0;
    }
    return player->get()->getProgress();
}

void cj_PAGPlayer_setProgress(const int64_t ptr, double value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setProgress", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_setProgress", "player or player->get() is null.");
        return;
    }
    player->get()->setProgress(value);
}

int64_t cj_PAGPlayer_currentFrame(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_currentFrame", "ptr is null.");
        return -1;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_currentFrame", "player or player->get() is null.");
        return -1;
    }
    return player->get()->currentFrame();
}

void cj_PAGPlayer_prepare(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_prepare", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_prepare", "player or player->get() is null.");
        return;
    }
    player->get()->prepare();
}

bool cj_PAGPlayer_flush(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_flush", "ptr is null.");
        return false;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_flush", "player or player->get() is null.");
        return false;
    }
    return player->get()->flush();
}

void cj_PAGPlayer_getBounds(const int64_t ptrCJPAGPlayer, const int64_t ptrCJPAGLayerHandle, float values[4]) {
    if (ptrCJPAGPlayer == 0 || ptrCJPAGLayerHandle == 0 || values == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getBounds", "Null input detected.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptrCJPAGPlayer;
    CJPAGLayerHandle *layerHandle = (CJPAGLayerHandle *)ptrCJPAGLayerHandle;
    if (!player || !player->get() || !layerHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getBounds", "Invalid player or layer handle.");
        return;
    }
    std::shared_ptr<pag::PAGLayer> layer = layerHandle->get();
    if (!layer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getBounds", "Layer is null.");
        return;
    }
    layer->setVisible(false);
    Rect rect = player->get()->getBounds(layer);
    values[0] = rect.left;
    values[1] = rect.top;
    values[2] = rect.right;
    values[3] = rect.bottom;
}

CJInt64Array cj_PAGPlayer_getLayersUnderPoint(const int64_t ptr, float surfaceX, float surfaceY) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getLayersUnderPoint", "ptr is null.");
        return {};
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player || !player->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_getLayersUnderPoint",
                     "player or player->get() is null.");
        return {};
    }
    std::vector<std::shared_ptr<PAGLayer>> pagLayers = player->get()->getLayersUnderPoint(surfaceX, surfaceY);
    if (pagLayers.empty()) {
        return {};
    }
    long long size = pagLayers.size();
    int64_t *arr = new int64_t[size];
    for (size_t i = 0; i < pagLayers.size(); i++) {
        std::shared_ptr<PAGLayer> pagLayer = pagLayers[i];
        if (!pagLayer) {
            delete[] arr;
            return {};
        }
        CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagLayer);
        arr[i] = (int64_t)cjlayer;
    }
    return CJInt64Array{size, arr};
}

bool cj_PAGPlayer_hitTestPoint(const int64_t ptrCJPAGPlayer, const int64_t ptrCJPAGLayerHandle, float surfaceX,
                               float surfaceY, bool pixelHitTest) {
    if (ptrCJPAGPlayer == 0 || ptrCJPAGLayerHandle == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_hitTestPoint", "Null input detected.");
        return false;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptrCJPAGPlayer;
    CJPAGLayerHandle *layerHandle = (CJPAGLayerHandle *)ptrCJPAGLayerHandle;
    if (!player || !player->get() || !layerHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_hitTestPoint", "Invalid player or layer handle.");
        return false;
    }
    std::shared_ptr<pag::PAGLayer> layer = layerHandle->get();
    if (!layer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_hitTestPoint", "Layer is null.");
        return false;
    }
    bool value = player->get()->hitTestPoint(layer, surfaceX, surfaceY, pixelHitTest);
    return value;
}

void cj_PAGPlayer_release(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_release", "ptr is null.");
        return;
    }
    CJPAGPlayer *player = (CJPAGPlayer *)ptr;
    if (!player) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGPlayer_release", "Invalid player");
        return;
    }
    delete player;
}
}
}