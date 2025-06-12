/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_layer_handle.h"
#include "pag/file.h"

namespace pag {
extern "C" {

long long cj_PAGShapeLayer_make(int *bytes, const int64_t length, char *filePath, char *password) {
    std::string fp = filePath;
    std::string pwd = password;
    static std::shared_ptr<File> file = File::Load(bytes, length, fp, pwd);
    PAGShapeLayer *pagLayer = new PAGShapeLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGShapeLayer> layer = std::shared_ptr<pag::PAGShapeLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGShapeLayer_makeByURL(char *filePath, char *password) {
    std::string fp = filePath;
    std::string pwd = password;
    static std::shared_ptr<File> file = File::Load(fp, pwd);
    PAGShapeLayer *pagLayer = new PAGShapeLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGShapeLayer> layer = std::shared_ptr<pag::PAGShapeLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}
}
} // namespace pag
