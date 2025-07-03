/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_disk_cache.h"

namespace pag {
extern "C" {

long long cj_PAGDiskCache_maxDiskSize() { return static_cast<long>(PAGDiskCache::MaxDiskSize()); }

void cj_PAGDiskCache_setMaxDiskSize(int size) { PAGDiskCache::SetMaxDiskSize(size); }

void cj_PAGDiskCache_removeAll() { PAGDiskCache::RemoveAll(); }

CJBytesArray cj_PAGDiskCache_readFile(char *key) {
    const std::string &str = key;
    auto data = pag::DiskCache::ReadFile(str);
    if (data == nullptr) {
        return {0, nullptr};
    }
    int size = data->size();
    auto bytes = reinterpret_cast<const uint8_t *>(data->data());
    uint8_t *buf = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        buf[i] = bytes[i];
    }
    return CJBytesArray{size, buf};
}

bool cj_PAGDiskCache_writeFile(char *key, uint8_t *bytes, int size) {
    auto byteData = tgfx::Data::MakeWithoutCopy(bytes, size);
    auto result = pag::DiskCache::WriteFile(key, byteData);
    return result;
}

void cj_PAGDiskCache_SetCacheDir(char *path) {
    const std::string &cacheDir = path;
    auto nativePlatform =
        const_cast<NativePlatform *>(reinterpret_cast<const NativePlatform *>(NativePlatform::Current()));
    nativePlatform->setCacheDir(cacheDir);
    return;
}
}
} // namespace pag
