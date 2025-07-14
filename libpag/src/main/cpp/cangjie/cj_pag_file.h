/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#pragma once

#include "cj_helper.h"
#include "cj_pag_image.h"
#include "cj_pag_layer_handle.h"
#include "pag/file.h"

namespace pag {
typedef struct {
    bool applyFill;
    bool applyStroke;
    bool boxText;
    bool fauxBold;
    bool strokeOverFill;
    bool fauxItalic;
    float baselineShift;
    float firstBaseLine;
    float fontSize;
    float strokeWidth;
    float leading;
    float tracking;
    uint8_t backgroundAlpha;
    uint32_t fillColor;
    uint32_t strokeColor;
    uint32_t backgroundColor;
    uint8_t justification;
    float boxTextRect[4];
    CJBytesArray fontFamily;
    CJBytesArray fontStyle;
    CJBytesArray text;
} PAGTextData;

extern "C" {
uint32_t cj_PAGFile_MaxSupportedTagLevel();
int64_t cj_PAGFile_LoadFromPath(const char *path);
int64_t cj_PAGFile_LoadFromBytes(uint8_t *bytes, size_t length, const char *path);
int64_t cj_PAGFile_tagLevel(const int64_t ptr);
int64_t cj_PAGFile_numTexts(const int64_t ptr);
int64_t cj_PAGFile_numImages(const int64_t ptr);
int64_t cj_PAGFile_numVideos(const int64_t ptr);
CJBytesArray cj_PAGFile_path(const int64_t ptr);
PAGTextData cj_PAGFile_getTextData(const int64_t ptr, int32_t index);
void cj_PAGFile_replaceText(const int64_t ptr, int32_t index, PAGTextData data);
void cj_PAGFile_replaceImage(const int64_t ptrPAGFile, int32_t index, const int64_t ptrPAGImage);
void cj_PAGFile_replaceImageByName(const int64_t ptrPAGFile, const char *layerName, const int64_t ptrPAGImage);
CJInt64Array cj_PAGFile_getEditableIndices(const int64_t ptrPAGFile, const int32_t layerType);
int32_t cj_PAGFile_timeStretchMode(const int64_t ptrPAGFile);
void cj_PAGFile_setTimeStretchMode(const int64_t ptrPAGFile, int32_t mode);
void cj_PAGFile_setDuration(const int64_t ptrPAGFile, int64_t duration);
int64_t cj_PAGFile_duration(const int64_t ptrPAGFile);
int64_t cj_PAGFile_copyOriginal(const int64_t ptrPAGFile);
}
} // namespace pag