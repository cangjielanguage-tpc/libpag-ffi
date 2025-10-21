/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_layer_handle.h"
#include "pag/file.h"

namespace pag {
extern "C" {
long long cj_PAGShapeLayer_make(int *bytes, const int64_t length, char *filePath, char *credentialKey)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(credentialKey, credentialKey + strlen(credentialKey));
    static std::shared_ptr<File> file = File::Load(bytes, length, fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
    PAGShapeLayer *pagLayer = new PAGShapeLayer(file, nullptr);
    if (!pagLayer) {
        return -1;
    }
    std::shared_ptr<pag::PAGShapeLayer> layer = std::shared_ptr<pag::PAGShapeLayer>(pagLayer);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    return (int64_t)cjlayer;
}

long long cj_PAGShapeLayer_makeByURL(char *filePath, char *credentialKey)
{
    std::string fp = filePath;
    std::vector<char> pwdSecret(credentialKey, credentialKey + strlen(credentialKey));
    static std::shared_ptr<File> file = File::Load(fp, std::string(pwdSecret.data()));
    std::fill(pwdSecret.begin(), pwdSecret.end(), 0);
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
