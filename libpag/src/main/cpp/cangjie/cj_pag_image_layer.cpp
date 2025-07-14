/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_image.h"
#include "cj_pag_layer_handle.h"

namespace pag {
extern "C" {

long long cj_PAGImageLayer_make(int *bytes, const int64_t length, char *filePath, char *password)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(password, password + strlen(password));
    static std::shared_ptr<File> file = File::Load(bytes, length, fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
    PAGImageLayer *pagLayer = new PAGImageLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGImageLayer> layer = std::shared_ptr<pag::PAGImageLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGImageLayer_makeByURL(char *filePath, char *password)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(password, password + strlen(password));
    static std::shared_ptr<File> file = File::Load(fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
    PAGImageLayer *pagLayer = new PAGImageLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGImageLayer> layer = std::shared_ptr<pag::PAGImageLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGImageLayer_nativeMake(const int64_t width, const int64_t height, const int64_t duration)
{
    if (width <= 0 || height <= 0 || duration <= 0) {
        return -1;
    }

    std::shared_ptr<PAGImageLayer> layer = PAGImageLayer::Make(width, height, duration);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

static std::shared_ptr<PAGImageLayer> getPAGImageLayer(std::shared_ptr<pag::PAGLayer> layer)
{
    if (layer && layer->layerType() == LayerType::Image) {
        return std::static_pointer_cast<PAGImageLayer>(layer);
    }
    return nullptr;
}

long long cj_PAGImageLayer_contentDuration(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[contentDuration]-the pointer of PAGImageLayer is null.");
        return 0;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]", "[contentDuration]-the layer is nullptr.");
        return 0;
    }

    std::shared_ptr<PAGImageLayer> imageLayer = getPAGImageLayer(layer);
    long long times = imageLayer->contentDuration();
    return times;
}

CJPAGVideoRangeArray cj_PAGImageLayer_getVideoRanges(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[getVideoRanges]-the pointer of PAGImageLayer is null.");
        return CJPAGVideoRangeArray{0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]", "[getVideoRanges]-the layer is nullptr.");
        return CJPAGVideoRangeArray{0, nullptr};
    }

    std::shared_ptr<PAGImageLayer> imageLayer = getPAGImageLayer(layer);
    std::vector<PAGVideoRange> pagVideoRanges = imageLayer->getVideoRanges();
    long long size = pagVideoRanges.size();
    if (size == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]", "[getVideoRanges]-the layer is nullptr.");
        return CJPAGVideoRangeArray{0, nullptr};
    }

    CJPAGVideoRange *arr = CreateVideoRanges(pagVideoRanges);
    return CJPAGVideoRangeArray{size, arr};
}

void cj_PAGImageLayer_setImage(const int64_t ptr, const int64_t image)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[setImage]-the pointer of PAGImageLayer is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]", "[setImage]-the layer is nullptr.");
        return;
    }

    std::shared_ptr<PAGImageLayer> imageLayer = getPAGImageLayer(layer);
    intptr_t imageInt = static_cast<intptr_t>(image);
    CJPAGImage *cjimage = reinterpret_cast<CJPAGImage *>(imageInt);
    if (cjimage == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]", "[setImage]-the image is nullptr.");
        imageLayer->setImage(nullptr);
    } else {
        std::shared_ptr<PAGImage> pagimage = cjimage->get();
        imageLayer->setImage(pagimage);
    }
}

CJBytesArray cj_PAGImageLayer_imageBytes(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[imageBytes]-the pointer of PAGImageLayer is null.");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);

    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[imageBytes]-imageBytes: the layer is nullptr.");
        return {0, nullptr};
    }
    std::shared_ptr<PAGImageLayer> imageLayer = getPAGImageLayer(layer);
    ByteData *data = imageLayer->imageBytes();
    if (data == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageLayer]",
                     "[imageBytes]-The result value obtained through the ImageLayer function imagebytes is nullptr.");
        return {0, nullptr};
    }
    int size = data->length();
    auto buf = reinterpret_cast<const uint8_t *>(data->data());
    uint8_t *bytes = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        bytes[i] = buf[i];
    }
    return CJBytesArray{size, bytes};
}
}
}