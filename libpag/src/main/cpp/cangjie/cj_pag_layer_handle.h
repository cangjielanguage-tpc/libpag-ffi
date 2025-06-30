/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG_CJ_CJ_PAG_LAYER_HANDLE_H
#define LIBPAG_CJ_CJ_PAG_LAYER_HANDLE_H

#include "cj_helper.h"
#include "pag/file.h"
#include <pag/pag.h>

namespace pag {
class CJPAGLayerHandle {
public:
    explicit CJPAGLayerHandle(std::shared_ptr<pag::PAGLayer> layer) : layer(layer) {}

    virtual ~CJPAGLayerHandle();

    std::shared_ptr<pag::PAGLayer> get() {
        std::lock_guard lock_guard(locker);
        return layer;
    }

    void reset() {
        std::lock_guard lock_guard(locker);
        layer = nullptr;
    }

private:
    std::shared_ptr<pag::PAGLayer> layer;
    std::mutex locker;
};

} // namespace pag

extern "C" { // cangjie [PAGLayer] ffi
long long cj_PAGLayer_make(int *bytes, const int64_t length, char *filePath, char *password);
long long cj_PAGLayer_makeByURL(char *filePath, char *password);
int8_t cj_PAGLayer_layerType(const int64_t ptr);
char *cj_PAGLayer_layerName(const int64_t ptr);
void cj_PAGLayer_matrix(const int64_t ptr, float buf[]);
void cj_PAGLayer_setMatrix(const int64_t ptr, float *buf);
void cj_PAGLayer_resetMatrix(const int64_t ptr);
void cj_PAGLayer_getTotalMatrix(const int64_t ptr, float buf[]);
bool cj_PAGLayer_visible(const int64_t ptr);
void cj_PAGLayer_setVisible(const int64_t ptr, bool value);
int cj_PAGLayer_editableIndex(const int64_t ptr);
long long cj_PAGLayer_parent(const int64_t ptr);
MarkersPAGLayer cj_PAGLayer_markers(const int64_t ptr);
int64_t cj_PAGLayer_localTimeToGlobal(const int64_t ptr, const int64_t localTime);
int64_t cj_PAGLayer_globalToLocalTime(const int64_t ptr, const int64_t globalTime);
int64_t cj_PAGLayer_duration(const int64_t ptr);
float cj_PAGLayer_frameRate(const int64_t ptr);
int64_t cj_PAGLayer_startTime(const int64_t ptr);
void cj_PAGLayer_setStartTime(const int64_t ptr, const int64_t time);
int64_t cj_PAGLayer_currentTime(const int64_t ptr);
void cj_PAGLayer_setCurrentTime(const int64_t ptr, const int64_t time);
double cj_PAGLayer_getProgress(const int64_t ptr);
void cj_PAGLayer_setProgress(const int64_t ptr, const double value);
bool cj_PAGLayer_isPAGFile(const int64_t ptr);
int64_t cj_PAGLayer_trackMatteLayer(const int64_t ptr);
float *cj_PAGLayer_getBounds(const int64_t ptr);
bool cj_PAGLayer_excludedFromTimeline(const int64_t ptr);
void cj_PAGLayer_setExcludedFromTimeline(const int64_t ptr, bool value);
bool cj_PAGLayer_nativeEquals(const int64_t ptr, const int64_t otherptr);
void cj_PAGLayer_nativeRelease(const int64_t ptr);
bool cj_PAGLayer_isNullptr(const int64_t ptr);
// cangjie [PAGShapeLayer] ffi
long long cj_PAGShapeLayer_make(int *bytes, const int64_t length, char *filePath, char *password);
long long cj_PAGShapeLayer_makeByURL(char *filePath, char *password);
// cangjie [PAGImageLayer] ffi
long long cj_PAGImageLayer_nativeMake(const int64_t width, const int64_t height, const int64_t duration);
long long cj_PAGImageLayer_contentDuration(const int64_t ptr);
CJPAGVideoRangeArray cj_PAGImageLayer_getVideoRanges(const int64_t ptr);
void cj_PAGImageLayer_setImage(const int64_t ptr, const int64_t image);
CJBytesArray cj_PAGImageLayer_imageBytes(const int64_t ptr);
// cangjie [PAGSolidLayer] ffi
long long cj_PAGSolidLayer_make(const int64_t duration, const int64_t width, const int64_t height,
                                pag::Color solidColor, const uint8_t opacity);
long long cj_PAGSolidLayer_solidColor(const int64_t ptr);
void cj_PAGSolidLayer_setSolidColor(const int64_t ptr, const int64_t solidColor);
// cangjie [PAGTextLayer] ffi
long long cj_PAGTextLayer_make(const int64_t duration, char *text, float fontSize, char *fontFamily, char *fontStyle);
long long cj_PAGTextLayer_fillColor(const int64_t ptr);
void cj_PAGTextLayer_setFillColor(const int64_t ptr, const int64_t color);
long long cj_PAGTextLayer_font(const int64_t ptr);
void cj_PAGTextLayer_setFont(const int64_t ptr, const int64_t fontptr);
double cj_PAGTextLayer_fontSize(const int64_t ptr);
void cj_PAGTextLayer_setFontSize(const int64_t ptr, double fontSize);
long long cj_PAGTextLayer_strokeColor(const int64_t ptr);
void cj_PAGTextLayer_setStrokeColor(const int64_t ptr, const int64_t color);
char *cj_PAGTextLayer_text(const int64_t ptr);
void cj_PAGTextLayer_setText(const int64_t ptr, char *t);
void cj_PAGTextLayer_reset(const int64_t ptr);
void cj_PAGTextLayer_release(const int64_t ptr);
}
#endif // LIBPAG_CJ_CJ_PAG_LAYER_HANDLE_H
