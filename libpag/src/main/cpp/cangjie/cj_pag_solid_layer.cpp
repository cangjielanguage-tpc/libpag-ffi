/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_helper.h"
#include "cj_pag_layer_handle.h"

namespace pag {
extern "C" {

long long cj_PAGSolidLayer_make(const int64_t duration, const int64_t width, const int64_t height,
                                pag::Color solidColor, const uint8_t opacity) {
    if (width <= 0 || height <= 0 || duration <= 0) {
        return -1;
    }
    std::shared_ptr<PAGSolidLayer> layer = PAGSolidLayer::Make(duration, width, height, solidColor, opacity);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

static std::shared_ptr<PAGSolidLayer> getPAGSolidLayer(const int64_t ptr) {
    if (ptr == 0) {
        return nullptr;
    }
    CJPAGLayerHandle *instance = (CJPAGLayerHandle *)ptr;
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        return nullptr;
    }
    if (layer && layer->layerType() == LayerType::Solid) {
        return std::static_pointer_cast<PAGSolidLayer>(layer);
    }
    return nullptr;
}

long long cj_PAGSolidLayer_solidColor(const int64_t ptr) {
    std::shared_ptr<PAGSolidLayer> solidLayer = getPAGSolidLayer(ptr);
    if (solidLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGSolidLayer]",
                     "[solidColor]-the pointer of PAGSolidLayer is null.");
        return 0;
    }

    Color color = solidLayer->solidColor();
    long long res = MakeColorInt(color.red, color.green, color.blue);
    return res;
}

void cj_PAGSolidLayer_setSolidColor(const int64_t ptr, const int64_t solidColor) {
    std::shared_ptr<PAGSolidLayer> solidLayer = getPAGSolidLayer(ptr);
    if (solidLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGSolidLayer]",
                     "[setSolidColor]-the pointer of PAGSolidLayer is null.");
        return;
    }
    Color color = ToColor(solidColor);
    solidLayer->setSolidColor(color);
}
}
} // namespace pag
