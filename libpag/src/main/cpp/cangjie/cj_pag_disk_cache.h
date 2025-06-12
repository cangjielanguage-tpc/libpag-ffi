/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_PAG_DISK_CACHE_H
#define LIBPAG4CJ_CJ_PAG_DISK_CACHE_H

#include <pag/pag.h>
#include "cj_type.h"
#include <hilog/log.h>
#include "rendering/caches/DiskCache.h"

extern "C" {// cangjie [PAGDiskCache] ffi
long long cj_PAGDiskCache_maxDiskSize();
void cj_PAGDiskCache_setMaxDiskSize(int size);
void cj_PAGDiskCache_removeAll();
CJBytesArray cj_PAGDiskCache_readFile(char* key);
bool cj_PAGDiskCache_writeFile(char* key, uint8_t* bytes, int size);
}

#endif //LIBPAG4CJ_CJ_PAG_DISK_CACHE_H
