/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H
#define LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H

#include <pag/pag.h>
#include "rendering/PAGAnimator.h"
#include "tgfx/gpu/Window.h"
#include "cj_type.h"
#include "cj_pag_composition.h"
#include <hilog/log.h>
#include "base/utils/TGFXCast.h"
#include "base/utils/TimeUtil.h"
#include "cj_helper.h"
#include "rendering/utils/ApplyScaleMode.h"
#include "tgfx/core/ColorType.h"
#include "../../../third_party/tgfx/src/utils/UniqueID.h"

extern "C" {// cangjie [PAGImageView] ffi
int64_t cj_PAGImageViewController_createPAGImageView();
void cj_PAGImageViewController_setComposition(const int64_t cjImageView, const int64_t native, float maxFrameRate);
int cj_PAGImageViewController_scaleMode(const int64_t cjImageView);
void cj_PAGImageViewController_setScaleMode(const int64_t cjImageView, const int32_t scaleMode);
CJFloat32Array cj_PAGImageViewController_matrix(const int64_t cjImageView);
void cj_PAGImageViewController_setMatrix(const int64_t cjImageView, float* bytes);
float cj_PAGImageViewController_renderScale(const int64_t cjImageView);
void cj_PAGImageViewController_setRenderScale(const int64_t cjImageView, double renderScale);
bool cj_PAGImageViewController_cacheAllFramesInMemory(const int64_t cjImageView);
void cj_PAGImageViewController_setCacheAllFramesInMemory(const int64_t cjImageView, bool enable);
double cj_PAGImageViewController_currentFrame(const int64_t cjImageView);
void cj_PAGImageViewController_setCurrentFrame(const int64_t cjImageView, double currentFrame);
CJPixelMap cj_PAGImageViewController_currentImage(const int64_t cjImageView);
void cj_PAGImageViewController_play(const int64_t cjImageView);
bool cj_PAGImageViewController_isPlaying(const int64_t cjImageView);
void cj_PAGImageViewController_pause(const int64_t cjImageView);
int64_t cj_PAGImageViewController_repeatCount(const int64_t cjImageView);
void cj_PAGImageViewController_setRepeatCount(const int64_t cjImageView, const int64_t repeatCount);
bool cj_PAGImageViewController_flush(const int64_t cjImageView);
const char *cj_PAGImageViewController_uniqueID(const int64_t cjImageView);
void cj_PAGImageViewController_update(const int64_t cjImageView);

}

namespace pag {
//class CJPAGImageView : public PAGAnimator::Listener, public XComponentListener {
class CJPAGImageView : public PAGAnimator::Listener {
    public:
        static inline std::string ClassName() {
            return "CJPAGImageView";
        }

        explicit CJPAGImageView(const std::string& id) : id(std::move(id)) {
        }

        virtual ~CJPAGImageView() {
            release();
        }
        void onAnimationStart(PAGAnimator*) override;
        void onAnimationCancel(PAGAnimator*) override;
        void onAnimationEnd(PAGAnimator*) override;
        void onAnimationRepeat(PAGAnimator*) override;
        void onAnimationUpdate(PAGAnimator* animator) override;
        std::shared_ptr<PAGAnimator> getAnimator();

        void setCurrentFrame(Frame currentFrame);
        Frame currentFrame();
        void setComposition(std::shared_ptr<PAGComposition> composition, float frameRate);
        void setScaleMode(int scaleMode);
        int scaleMode();
        void setMatrix(const Matrix& matrix);
        Matrix matrix();
        void setRenderScale(float renderScale);
        float renderScale();
        void setCacheAllFramesInMemory(bool cacheAllFramesInMemory);
        bool cacheAllFramesInMemory();
        bool flush();

        CJPixelMap getCurrentPixelMap();

        void release();
        std::string id;

        //如果后续传入函数，需要处理。    

        std::shared_ptr<PAGAnimator> _animator = nullptr;

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
        float _frameRate = 30.0f;
        int _scaleMode = PAGScaleMode::LetterBox;
        tgfx::Matrix _matrix = tgfx::Matrix::I();
        bool _cacheAllFramesInMemory = false;
        std::shared_ptr<PAGComposition> _composition = nullptr;

        std::shared_ptr<PAGDecoder> _decoder = nullptr;

        //TODO: ohos的 SystemCapability.Graphic.Graphic2D.NativeWindow，是否替换成 cj的 ohos.window.* ？？？
        std::shared_ptr<tgfx::Window> targetWindow = nullptr;

        std::shared_ptr<tgfx::Image> currentImage = nullptr;
        tgfx::Bitmap currentBitmap;

        std::unordered_map<Frame, std::pair<tgfx::Bitmap, std::shared_ptr<tgfx::Image>>> images;
};
}

#endif //LIBPAG4CJ_CJ_PAG_IMAGE_VIEW_H
