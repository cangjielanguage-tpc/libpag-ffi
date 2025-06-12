/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_surface.h"

namespace pag {

CJPAGSurface::~CJPAGSurface() { clear(); }

extern "C" {
long long cj_PAGSurface_setupOffscreen(int width, int height) {
    static std::shared_ptr<PAGSurface> surface = PAGSurface::MakeOffscreen(width, height);
    if (!surface) {
        return -1;
    }
    CJPAGSurface *handler = new CJPAGSurface(surface);
    // Declare and initialize pointers to classes
    return (int64_t)handler;
}

int64_t cj_PAGSurface_fromSurfaceID(int64_t surfaceId) {
    OHNativeWindow *window = nullptr;
    int ret = OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &window);
    if (ret != 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_fromSurfaceID",
                     "Could not Create Native Window From Surface Id: %{public}ld", surfaceId);
        return -1;
    }
    auto drawable = pag::GPUDrawable::FromWindow(window);
    std::shared_ptr<PAGSurface> surface = PAGSurface::MakeFrom(drawable);
    if (!surface) {
        return -1;
    }
    CJPAGSurface *handler = new CJPAGSurface(surface);
    return (int64_t)handler;
}

long long cj_PAGSurface_width(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_width", "Pointer is null");
        return 0;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    return instance->get()->width();
}

long long cj_PAGSurface_height(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_height", "Pointer is null");
        return 0;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    return instance->get()->height();
}

bool cj_PAGSurface_clearAll(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_clearAll", "Pointer is null");
        return false;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    return instance->get()->clearAll();
}

void cj_PAGSurface_freeCache(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_freeCache", "Pointer is null");
        return;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    instance->get()->freeCache();
    return;
}

void cj_PAGSurface_updateSize(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_updateSize", "Pointer is null");
        return;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    instance->get()->updateSize();
    return;
}

CJPixelMap cj_PAGSurface_makeSnapshot(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_makeSnapshot", "Pointer is null");
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    if (instance != nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    return MakeSnapshot(instance->get());
}

void cj_PAGSurface_release(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGSurface_release", "Pointer is null");
        return;
    }
    CJPAGSurface *instance;
    instance = (CJPAGSurface *)ptr;
    if (!instance || !instance->get()) {
        return;
    }
    instance->get()->freeCache();
    delete instance;
    return;
}
}
} // namespace pag
