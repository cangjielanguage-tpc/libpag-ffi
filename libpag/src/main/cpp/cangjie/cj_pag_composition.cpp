/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_composition.h"

namespace pag {
extern "C" {
static std::shared_ptr<PAGComposition> getPAGComposition(std::shared_ptr<pag::PAGLayer> layer)
{
    if (layer && layer->layerType() == LayerType::PreCompose) {
        return std::static_pointer_cast<PAGComposition>(layer);
    }
    return nullptr;
}

long long cj_PAGComposition_Make(int width, int height)
{
    std::shared_ptr<PAGComposition> pagComposition = PAGComposition::Make(width, height);
    if (!pagComposition) {
        return 0;
    }
    CJPAGLayerHandle *handler = new CJPAGLayerHandle(pagComposition);
    return (int64_t)handler;
}

long long cj_PAGComposition_width(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[width]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }
    return pagComposition->width();
}

long long cj_PAGComposition_height(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "PAGComposition]",
                     "[height]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }
    return pagComposition->height();
}

void cj_PAGComposition_setContentSize(const int64_t ptr, int width, int height)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[setContentSize]-the pointer of PAGComposition is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return;
    }
    return pagComposition->setContentSize(width, height);
}

long long cj_PAGComposition_numChildren(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[numChildren]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }

    return pagComposition->numChildren();
}

long long cj_PAGComposition_getLayerAt(const int64_t ptr, const int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[getLayerAt]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> pagLayer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(pagLayer);
    if (pagComposition == nullptr) {
        return 0;
    }
    std::shared_ptr<PAGLayer> layer = pagComposition->getLayerAt(index);
    if (layer == nullptr) {
        return 0;
    }
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);

    return (int64_t)cjlayer;
}

long long cj_PAGComposition_getLayerIndex(const int64_t ptr, const int64_t nativeLayer)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[getLayerIndex]", "the pointer of PAGComposition is null.");
        return -1;
    } else if (nativeLayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[getLayerIndex]", "the pointer of PAGLayer is null.");
        return -1;
    }
    // Obtain the CJPAGLayerHandle corresponding to the native layer, and then obtain the PAGLayer.
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[getLayerIndex]", "[getLayerIndex]-the PAGLayer is null.");
        return -1;
    }
    // Retrieve the CJPAGLayerHandle corresponding to the current PAGComposition
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return -1;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call getLayerIndex
    long long layerIndex = pagComposition->getLayerIndex(pagLayer);
    return layerIndex;
}

void cj_PAGComposition_setLayerIndex(const int64_t ptr, const int64_t nativeLayer, const int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[setLayerIndex]-the pointer of PAGComposition is null.");
        return;
    }
    // Obtain the CJPAGLayerHandle corresponding to the native layer, and then obtain the PAGLayer.
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        return;
    }
    // Retrieve the CJPAGLayerHandle corresponding to the current PAGComposition
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call setLayerIndex
    pagComposition->setLayerIndex(pagLayer, index);
}

bool cj_PAGComposition_addLayer(const int64_t ptr, const int64_t nativeLayer)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[addLayer]-the pointer of PAGComposition is null.");
        return false;
    } else if (nativeLayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]", "[addLayer]-the pointer of PAGLayer is null.");
        return false;
    }
    // Obtain the CJPAGLayerHandle corresponding to the native layer, and then obtain the PAGLayer.
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        return false;
    }
    // Retrieve the CJPAGLayerHandle corresponding to the current PAGComposition
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return false;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call addLayer
    bool res = pagComposition->addLayer(pagLayer);
    return res;
}

bool cj_PAGComposition_addLayerAt(const int64_t ptr, const int64_t nativeLayer, const int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[addLayerAt]-the pointer of PAGComposition is null.");
        return false;
    } else if (nativeLayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[addLayerAt]-the pointer of PAGLayer is null.");
        return false;
    }
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return false;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call addLayerAt
    bool res = pagComposition->addLayerAt(pagLayer, index);
    return res;
}

bool cj_PAGComposition_contains(const int64_t ptr, const int64_t nativeLayer)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[contains]-the pointer of PAGComposition is null.");
        return false;
    } else if (nativeLayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]", "[contains]-the pointer of PAGLayer is null.");
        return false;
    }
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return false;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call contains
    bool res = pagComposition->contains(pagLayer);
    return res;
}

long long cj_PAGComposition_removeLayer(const int64_t ptr, const int64_t nativeLayer)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[removeLayer]-the pointer of PAGComposition is null.");
        return 0;
    } else if (nativeLayer == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[removeLayer]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t nativeLayerInt = static_cast<intptr_t>(nativeLayer);
    CJPAGLayerHandle *cjlayer = reinterpret_cast<CJPAGLayerHandle *>(nativeLayerInt);
    std::shared_ptr<PAGLayer> pagLayer = cjlayer->get();
    if (pagLayer == nullptr) {
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call removeLayer
    std::shared_ptr<PAGLayer> removeLayer = pagComposition->removeLayer(pagLayer);
    if (removeLayer == nullptr) {
        return 0;
    }
    CJPAGLayerHandle *cjremoveLayer = new CJPAGLayerHandle(removeLayer);
    return (int64_t)cjremoveLayer;
}

long long cj_PAGComposition_removeLayerAt(const int64_t ptr, const int64_t index)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[removeLayerAt]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call removeLayerAt
    std::shared_ptr<PAGLayer> removeLayer = pagComposition->removeLayerAt(index);
    if (removeLayer == nullptr) {
        return 0;
    }
    CJPAGLayerHandle *cjremoveLayer = new CJPAGLayerHandle(removeLayer);
    return (int64_t)cjremoveLayer;
}

void cj_PAGComposition_removeAllLayers(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[removeAllLayers]-the pointer of PAGComposition is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return;
    }

    return pagComposition->removeAllLayers();
}

void cj_PAGComposition_swapLayer(const int64_t ptr, const int64_t nativeLayer1, const int64_t nativeLayer2)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[swapLayer]-the pointer of PAGComposition is null.");
        return;
    } else if (nativeLayer1 == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[swapLayer]-the pointer of PAGLayer1 is null.");
        return;
    } else if (nativeLayer2 == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[swapLayer]-the pointer of PAGLayer2 is null.");
        return;
    }
    intptr_t nativeLayer1Int = static_cast<intptr_t>(nativeLayer1);
    CJPAGLayerHandle *cjlayer1 = reinterpret_cast<CJPAGLayerHandle *>(nativeLayer1Int);
    std::shared_ptr<PAGLayer> pagLayer1 = cjlayer1->get();
    if (pagLayer1 == nullptr) {
        return;
    }
    intptr_t nativeLayer2Int = static_cast<intptr_t>(nativeLayer2);
    CJPAGLayerHandle *cjlayer2 = reinterpret_cast<CJPAGLayerHandle *>(nativeLayer2Int);

    std::shared_ptr<PAGLayer> pagLayer2 = cjlayer2->get();
    if (pagLayer2 == nullptr) {
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return;
    }
    pagComposition->swapLayer(pagLayer1, pagLayer2);
}

void cj_PAGComposition_swapLayerAt(const int64_t ptr, const int64_t index1, const int64_t index2)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[swapLayerAt]-the pointer of PAGComposition is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return;
    }
    return pagComposition->swapLayerAt(index1, index2);
}

CJBytesArray cj_PAGComposition_audioBytes(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[audioBytes]-the pointer of PAGComposition is null.");
        return CJBytesArray{0, nullptr};
    }
    // Retrieve pag:: PAGComposition from CJPAGLayerHandle and call audiobytes
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]", "[audioBytes]-the PAGComposition is null.");
        return CJBytesArray{0, nullptr};
    }
    ByteData *audioBytes = pagComposition->audioBytes();
    if (audioBytes == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]", "[audioBytes]-the ByteData is null.");
        return CJBytesArray{0, nullptr};
    }
    int size = audioBytes->length();
    uint8_t *buf = audioBytes->data();
    uint8_t *bytes = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        bytes[i] = buf[i];
    }
    return CJBytesArray{size, bytes};
}

long long cj_PAGComposition_audioStartTime(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[audioStartTime]-the pointer of PAGComposition is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return 0;
    }

    return pagComposition->audioStartTime();
}

MarkersPAGLayer cj_PAGComposition_audioMarkers(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[audioMarkers]-the pointer of PAGComposition is null.");
        return MarkersPAGLayer{0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return MarkersPAGLayer{0, nullptr};
    }

    std::vector<const Marker *> markers = pagComposition->audioMarkers();
    if (markers.empty()) {
        return MarkersPAGLayer{0, nullptr};
    }

    long long size = markers.size();

    CJMarker *arr = CreateMarkers(markers);
    return MarkersPAGLayer{size, arr};
}

CJInt64Array cj_PAGComposition_getLayersByName(const int64_t ptr, char *layerName)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[getLayersByName]-the pointer of PAGComposition is null.");
        return CJInt64Array{0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return CJInt64Array{0, nullptr};
    }
    const std::string &ln = layerName;
    std::vector<std::shared_ptr<PAGLayer>> pagLayers = pagComposition->getLayersByName(ln);
    if (pagLayers.empty()) {
        return CJInt64Array{0, nullptr};
    }
    long long size = pagLayers.size();
    int64_t *arr = new int64_t[size];
    for (size_t i = 0; i < pagLayers.size(); i++) {
        std::shared_ptr<PAGLayer> pagLayer = pagLayers[i];
        if (pagLayer == nullptr) {
            return CJInt64Array{0, nullptr};
        }

        CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagLayer);
        arr[i] = (int64_t)cjlayer;
    }
    return CJInt64Array{size, arr};
}

CJInt64Array cj_PAGComposition_getLayersUnderPoint(const int64_t ptr, float localX, float localY)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGComposition]",
                     "[getLayersUnderPoint]-the pointer of PAGComposition is null.");
        return CJInt64Array{0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    std::shared_ptr<pag::PAGComposition> pagComposition = getPAGComposition(layer);
    if (pagComposition == nullptr) {
        return CJInt64Array{0, nullptr};
    }
    std::vector<std::shared_ptr<PAGLayer>> pagLayers = pagComposition->getLayersUnderPoint(localX, localY);
    if (pagLayers.empty()) {
        return CJInt64Array{0, nullptr};
    }
    long long size = pagLayers.size();
    int64_t *arr = new int64_t[size];
    for (size_t i = 0; i < pagLayers.size(); i++) {
        std::shared_ptr<PAGLayer> pagLayer = pagLayers[i];
        if (pagLayer == nullptr) {
            return CJInt64Array{0, nullptr};
        }
        CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagLayer);
        arr[i] = (int64_t)cjlayer;
    }
    return CJInt64Array{size, arr};
}
}
} // namespace pag
