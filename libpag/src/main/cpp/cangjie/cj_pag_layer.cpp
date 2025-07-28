/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_layer_handle.h"

namespace pag {

CJPAGLayerHandle::~CJPAGLayerHandle() { reset(); }

extern "C" {
long long cj_PAGLayer_make(int *bytes, const int64_t length, char *filePath, char *password)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(password, password + strlen(password));
    static std::shared_ptr<File> file = File::Load(bytes, length, fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
    PAGLayer *pagLayer = new PAGLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> layer = std::shared_ptr<pag::PAGLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGLayer_makeByURL(char *filePath, char *password)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(password, password + strlen(password));
    static std::shared_ptr<File> file = File::Load(fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
    PAGLayer *pagLayer = new PAGLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> layer = std::shared_ptr<pag::PAGLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

int8_t cj_PAGLayer_layerType(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[layerType] - the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance->get()) {
        return LAYER_TYPE_UNKNOWN;
    }
    LayerType lt = instance->get()->layerType();
    int64_t types = LAYER_TYPE_UNKNOWN;
    switch (lt) {
        case LayerType::Unknown:
            types = LAYER_TYPE_UNKNOWN;
            break;
        case LayerType::Null:
            types = LAYER_TYPE_NULL;
            break;
        case LayerType::Solid:
            types = LAYER_TYPE_SOLID;
            break;
        case LayerType::Text:
            types = LAYER_TYPE_TEXT;
            break;
        case LayerType::Shape:
            types = LAYER_TYPE_SHAPE;
            break;
        case LayerType::Image:
            types = LAYER_TYPE_IMAGE;
            break;
        case LayerType::PreCompose:
            types = LAYER_TYPE_PRECOMPOSE;
            break;
        case LayerType::Camera:
            types = LAYER_TYPE_CAMERA;
            break;
        default:
            types = LAYER_TYPE_UNKNOWN;
            break;
    }
    return types;
}

bool cj_PAGLayer_isPAGFile(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[isPAGFile]-the pointer of PAGLayer is null.");
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance->get()) {
        return false;
    }
    bool flag = instance->get()->isPAGFile();
    return flag;
}

CJBytesArray cj_PAGLayer_layerName(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[layerName]-the pointer of PAGLayer is null.");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::string layerName = instance->get()->layerName();
    CJBytesArray result = stringToCJBytesArray(layerName);
    return result;
}

void cj_PAGLayer_matrix(const int64_t ptr, float buf[])
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[matrix]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    instance->get()->matrix().get9(buf);
}

void cj_PAGLayer_setMatrix(const int64_t ptr, float *buf)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    auto pagLayer = instance->get();
    if (pagLayer == nullptr) {
        return;
    }
    Matrix matrix = {};
    matrix.set9(buf);
    pagLayer->setMatrix(matrix);
}

void cj_PAGLayer_resetMatrix(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[resetMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    instance->get()->resetMatrix();
}

void cj_PAGLayer_getTotalMatrix(const int64_t ptr, float buf[])
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getTotalMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->getTotalMatrix().get9(buf);
}

bool cj_PAGLayer_visible(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[visible]-the pointer of PAGLayer is null.");
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    bool visible = instance->get()->visible();
    return visible;
}

void cj_PAGLayer_setVisible(const int64_t ptr, bool value)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setVisible]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->setVisible(value);
}

int cj_PAGLayer_editableIndex(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[editableInde]-the pointer of PAGLayer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int visible = instance->get()->editableIndex();
    return visible;
}

long long cj_PAGLayer_parent(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[parent]-the pointer of PAGLayer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<PAGComposition> pagComposition = instance->get()->parent();
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagComposition);
    return (int64_t)cjlayer;
}

MarkersPAGLayer cj_PAGLayer_markers(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[markers]-the pointer of PAGLayer is null.");
        return MarkersPAGLayer{0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::vector<const Marker *> markers = instance->get()->markers();
    long long size = markers.size();
    CJMarker *arr = CreateMarkers(markers);
    if (arr == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[markers]-create markers fail. the size = %{public}lld", size);
        return MarkersPAGLayer{0, nullptr};
    }
    return MarkersPAGLayer{size, arr};
}

int64_t cj_PAGLayer_localTimeToGlobal(const int64_t ptr, const int64_t localTime)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[localTimeToGlobal]-the pointer of PAGLayer is null.");
        return localTime;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int64_t times = instance->get()->localTimeToGlobal(localTime);
    return times;
}

int64_t cj_PAGLayer_globalToLocalTime(const int64_t ptr, const int64_t globalTime)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[globalToLocalTime]-the pointer of PAGLayer is null.");
        return globalTime;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int64_t times = instance->get()->globalToLocalTime(globalTime);
    return times;
}

int64_t cj_PAGLayer_duration(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[duration]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int64_t times = instance->get()->duration();
    return times;
}

float cj_PAGLayer_frameRate(const int64_t ptr)
{
    constexpr float DEFAULT_MAX_FRAME_RATE = 60.0f;
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[frameRate]-the pointer of PAGLayer is null.");
        return DEFAULT_MAX_FRAME_RATE;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    float frameRate = instance->get()->frameRate();
    return frameRate;
}

int64_t cj_PAGLayer_startTime(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[startTime]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int64_t times = instance->get()->startTime();
    return times;
}

void cj_PAGLayer_setStartTime(const int64_t ptr, const int64_t time)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setStartTime]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->setStartTime(time);
}

int64_t cj_PAGLayer_currentTime(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[currentTime]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    int64_t times = instance->get()->currentTime();
    return times;
}

void cj_PAGLayer_setCurrentTime(const int64_t ptr, const int64_t time)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setCurrentTime]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->setCurrentTime(time);
}

double cj_PAGLayer_getProgress(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getProgress]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    double progress = instance->get()->getProgress();
    return progress;
}

void cj_PAGLayer_setProgress(const int64_t ptr, const double value)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setProgress]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->setProgress(value);
}

int64_t cj_PAGLayer_trackMatteLayer(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[trackMatteLayer]-the pointer of PAGLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<PAGLayer> layer = instance->get()->trackMatteLayer();
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

float *cj_PAGLayer_getBounds(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getBounds]-the pointer of PAGLayer is null.");
        return nullptr;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    Rect rect = instance->get()->getBounds();
    return CreateRect(rect);
}

bool cj_PAGLayer_excludedFromTimeline(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[excludedFromTimeline]-the pointer of PAGLayer is null.");
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    bool res = instance->get()->excludedFromTimeline();
    return res;
}

void cj_PAGLayer_setExcludedFromTimeline(const int64_t ptr, bool value)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[setExcludedFromTimeline]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->get()->setExcludedFromTimeline(value);
}

bool cj_PAGLayer_nativeEquals(const int64_t ptr, const int64_t otherptr)
{
    if (ptr == 0 && otherptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[nativeEquals]-the pointer and the other pointer of PAGLayer is null.");
        return true;
    } else if (ptr == 0 || otherptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[nativeEquals]-the pointer or the other pointer of PAGLayer is null.");
        return false;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    intptr_t otherptrInt = static_cast<intptr_t>(otherptr);
    CJPAGLayerHandle *instanceOther = reinterpret_cast<CJPAGLayerHandle *>(otherptrInt);
    std::shared_ptr<pag::PAGLayer> layerOther = instanceOther->get();
    return layer == layerOther;
}

void cj_PAGLayer_nativeRelease(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[nativeRelease]-the pointer of PAGLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    instance->reset();
    delete instance;
}

bool cj_PAGLayer_isNullptr(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[isNullptr]-the pointer of PAGLayer is null.");
        return true;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> pagLayer = instance->get();
    return pagLayer == nullptr;
}
}
} // namespace pag
