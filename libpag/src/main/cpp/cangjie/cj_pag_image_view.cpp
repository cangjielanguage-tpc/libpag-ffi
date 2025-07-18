/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_image_view.h"

namespace pag {
extern "C" {
static std::unordered_map<std::string, std::shared_ptr<CJPAGImageView>> ImageViewMap = {};

void CJPAGImageView::onAnimationStart(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Start), g_imageView);
    }
}

void CJPAGImageView::onAnimationCancel(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Cancel), g_imageView);
    }
}

void CJPAGImageView::onAnimationEnd(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::End), g_imageView);
    }
}

void CJPAGImageView::onAnimationRepeat(PAGAnimator *)
{
    std::lock_guard lock_guard(locker);
    if (playingStateCallback) {
        playingStateCallback(static_cast<int>(AnimationState::Repeat), g_imageView);
    }
}

void CJPAGImageView::onAnimationUpdate(PAGAnimator *animator)
{
    std::lock_guard lock_guard(locker);
    if (playingProgressCallback) {
        playingProgressCallback(g_imageView);
    }
    Frame frame = 0;
    auto decoder = getDecoderInternal();
    if (_composition != nullptr && decoder != nullptr) {
        frame = ProgressToFrame(animator->progress(), _decoder->numFrames());
    }
    handleFrame(frame);
}

void cj_PAGImageViewController_onAnimatorStateChange(const int64_t cjImageView,
                                                     CJPAGImageView::stateCallback callback)
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_onAnimatorStateChange", "view is null");
        return;
    }
    view->g_imageView = cjImageView;
    view->playingStateCallback = callback;
}

void cj_PAGImageViewController_onAnimatorProgress(const int64_t cjImageView,
                                                  CJPAGImageView::progressCallback callback)
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_onAnimatorProgress", "view is null");
        return;
    }
    view->g_imageView = cjImageView;
    view->playingProgressCallback = callback;
}

void CJPAGImageView::invalidSize()
{
    if (targetWindow && _window) {
        targetWindow->invalidSize();
        OH_NativeWindow_NativeWindowHandleOpt(_window, GET_BUFFER_GEOMETRY, &_height, &_width);
    } else {
        _width = 0;
        _height = 0;
    }
    invalidDecoder();
}

void cj_PAGImageViewController_SetSurfaceId(const int64_t cjImageView, int64_t surfaceId)
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_SetSurfaceId", "view is null");
        return;
    }
    view->create(surfaceId);
}

void cj_PAGImageViewController_ChangeSurface(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_ChangeSurface", "view is null");
        return;
    }
    view->invalidSize();
}

int64_t cj_PAGImageViewController_createPAGImageView()
{
    std::string id = "PAGImageView" + std::to_string(tgfx::UniqueID::Next());
    auto imageView = std::make_shared<CJPAGImageView>(id);
    imageView->_animator = PAGAnimator::MakeFrom(imageView);
    ImageViewMap.emplace(id, imageView);
    return reinterpret_cast<int64_t>(imageView.get());
}

void cj_PAGImageViewController_destroyJPAGImageView(const char *id)
{
    if (id == nullptr || id[0] == '\0') {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_destroyJPAGView",
                     "id is null or empty.");
        return;
    }
    ImageViewMap.erase(id);
}

void cj_PAGImageViewController_setComposition(const int64_t cjImageView, const int64_t native, double maxFrameRate,
                                              bool isNull)
{
    if (cjImageView == 0 || native == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageViewController]",
                     "[setComposition]---CJImageView: %{public}ld, CJPAGLayerHandle: %{public}ld", cjImageView, native);
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view == nullptr) {
        return;
    }
    intptr_t nativeInt = static_cast<intptr_t>(native);
    CJPAGLayerHandle *cjPAGLayerHandle = reinterpret_cast<CJPAGLayerHandle *>(nativeInt);
    std::shared_ptr<pag::PAGLayer> layer = cjPAGLayerHandle->get();
    if (isNull) {
        view->setComposition(nullptr, 30.0f);
        return;
    }
    if (layer && layer->layerType() == LayerType::PreCompose) {
        std::shared_ptr<pag::PAGComposition> pagComposition = std::static_pointer_cast<PAGComposition>(layer);
        view->setComposition(pagComposition, maxFrameRate);
    } else {
        view->setComposition(nullptr, 30.0f);
    }
}

int cj_PAGImageViewController_scaleMode(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_scaleMode", "Pointer is null");
        return 0;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    int scaleMode = PAGScaleMode::LetterBox;
    if (view != nullptr) {
        scaleMode = view->scaleMode();
    }
    return scaleMode;
}

void cj_PAGImageViewController_setScaleMode(const int64_t cjImageView, const int32_t scaleMode)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setScaleMode", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        view->setScaleMode(scaleMode);
    }
    return;
}

CJFloat32Array cj_PAGImageViewController_matrix(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_matrix", "Pointer is null");
        return {0, nullptr};
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    auto matrix = Matrix::I();
    if (view != nullptr) {
        matrix = view->matrix();
    }
    float *buf = CreateMatrix(matrix);
    return CJFloat32Array{9, buf};
}

void cj_PAGImageViewController_matrixFromArray(const int64_t cjImageView, float values[9])
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_matrixFromArray", "Pointer is null");
        return;
    }
    auto matrix = Matrix::I();
    if (view != nullptr) {
        matrix = view->matrix();
        matrix.get9(values);
    }
}

void cj_PAGImageViewController_setMatrix(const int64_t cjImageView, float *bytes)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setMatrix", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        view->setMatrix(GetMatrix(bytes));
    }
    return;
}

void cj_PAGImageViewController_setMatrixFromArray(const int64_t cjImageView, float values[9])
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setMatrixFromArray", "Pointer is null");
        return;
    }
    if (view != nullptr) {
        Matrix matrix = {};
        float scaleX = values[0];
        float skewX = values[1];
        float transX = values[2];
        float skewY = values[3];
        float scaleY = values[4];
        float transY = values[5];
        constexpr float MATRIX_HX = 0.0f;
        constexpr float MATRIX_HY = 0.0f;
        constexpr float MATRIX_W = 1.0f;
        matrix.setAll(scaleX, skewX, transX, skewY, scaleY, transY, MATRIX_HX, MATRIX_HY, MATRIX_W);
        view->setMatrix(matrix);
    }
}

float cj_PAGImageViewController_renderScale(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_renderScale", "Pointer is null");
        return 1.0f;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        return view->renderScale();
    }
    return 1.0f;
}

void cj_PAGImageViewController_setRenderScale(const int64_t cjImageView, float renderScale)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setRenderScale", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        view->setRenderScale(renderScale);
    }
}

bool cj_PAGImageViewController_cacheAllFramesInMemory(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_cacheAllFramesInMemory",
                     "Pointer is null");
        return false;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    bool cacheAllFramesInMemory = false;
    if (view != nullptr) {
        cacheAllFramesInMemory = view->cacheAllFramesInMemory();
    }
    return cacheAllFramesInMemory;
}

void cj_PAGImageViewController_setCacheAllFramesInMemory(const int64_t cjImageView, bool enable)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setCacheAllFramesInMemory",
                     "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        view->setCacheAllFramesInMemory(enable);
    }
}

int64_t cj_PAGImageViewController_currentFrame(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_currentFrame", "Pointer is null");
        return 0.0;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    int64_t currentFrame = 0;
    if (view != nullptr) {
        currentFrame = view->currentFrame();
    }
    return currentFrame;
}

void cj_PAGImageViewController_setCurrentFrame(const int64_t cjImageView, int64_t currentFrame)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setCurrentFrame", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (view != nullptr) {
        view->setCurrentFrame(currentFrame);
    }
}

CJPixelMap cj_PAGImageViewController_currentImage(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_currentImage", "Pointer is null");
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view == nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    return view->getCurrentPixelMap();
}

void cj_PAGImageViewController_play(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_play", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator) {
            animator->start();
        }
    }
}

bool cj_PAGImageViewController_isPlaying(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_isPlaying", "Pointer is null");
        return false;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    bool isPlaying = false;
    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator != nullptr) {
            isPlaying = animator->isRunning();
        }
    }
    return isPlaying;
}

void cj_PAGImageViewController_pause(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_pause", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator) {
            animator->cancel();
        }
    }
}

int64_t cj_PAGImageViewController_repeatCount(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_repeatCount", "Pointer is null");
        return 0;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    int64_t repeatCount = 0;
    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator != nullptr) {
            repeatCount = animator->repeatCount();
        }
    }
    return repeatCount;
}

void cj_PAGImageViewController_setRepeatCount(const int64_t cjImageView, const int64_t repeatCount)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setRepeatCount", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator) {
            animator->setRepeatCount(repeatCount);
        }
    }
}

bool cj_PAGImageViewController_flush(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_flush", "Pointer is null");
        return false;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    bool flushResult = false;
    if (view != nullptr) {
        flushResult = view->flush();
    }
    return flushResult;
}

CJBytesArray cj_PAGImageViewController_uniqueID(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_uniqueID", "Pointer is null");
        return {0, nullptr};
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view == nullptr) {
        return {0, nullptr};
    }
    std::string id = view->id;
    CJBytesArray uniqueID = stringToCJBytesArray(id);
    return uniqueID;
}

void cj_PAGImageViewController_update(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_update", "Pointer is null");
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);

    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator) {
            animator->update();
        }
    }
}

void cj_PAGImageViewController_release(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        return;
    }
    intptr_t cjImageViewInt = static_cast<intptr_t>(cjImageView);
    CJPAGImageView *view = reinterpret_cast<CJPAGImageView *>(cjImageViewInt);
    if (!view) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_release", "imageview is null");
        return;
    }
    view->release();
}

std::shared_ptr<PAGDecoder> CJPAGImageView::getDecoderInternal()
{
    if (targetWindow == nullptr || _composition == nullptr) {
        invalidDecoder();
        return nullptr;
    }
    if (_decoder == nullptr) {
        float scaleFactor = 1.0;
        if (_width >= _height) {
            scaleFactor = static_cast<float>(_renderScale * (_width * 1.0 / _composition->width()));
        } else {
            scaleFactor = static_cast<float>(_renderScale * (_height * 1.0 / _composition->height()));
        }
        _decoder = PAGDecoder::MakeFrom(_composition, _frameRate, scaleFactor);
        refreshMatrixFromScaleMode();
    }
    return _decoder;
}

void CJPAGImageView::invalidDecoder()
{
    _decoder = nullptr;
    images.clear();
}

std::shared_ptr<PAGAnimator> CJPAGImageView::getAnimator()
{
    std::lock_guard lock_guard(locker);
    return _animator;
}

void CJPAGImageView::setCurrentFrame(Frame currentFrame)
{
    std::lock_guard lock_guard(locker);
    if (_animator == nullptr || _composition == nullptr || _decoder == nullptr) {
        return;
    }
    _animator->setProgress(FrameToProgress(currentFrame, _decoder->numFrames()));
}

Frame CJPAGImageView::currentFrame()
{
    std::lock_guard lock_guard(locker);
    if (_animator == nullptr || _decoder == nullptr) {
        return 0;
    }
    return ProgressToFrame(_animator->progress(), _decoder->numFrames());
}

void CJPAGImageView::setComposition(std::shared_ptr<PAGComposition> composition, double frameRate)
{
    std::lock_guard lock_guard(locker);
    if (_animator == nullptr) {
        return;
    }
    if (composition != nullptr) {
        _animator->setDuration(composition->duration());
    } else {
        _animator->setDuration(0);
    }
    _composition = composition;
    _frameRate = frameRate;
    invalidDecoder();
}

void CJPAGImageView::setScaleMode(int scaleMode)
{
    std::lock_guard lock_guard(locker);
    _scaleMode = scaleMode;
    refreshMatrixFromScaleMode();
}

int CJPAGImageView::scaleMode() { return _scaleMode; }

void CJPAGImageView::setMatrix(const class Matrix &matrix)
{
    std::lock_guard lock_guard(locker);
    _matrix = ToTGFX(matrix);
    _scaleMode = PAGScaleMode::None;
}

class Matrix CJPAGImageView::matrix()
{
    std::lock_guard lock_guard(locker);
    return ToPAG(_matrix);
}

void CJPAGImageView::setRenderScale(float renderScale)
{
    std::lock_guard lock_guard(locker);
    if (renderScale <= 0.0 || renderScale > 1.0) {
        renderScale = 1.0;
    }
    if (_renderScale == renderScale) {
        return;
    }
    _renderScale = renderScale;
    invalidDecoder();
}

float CJPAGImageView::renderScale() { return _renderScale; }

void CJPAGImageView::setCacheAllFramesInMemory(bool cacheAllFramesInMemory)
{
    std::lock_guard lock_guard(locker);
    if (_cacheAllFramesInMemory == cacheAllFramesInMemory) {
        return;
    }
    _cacheAllFramesInMemory = cacheAllFramesInMemory;
    if (!_cacheAllFramesInMemory) {
        images.clear();
    }
}

bool CJPAGImageView::cacheAllFramesInMemory() { return _cacheAllFramesInMemory; }

bool CJPAGImageView::flush()
{
    std::lock_guard lock_guard(locker);
    auto decoder = getDecoderInternal();
    if (decoder && _animator) {
        return handleFrame(ProgressToFrame(_animator->progress(), decoder->numFrames()));
    }
    return false;
}

void CJPAGImageView::refreshMatrixFromScaleMode()
{
    if (_scaleMode == PAGScaleMode::None) {
        return;
    }
    if (_decoder == nullptr) {
        return;
    }
    _matrix = ToTGFX(ApplyScaleMode(_scaleMode, _decoder->width() / _renderScale, _decoder->height() / _renderScale,
                                    _width, _height));
}

bool CJPAGImageView::handleFrame(Frame frame)
{
    auto decoder = getDecoderInternal();
    if (!decoder) {
        return false;
    }
    if (!decoder->checkFrameChanged(frame)) {
        return true;
    }
    auto image = getImage(frame);
    if (!image.second) {
        return false;
    }
    currentBitmap = image.first;
    currentImage = image.second;
    return present(currentImage);
}

std::pair<tgfx::Bitmap, std::shared_ptr<tgfx::Image>> CJPAGImageView::getImage(Frame frame)
{
    if (_cacheAllFramesInMemory && images.find(frame) != images.end()) {
        return images[frame];
    }
    tgfx::Bitmap bitmap;
    if (!bitmap.allocPixels(_decoder->width(), _decoder->height(), false, false)) {
        return {{}, nullptr};
    }
    auto pixels = bitmap.lockPixels();
    if (pixels == nullptr) {
        return {{}, nullptr};
    }
    _decoder->readFrame(frame, pixels, bitmap.rowBytes());
    bitmap.unlockPixels();
    auto image = tgfx::Image::MakeFrom(bitmap);
    if (image == nullptr) {
        return {{}, nullptr};
    }
    if (_cacheAllFramesInMemory) {
        images[frame] = {bitmap, image};
    }
    return {bitmap, image};
}

bool CJPAGImageView::present(std::shared_ptr<tgfx::Image> image)
{
    if (!targetWindow && image) {
        return false;
    }
    auto device = targetWindow->getDevice();
    if (!device) {
        return false;
    }
    auto context = device->lockContext();
    if (!context) {
        return false;
    }
    auto surface = targetWindow->getSurface(context, true);
    if (surface == nullptr) {
        surface = targetWindow->getSurface(context, false);
    }
    if (!surface) {
        device->unlock();
        return false;
    }
    auto canvas = surface->getCanvas();
    if (!canvas) {
        device->unlock();
        return false;
    }
    canvas->clear();
    tgfx::Matrix imageMatrix = tgfx::Matrix::MakeScale(1.0 / _renderScale);
    imageMatrix.postConcat(_matrix);
    canvas->drawImage(image, imageMatrix);
    surface->flush();
    context->submit();
    targetWindow->present(context);
    context->purgeResourcesNotUsedSince(std::chrono::steady_clock::now());
    device->unlock();
    return true;
}

CJPixelMap CJPAGImageView::getCurrentPixelMap()
{
    constexpr uint8_t ALPHA_TYPE_OPAQUE = 2;
    constexpr uint8_t PIXEL_FORMAT_RGBA_8888 = 2;
    constexpr uint8_t PIXEL_FORMAT_BGRA_8888 = 3;
    constexpr int BYTES_PER_PIXEL = 4;
    std::lock_guard lock_guard(locker);
    if (currentBitmap.isEmpty()) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    int32_t width = currentBitmap.width();
    int32_t height = currentBitmap.height();
    int size = currentBitmap.byteSize();
    tgfx::ColorType colorType = currentBitmap.colorType();
    uint8_t pixelFormat = PIXEL_FORMAT_RGBA_8888;
    uint8_t alphaType = ALPHA_TYPE_OPAQUE;
    bool editable = false;
    uint8_t *buf = new uint8_t[size];
    void *pixels = currentBitmap.lockPixels();
    if (pixels != nullptr) {
        std::copy(static_cast<uint8_t *>(pixels), static_cast<uint8_t *>(pixels) + size, buf);
        currentBitmap.unlockPixels();
        currentBitmap.unlockPixels();
        constexpr int RGBA_CHANNEL_B_INDEX = 2;
        if (colorType == tgfx::ColorType::RGBA_8888) {
            // Convert RGBA to BGRA (every 4 bytes is one pixel)
            for (int i = 0; i < size; i += BYTES_PER_PIXEL) {
                std::swap(buf[i], buf[i + RGBA_CHANNEL_B_INDEX]); // R ↔ B
            }
            pixelFormat = PIXEL_FORMAT_BGRA_8888;
        }
        return CJPixelMap{size, buf, alphaType, editable, pixelFormat, height, width};
    } else {
        delete[] buf;
        currentBitmap.unlockPixels();
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
}

void CJPAGImageView::create(int64_t surfaceId)
{
    std::lock_guard lock_guard(locker);
    OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &_window);
    targetWindow = tgfx::EGLWindow::MakeFrom(reinterpret_cast<EGLNativeWindowType>(_window));
    invalidSize();
    _animator->update();
}

void CJPAGImageView::release()
{
    std::lock_guard lock_guard(locker);
    OH_NativeWindow_DestroyNativeWindow(_window);
    if (playingProgressCallback) {
        playingProgressCallback = nullptr;
    }
    if (playingStateCallback) {
        playingStateCallback = nullptr;
    }
    if (_animator) {
        _animator = nullptr;
    }
    invalidDecoder();
}
}
} // namespace pag
