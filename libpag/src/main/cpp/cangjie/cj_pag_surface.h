/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_PAG_SURFACE_H
#define LIBPAG4CJ_CJ_PAG_SURFACE_H

#include "../../external/platform/GPUDrawable.h"
#include "cj_helper.h"

namespace pag {
class CJPAGSurface {
public:
    explicit CJPAGSurface(std::shared_ptr<PAGSurface> pagSurface) : pagSurface(pagSurface) {}

    virtual ~CJPAGSurface();

    std::shared_ptr<PAGSurface> get()
    {
        std::lock_guard lock_guard(locker);
        return pagSurface;
    }

    void clear()
    {
        std::lock_guard lock_guard(locker);
        pagSurface = nullptr;
    }

private:
    std::shared_ptr<pag::PAGSurface> pagSurface;
    std::mutex locker;
};

extern "C" {
long long cj_PAGSurface_setupOffscreen(int width, int height);
int64_t cj_PAGSurface_fromSurfaceID(int64_t surfaceId);
long long cj_PAGSurface_width(const int64_t ptr);
long long cj_PAGSurface_height(const int64_t ptr);
bool cj_PAGSurface_clearAll(const int64_t ptr);
void cj_PAGSurface_freeCache(const int64_t ptr);
void cj_PAGSurface_updateSize(const int64_t ptr);
CJPixelMap cj_PAGSurface_makeSnapshot(const int64_t ptr);
void cj_PAGSurface_release(const int64_t ptr);
}
} // namespace pag
#endif // LIBPAG4CJ_CJ_PAG_SURFACE_H
