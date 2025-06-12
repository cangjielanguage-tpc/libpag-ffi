/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_image_view.h"

namespace pag {
extern "C" {
static std::unordered_map<std::string, std::shared_ptr<CJPAGImageView>> ViewMap = {};
typedef void (*stateCallback)(uint8_t);
static stateCallback playingStateCallback = NULL;
typedef void (*progressCallback)(int64_t);
static progressCallback playingProgressCallback = NULL;
int64_t totalFrame = 0;

void CJPAGImageView::onAnimationStart(PAGAnimator *) {
    if (playingStateCallback) {
        playingStateCallback(0);
    }
}
void CJPAGImageView::onAnimationCancel(PAGAnimator *) {
    if (playingStateCallback) {
        playingStateCallback(1);
    }
}
void CJPAGImageView::onAnimationEnd(PAGAnimator *) {
    if (playingStateCallback) {
        playingStateCallback(2);
    }
}
void CJPAGImageView::onAnimationRepeat(PAGAnimator *) {
    if (playingStateCallback) {
        playingStateCallback(3);
    }
}

void CJPAGImageView::onAnimationUpdate(PAGAnimator *animator) {
    if (playingProgressCallback) {
        auto targetFrame = ProgressToFrame(animator->progress(), totalFrame);
        playingProgressCallback(targetFrame);
    }
    Frame frame = 0;
    auto decoder = getDecoderInternal();
    if (_composition != nullptr && decoder != nullptr) {
        frame = ProgressToFrame(animator->progress(), _decoder->numFrames());
    }
    handleFrame(frame);
}

int64_t cj_PAGImageViewController_createPAGImageView() {
    // 生成唯一 ID
    const std::string id = "PAGImageView" + std::to_string(tgfx::UniqueID::Next());

    // 创建 shared_ptr 并保存到全局映射（防止对象被销毁）
    auto cView = std::make_shared<CJPAGImageView>(id);
    cView->_animator = PAGAnimator::MakeFrom(cView);
    
    ViewMap.emplace(id, cView); // 假设 ViewMap 是全局的 std::map

    // 返回原始指针（转换为 int64_t）
    return reinterpret_cast<int64_t>(cView.get());
}

void cj_PAGImageViewController_setComposition(const int64_t cjImageView, const int64_t native, float maxFrameRate)
{
    if (cjImageView == 0 || native == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGImageViewController]", "[setComposition]---CJImageView: %{public}ld, CJPAGLayerHandle: %{public}ld", cjImageView, native);
        return;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view == nullptr) {
        return;
    }
    
    CJPAGLayerHandle* cjPAGLayerHandle;
    cjPAGLayerHandle = (CJPAGLayerHandle*)native;
    std::shared_ptr<pag::PAGLayer> layer = cjPAGLayerHandle->get();
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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view != nullptr) {
        view->setScaleMode(scaleMode);
    }
    return;
}

CJFloat32Array cj_PAGImageViewController_matrix(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_matrix", "Pointer is null");
        return {};
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    auto matrix = Matrix::I();
    if (view != nullptr) {
        matrix = view->matrix();
    }
    float* buf = CreateMatrix(matrix);
    return CJFloat32Array{9, buf};
}

void cj_PAGImageViewController_setMatrix(const int64_t cjImageView, float* bytes)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setMatrix", "Pointer is null");
        return;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view != nullptr) {
        view->setMatrix(GetMatrix(bytes));
    }
    return;
}

float cj_PAGImageViewController_renderScale(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_renderScale", "Pointer is null");
        return -1.0;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view != nullptr) {
        return view->renderScale();
    }
    return -1.0;
}

void cj_PAGImageViewController_setRenderScale(const int64_t cjImageView, double renderScale)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setRenderScale", "Pointer is null");
        return;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    double value = renderScale;
    if (renderScale < 0.0 || renderScale > 1.0) {
        value = 1.0f;
    }
    if (view != nullptr) {
        view->setRenderScale(value);
    }
}

bool cj_PAGImageViewController_cacheAllFramesInMemory(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_cacheAllFramesInMemory", "Pointer is null");
        return false;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    bool cacheAllFramesInMemory = false;
    if (view != nullptr) {
        cacheAllFramesInMemory = view->cacheAllFramesInMemory();
    }
    return cacheAllFramesInMemory;
}

void cj_PAGImageViewController_setCacheAllFramesInMemory(const int64_t cjImageView, bool enable)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setCacheAllFramesInMemory", "Pointer is null");
        return;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view != nullptr) {
        view->setCacheAllFramesInMemory(enable);
    }
}

double cj_PAGImageViewController_currentFrame(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_currentFrame", "Pointer is null");
        return 0.0; 
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    int64_t currentFrame = 0;
    if (view != nullptr) {
        currentFrame = view->currentFrame();
    }
    return currentFrame;
}

void cj_PAGImageViewController_setCurrentFrame(const int64_t cjImageView, double currentFrame)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_setCurrentFrame", "Pointer is null");
        return; 
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;
    if (view != nullptr) {
        view->setCurrentFrame(currentFrame);
    }
}

CJPixelMap cj_PAGImageViewController_currentImage(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_currentImage", "Pointer is null");
        return {}; 
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

    if (view != nullptr) {
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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

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
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

    bool flushResult = false;
    if (view != nullptr) {
        flushResult = view->flush();
    }
    return flushResult;
}

const char *cj_PAGImageViewController_uniqueID(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_uniqueID", "Pointer is null");
        return "";
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

    if (view == nullptr) {
        return nullptr;
    }
    std::string id = view->id;
    char *uniqueID = pag::cj_string_To_UTF8((char *)id.c_str(),"ISO-8859-1");
    return uniqueID;
}

void cj_PAGImageViewController_update(const int64_t cjImageView)
{
    if (cjImageView == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGImageViewController_update", "Pointer is null");
        return;
    }
    CJPAGImageView* view;
    view = (CJPAGImageView*)cjImageView;

    if (view != nullptr) {
        auto animator = view->getAnimator();
        if (animator) {
            animator->update();
        }
    }
}


std::shared_ptr<PAGDecoder> CJPAGImageView::getDecoderInternal() {
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

void CJPAGImageView::invalidDecoder() {
    _decoder = nullptr;
    images.clear();
}

std::shared_ptr<PAGAnimator> CJPAGImageView::getAnimator() {
    std::lock_guard lock_guard(locker);
    return _animator;
}

void CJPAGImageView::setCurrentFrame(Frame currentFrame) {
    std::lock_guard lock_guard(locker);
    if (_animator == nullptr || _composition == nullptr || _decoder == nullptr) {
        return;
    }
    _animator->setProgress(FrameToProgress(currentFrame, _decoder->numFrames()));
}

Frame CJPAGImageView::currentFrame() {
    std::lock_guard lock_guard(locker);
    if (_animator == nullptr || _decoder == nullptr) {
        return 0;
    }
    return ProgressToFrame(_animator->progress(), _decoder->numFrames());
}

void CJPAGImageView::setComposition(std::shared_ptr<PAGComposition> composition, float frameRate) {
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

void CJPAGImageView::setScaleMode(int scaleMode) {
    std::lock_guard lock_guard(locker);
    _scaleMode = scaleMode;
    refreshMatrixFromScaleMode();
}

int CJPAGImageView::scaleMode() {
    return _scaleMode;
}

void CJPAGImageView::setMatrix(const class Matrix& matrix) {
    std::lock_guard lock_guard(locker);
    _matrix = ToTGFX(matrix);
    _scaleMode = PAGScaleMode::None;
}

class Matrix CJPAGImageView::matrix() {
    std::lock_guard lock_guard(locker);
    return ToPAG(_matrix);
}

void CJPAGImageView::setRenderScale(float renderScale) {
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

float CJPAGImageView::renderScale() {
    return _renderScale;
}

void CJPAGImageView::setCacheAllFramesInMemory(bool cacheAllFramesInMemory) {
    std::lock_guard lock_guard(locker);
    if (_cacheAllFramesInMemory == cacheAllFramesInMemory) {
        return;
    }
    _cacheAllFramesInMemory = cacheAllFramesInMemory;
    if (!_cacheAllFramesInMemory) {
        images.clear();
    }
}

bool CJPAGImageView::cacheAllFramesInMemory() {
  return _cacheAllFramesInMemory;
}

bool CJPAGImageView::flush() {
    std::lock_guard lock_guard(locker);
    auto decoder = getDecoderInternal();
    if (decoder && _animator) {
        return handleFrame(ProgressToFrame(_animator->progress(), decoder->numFrames()));
    }
    return false;
}

void CJPAGImageView::refreshMatrixFromScaleMode() {
    if (_scaleMode == PAGScaleMode::None) {
        return;
    }
    if (_decoder == nullptr) {
        return;
    }

    _matrix = ToTGFX(ApplyScaleMode(_scaleMode, _decoder->width() / _renderScale,
                                    _decoder->height() / _renderScale, _width, _height));
}

bool CJPAGImageView::handleFrame(Frame frame) {
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

std::pair<tgfx::Bitmap, std::shared_ptr<tgfx::Image>> CJPAGImageView::getImage(Frame frame) {
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

bool CJPAGImageView::present(std::shared_ptr<tgfx::Image> image) {
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


CJPixelMap CJPAGImageView::getCurrentPixelMap() {
    std::lock_guard lock_guard(locker);
    if (currentBitmap.isEmpty()) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }

    //把 create PixelMap 移到 cangjie 代码中。
    // create PixelMap
    int32_t width = currentBitmap.width();
    int32_t height = currentBitmap.height();
    uint8_t pixelFormat = currentBitmap.colorType() == tgfx::ColorType::RGBA_8888
                          ? 2 // PIXEL_FORMAT_RGBA_8888
                          : 3; // PIXEL_FORMAT_BGRA_8888;
    uint8_t alphaType = 2; //OHOS_PIXEL_MAP_ALPHA_TYPE_PREMUL;
    bool editable = false;

    /*
     * 使用指定的ImageInfo将一个整数像素复制到 dstPixels。复制从 (srcX，srcY) 开始，并且不超过位图（width()，height()）。
     * 仅当像素转换可行时，才会复制像素。如果像素被复制到 dstPixels，则返回true。
     * bool readPixels(const ImageInfo& dstInfo, void* dstPixels, int srcX = 0, int srcY = 0) const;
    */
    void* pixelMapAddress = nullptr;
    bool flag = currentBitmap.readPixels(currentBitmap.info(), pixelMapAddress);
    if (!flag) {
        return CJPixelMap{0, nullptr, alphaType, editable, pixelFormat, height, width};
    }
    
    //返回像素的字节大小。
    int size = currentBitmap.byteSize();
    //返回像素的行字节数。

    auto bytes = reinterpret_cast<const uint8_t*>(pixelMapAddress);
    uint8_t* buf = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        buf[i] = bytes[i];
    }

    return CJPixelMap{size, buf, alphaType, editable, pixelFormat, height, width};
}

void CJPAGImageView::release() {
    std::lock_guard lock_guard(locker);
    //TODO：如果后续传入函数，需要处理。
    if (_animator) {
        _animator = nullptr;
    }

    invalidDecoder();
}
}
}
