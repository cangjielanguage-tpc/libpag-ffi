/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H
#define LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H

#include "../../../third_party/tgfx/src/utils/UniqueID.h"
#include "../../external/platform/GPUDrawable.h"
#include "base/utils/TGFXCast.h"
#include "base/utils/TimeUtil.h"
#include "cj_helper.h"
#include "cj_pag_composition.h"
#include "cj_type.h"
#include "rendering/PAGAnimator.h"
#include "rendering/utils/ApplyScaleMode.h"
#include "tgfx/core/ColorType.h"
#include "tgfx/gpu/Surface.h"
#include "tgfx/gpu/Window.h"
#include <EGL/eglplatform.h>
#include <algorithm>
#include <hilog/log.h>
#include <native_window/external_window.h>
#include <pag/pag.h>

extern "C" { // cangjie [PAGImageView] ffi
int64_t cj_PAGImageViewController_createPAGImageView();
void cj_PAGImageViewController_setComposition(const int64_t cjImageView, const int64_t native, double maxFrameRate,
                                              bool isNull);
int cj_PAGImageViewController_scaleMode(const int64_t cjImageView);
void cj_PAGImageViewController_setScaleMode(const int64_t cjImageView, const int32_t scaleMode);
CJFloat32Array cj_PAGImageViewController_matrix(const int64_t cjImageView);
void cj_PAGImageViewController_setMatrix(const int64_t cjImageView, float *bytes);
float cj_PAGImageViewController_renderScale(const int64_t cjImageView);
void cj_PAGImageViewController_setRenderScale(const int64_t cjImageView, float renderScale);
bool cj_PAGImageViewController_cacheAllFramesInMemory(const int64_t cjImageView);
void cj_PAGImageViewController_setCacheAllFramesInMemory(const int64_t cjImageView, bool enable);
int64_t cj_PAGImageViewController_currentFrame(const int64_t cjImageView);
void cj_PAGImageViewController_setCurrentFrame(const int64_t cjImageView, int64_t currentFrame);
CJPixelMap cj_PAGImageViewController_currentImage(const int64_t cjImageView);
void cj_PAGImageViewController_play(const int64_t cjImageView);
bool cj_PAGImageViewController_isPlaying(const int64_t cjImageView);
void cj_PAGImageViewController_pause(const int64_t cjImageView);
int64_t cj_PAGImageViewController_repeatCount(const int64_t cjImageView);
void cj_PAGImageViewController_setRepeatCount(const int64_t cjImageView, const int64_t repeatCount);
bool cj_PAGImageViewController_flush(const int64_t cjImageView);
CJBytesArray cj_PAGImageViewController_uniqueID(const int64_t cjImageView);
void cj_PAGImageViewController_update(const int64_t cjImageView);
void cj_PAGImageViewController_SetSurfaceId(const int64_t cjImageView, int64_t surfaceId);
void cj_PAGImageViewController_ChangeSurface(const int64_t cjImageView);
void cj_PAGImageViewController_release(const int64_t cjImageView);
void cj_PAGImageViewController_destroyJPAGImageView(const char *id);
void cj_PAGImageViewController_matrixFromArray(const int64_t cjImageView, float values[9]);
void cj_PAGImageViewController_setMatrixFromArray(const int64_t cjImageView, float values[9]);
}

namespace pag {
class CJPAGImageView : public PAGAnimator::Listener {
public:
    static inline std::string ClassName() { return "CJPAGImageView"; }
    explicit CJPAGImageView(const std::string &id) : id(std::move(id)) {}
    virtual ~CJPAGImageView() { release(); }
    void onAnimationStart(PAGAnimator *) override;
    void onAnimationCancel(PAGAnimator *) override;
    void onAnimationEnd(PAGAnimator *) override;
    void onAnimationRepeat(PAGAnimator *) override;
    void onAnimationUpdate(PAGAnimator *animator) override;
    std::shared_ptr<PAGAnimator> getAnimator();
    void setCurrentFrame(Frame currentFrame);
    Frame currentFrame();
    void setComposition(std::shared_ptr<PAGComposition> composition, double frameRate);
    void invalidSize();
    void setScaleMode(int scaleMode);
    int scaleMode();
    void setMatrix(const Matrix &matrix);
    Matrix matrix();
    void setRenderScale(float renderScale);
    float renderScale();
    void setCacheAllFramesInMemory(bool cacheAllFramesInMemory);
    bool cacheAllFramesInMemory();
    bool flush();
    CJPixelMap getCurrentPixelMap();
    void create(int64_t surfaceId);
    void release();
    std::string id;
    std::shared_ptr<PAGAnimator> _animator = nullptr;
    NativeWindow *_window = nullptr;
    std::shared_ptr<tgfx::Window> targetWindow = nullptr;
    double _frameRate = 30.0f;
    typedef void (*stateCallback)(uint8_t, int64_t);
    stateCallback playingStateCallback = nullptr;
    typedef void (*progressCallback)(int64_t);
    progressCallback playingProgressCallback = nullptr;
    int64_t g_imageView = 0;

private:
    std::shared_ptr<PAGDecoder> getDecoderInternal();
    void invalidDecoder();
    void refreshMatrixFromScaleMode();
    bool handleFrame(Frame frame);
    std::pair<tgfx::Bitmap, std::shared_ptr<tgfx::Image>> getImage(Frame frame);
    bool present(std::shared_ptr<tgfx::Image> image);
    std::mutex locker;
    int _width = 0;
    int _height = 0;
    float _renderScale = 1.0f;
    int _scaleMode = PAGScaleMode::LetterBox;
    tgfx::Matrix _matrix = tgfx::Matrix::I();
    bool _cacheAllFramesInMemory = false;
    std::shared_ptr<PAGComposition> _composition = nullptr;
    std::shared_ptr<PAGDecoder> _decoder = nullptr;
    std::shared_ptr<tgfx::Image> currentImage = nullptr;
    tgfx::Bitmap currentBitmap;
    std::unordered_map<Frame, std::pair<tgfx::Bitmap, std::shared_ptr<tgfx::Image>>> images;
};
} // namespace pag
#endif // LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H
