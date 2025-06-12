/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_layer_handle.h"

namespace pag {

CJPAGLayerHandle::~CJPAGLayerHandle() { reset(); }

extern "C" {

long long cj_PAGLayer_make(int *bytes, const int64_t length, char *filePath, char *password) {
    std::string fp = filePath;
    std::string pwd = password;
    static std::shared_ptr<File> file = File::Load(bytes, length, fp, pwd);
    PAGLayer *pagLayer = new PAGLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> layer = std::shared_ptr<pag::PAGLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGLayer_makeByURL(char *filePath, char *password) {
    std::string fp = filePath;
    std::string pwd = password;
    static std::shared_ptr<File> file = File::Load(fp, pwd);
    PAGLayer *pagLayer = new PAGLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> layer = std::shared_ptr<pag::PAGLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

int8_t cj_PAGLayer_layerType(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[layerType]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;

    LayerType lt = instance->get()->layerType();
    int64_t types = 0;
    switch (lt) {
    case LayerType::Unknown:
        types = 0;
        break;
    case LayerType::Null:
        types = 1;
        break;
    case LayerType::Solid:
        types = 2;
        break;
    case LayerType::Text:
        types = 3;
        break;
    case LayerType::Shape:
        types = 4;
        break;
    case LayerType::Image:
        types = 5;
        break;
    case LayerType::PreCompose:
        types = 6;
        break;
    case LayerType::Camera:
        types = 7;
        break;
    default:
        types = 0;
    }
    return types;
}

bool cj_PAGLayer_isPAGFile(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[isPAGFile]-the pointer of PAGLayer is null.");
        return false;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    bool flag = instance->get()->isPAGFile();
    return flag;
}

char *cj_PAGLayer_layerName(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[layerName]-the pointer of PAGLayer is null.");
        return nullptr;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    std::string layerName = instance->get()->layerName();
    char *cstr = new char[layerName.size() + 1];
    std::strcpy(cstr, layerName.c_str());
    return cstr;
}

void cj_PAGLayer_matrix(const int64_t ptr, float buf[]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[matrix]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;

    instance->get()->matrix().get9(buf);
}

void cj_PAGLayer_setMatrix(const int64_t ptr, float *buf) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    auto pagLayer = instance->get();
    if (pagLayer == nullptr) {
        return;
    }
    Matrix matrix = {};
    matrix.set9(buf);
    pagLayer->setMatrix(matrix);
}

void cj_PAGLayer_resetMatrix(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[resetMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;

    instance->get()->resetMatrix();
}

void cj_PAGLayer_getTotalMatrix(const int64_t ptr, float buf[]) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getTotalMatrix]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->getTotalMatrix().get9(buf);
}

bool cj_PAGLayer_visible(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[visible]-the pointer of PAGLayer is null.");
        return false;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    bool visible = instance->get()->visible();
    return visible;
}

void cj_PAGLayer_setVisible(const int64_t ptr, bool value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setVisible]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->setVisible(value);
}

int cj_PAGLayer_editableIndex(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[editableInde]-the pointer of PAGLayer is null.");
        return -1;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int visible = instance->get()->editableIndex();
    return visible;
}

long long cj_PAGLayer_parent(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[parent]-the pointer of PAGLayer is null.");
        return -1;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    std::shared_ptr<PAGComposition> pagComposition = instance->get()->parent();
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagComposition);
    return (int64_t)cjlayer;
}

MarkersPAGLayer cj_PAGLayer_markers(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[markers]-the pointer of PAGLayer is null.");
        return MarkersPAGLayer{0, nullptr};
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
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

int64_t cj_PAGLayer_localTimeToGlobal(const int64_t ptr, const int64_t localTime) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[localTimeToGlobal]-the pointer of PAGLayer is null.");
        return localTime;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int64_t times = instance->get()->localTimeToGlobal(localTime);
    return times;
}

int64_t cj_PAGLayer_globalToLocalTime(const int64_t ptr, const int64_t globalTime) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[globalToLocalTime]-the pointer of PAGLayer is null.");
        return globalTime;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int64_t times = instance->get()->globalToLocalTime(globalTime);
    return times;
}

int64_t cj_PAGLayer_duration(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[duration]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int64_t times = instance->get()->duration();
    return times;
}

float cj_PAGLayer_frameRate(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[frameRate]-the pointer of PAGLayer is null.");
        return 60.0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    float frameRate = instance->get()->frameRate();
    return frameRate;
}

int64_t cj_PAGLayer_startTime(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[startTime]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int64_t times = instance->get()->startTime();
    return times;
}

void cj_PAGLayer_setStartTime(const int64_t ptr, const int64_t time) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setStartTime]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->setStartTime(time);
}

int64_t cj_PAGLayer_currentTime(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[currentTime]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    int64_t times = instance->get()->currentTime();
    return times;
}

void cj_PAGLayer_setCurrentTime(const int64_t ptr, const int64_t time) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setCurrentTime]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->setCurrentTime(time);
}

double cj_PAGLayer_getProgress(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getProgress]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    double progress = instance->get()->getProgress();
    return progress;
}

void cj_PAGLayer_setProgress(const int64_t ptr, const double value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[setProgress]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->setProgress(value);
}

int64_t cj_PAGLayer_trackMatteLayer(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[trackMatteLayer]-the pointer of PAGLayer is null.");
        return 0;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    std::shared_ptr<PAGLayer> layer = instance->get()->trackMatteLayer();
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

float *cj_PAGLayer_getBounds(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[getBounds]-the pointer of PAGLayer is null.");
        return nullptr;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    Rect rect = instance->get()->getBounds();
    return CreateRect(rect);
}

bool cj_PAGLayer_excludedFromTimeline(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[excludedFromTimeline]-the pointer of PAGLayer is null.");
        return false;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    bool res = instance->get()->excludedFromTimeline();
    return res;
}

void cj_PAGLayer_setExcludedFromTimeline(const int64_t ptr, bool value) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[setExcludedFromTimeline]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    instance->get()->setExcludedFromTimeline(value);
}

bool cj_PAGLayer_nativeEquals(const int64_t ptr, const int64_t otherptr) {
    if (ptr == 0 && otherptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[nativeEquals]-the pointer and the other pointer of PAGLayer is null.");
        return true;
    } else if (ptr == 0 || otherptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]",
                     "[nativeEquals]-the pointer or the other pointer of PAGLayer is null.");
        return false;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    CJPAGLayerHandle *instanceOther;
    instanceOther = (CJPAGLayerHandle *)otherptr;
    std::shared_ptr<pag::PAGLayer> layerOther = instanceOther->get();
    return layer == layerOther;
}

void cj_PAGLayer_nativeRelease(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[nativeRelease]-the pointer of PAGLayer is null.");
        return;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    delete instance;
}

bool cj_PAGLayer_isNullptr(const int64_t ptr) {
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGLayer]", "[isNullptr]-the pointer of PAGLayer is null.");
        return true;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
    std::shared_ptr<pag::PAGLayer> pagLayer = instance->get();
    return pagLayer == nullptr;
}
}
} // namespace pag
