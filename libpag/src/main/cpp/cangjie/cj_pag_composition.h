/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_PAG_COMPOSITION_H
#define LIBPAG_CJ_CJ_PAG_COMPOSITION_H

#include "cj_helper.h"
#include "cj_pag_layer_handle.h"
#include <pag/pag.h>

extern "C" { // cangjie [PAGComposition] ffi
long long cj_PAGComposition_Make(int width, int height);
long long cj_PAGComposition_width(const int64_t ptr);
long long cj_PAGComposition_height(const int64_t ptr);
void cj_PAGComposition_setContentSize(const int64_t ptr, int width, int height);
long long cj_PAGComposition_numChildren(const int64_t ptr);
long long cj_PAGComposition_getLayerAt(const int64_t ptr, const int64_t index);
long long cj_PAGComposition_getLayerIndex(const int64_t ptr, const int64_t nativeLayer);
void cj_PAGComposition_setLayerIndex(const int64_t ptr, const int64_t nativeLayer, const int64_t index);
bool cj_PAGComposition_addLayer(const int64_t ptr, const int64_t nativeLayer);
bool cj_PAGComposition_addLayerAt(const int64_t ptr, const int64_t nativeLayer, const int64_t index);
bool cj_PAGComposition_contains(const int64_t ptr, const int64_t nativeLayer);
long long cj_PAGComposition_removeLayer(const int64_t ptr, const int64_t nativeLayer);
long long cj_PAGComposition_removeLayerAt(const int64_t ptr, const int64_t index);
void cj_PAGComposition_removeAllLayers(const int64_t ptr);
void cj_PAGComposition_swapLayer(const int64_t ptr, const int64_t pagLayer1, const int64_t pagLayer2);
void cj_PAGComposition_swapLayerAt(const int64_t ptr, const int64_t index1, const int64_t index2);
CJBytesArray cj_PAGComposition_audioBytes(const int64_t ptr);
long long cj_PAGComposition_audioStartTime(const int64_t ptr);
MarkersPAGLayer cj_PAGComposition_audioMarkers(const int64_t ptr);
CJInt64Array cj_PAGComposition_getLayersByName(const int64_t ptr, char *layerName);
CJInt64Array cj_PAGComposition_getLayersUnderPoint(const int64_t ptr, float localX, float localY);
}
#endif // LIBPAG_CJ_CJ_PAG_COMPOSITION_H
