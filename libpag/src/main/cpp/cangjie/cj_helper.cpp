/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_helper.h"

namespace pag {
extern "C" {
CJMarker *CreateMarker(const Marker *marker)
{
    if (marker == nullptr) {
        return nullptr;
    }
    CJMarker *result = new CJMarker();
    long long startTime = marker->startTime;
    long long duration = marker->duration;
    std::string commentStr = marker->comment;
    result->mStartTime = startTime;
    result->mDuration = duration;
    result->mComment = stringToCJBytesArray(commentStr);
    return result;
}

CJMarker *CreateMarkers(const std::vector<const Marker *> &markers)
{
    CJMarker *result = new CJMarker[markers.size()];
    if (result == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "Init", "[CreateMarkers]-new CJMarker fail.");
        return nullptr;
    }

    for (size_t i = 0; i < markers.size(); i++) {
        auto jsMarker = CreateMarker(markers[i]);
        if (jsMarker == nullptr) {
            return nullptr;
        }
        result[i] = *jsMarker;
    }
    return result;
}

float *CreateRect(const Rect &rect)
{
    constexpr int RECT_LEFT_INDEX = 0;
    constexpr int RECT_TOP_INDEX = 1;
    constexpr int RECT_RIGHT_INDEX = 2;
    constexpr int RECT_BOTTOM_INDEX = 3;
    constexpr int RECT_SIZE = 4;
    float *arr = new float[RECT_SIZE];
    arr[RECT_LEFT_INDEX] = rect.left;
    arr[RECT_TOP_INDEX] = rect.top;
    arr[RECT_RIGHT_INDEX] = rect.right;
    arr[RECT_BOTTOM_INDEX] = rect.bottom;
    return arr;
}

float *CreateMatrix(const Matrix &matrix)
{
    constexpr int MATRIX_SIZE = 9;
    std::array<float, MATRIX_SIZE> buffer{};
    matrix.get9(buffer.data());
    float *res = new float[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        res[i] = buffer[i];
    }
    return res;
}

Matrix GetMatrix(float *bytes)
{
    if (bytes == nullptr) {
        return {};
    }
    constexpr int MATRIX_SIZE = 9;
    Matrix result;
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        float val = 0;
        val = bytes[i];
        result.set(i, val);
    }
    return result;
}

CJPixelMap MakeSnapshot(std::shared_ptr<PAGSurface> surface)
{
    if (surface == nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    tgfx::ImageInfo imageInfo = tgfx::ImageInfo::Make(surface->width(), surface->height(), tgfx::ColorType::BGRA_8888);
    auto pixels = ByteData::Make(imageInfo.byteSize());
    if (pixels == nullptr) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    if (!surface->readPixels(ColorType::BGRA_8888, AlphaType::Premultiplied, pixels->data(), imageInfo.rowBytes())) {
        return CJPixelMap{0, nullptr, 0, false, 0, 0, 0};
    }
    int32_t width = imageInfo.width();
    int32_t height = imageInfo.height();
    uint8_t pixelFormat = 3; // PIXEL_FORMAT_BGRA_8888;
    uint8_t alphaType = 2; // OHOS_PIXEL_MAP_ALPHA_TYPE_PREMUL;
    bool editable = true;

    uint8_t *bytes = pixels->data();
    // Return the byte size of the pixel.
    int size = pixels->length();

    uint8_t *buf = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        buf[i] = bytes[i];
    }
    return CJPixelMap{size, buf, alphaType, editable, pixelFormat, height, width};
}

long long MakeColorInt(uint32_t red, uint32_t green, uint32_t blue)
{
    uint32_t color = (uint32_t(255) << 24) | (red << 16) | (green << 8) | (blue << 0);
    return static_cast<long long>(color);
}

Color ToColor(int value)
{
    auto color = static_cast<uint32_t>(value);
    auto red = (((color) >> 16) & 0xFF);
    auto green = (((color) >> 8) & 0xFF);
    auto blue = (((color) >> 0) & 0xFF);
    return {static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
}

CJPAGVideoRange *CreateVideoRange(const PAGVideoRange &videoRange)
{
    CJPAGVideoRange *result = new CJPAGVideoRange();

    long long startTime = videoRange.startTime();
    long long endTime = videoRange.endTime();
    long long playDuration = videoRange.playDuration();
    bool reversed = videoRange.reversed();

    result->startTime = startTime;
    result->endTime = endTime;
    result->playDuration = playDuration;
    result->reversed = reversed;

    return result;
}

CJPAGVideoRange *CreateVideoRanges(const std::vector<PAGVideoRange> &videoRanges)
{
    CJPAGVideoRange *result = new CJPAGVideoRange[videoRanges.size()];
    if (result == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "Init", "[CreateVideoRanges]-new CJPAGVideoRange fail.");
        return nullptr;
    }
    for (size_t i = 0; i < videoRanges.size(); i++) {
        auto pagVideoRange = CreateVideoRange(videoRanges[i]);
        if (pagVideoRange == nullptr) {
            return nullptr;
        }
        result[i] = *pagVideoRange;
    }
    return result;
}

void safe_copy(void *dest, uint32_t dest_size, const void *src, uint32_t src_size)
{
    if (!dest || !src) {
        throw std::invalid_argument("safe_copy null pointer passed to safe_copy.");
    }
    if (dest_size < src_size) {
        throw std::runtime_error("safe_copy insufficient space in the target buffer.");
    }
    uint8_t *dest_ptr = static_cast<uint8_t *>(dest);
    const uint8_t *src_ptr = static_cast<const uint8_t *>(src);
    for (uint32_t i = 0; i < src_size; ++i) {
        dest_ptr[i] = src_ptr[i];
    }
}
}

CJBytesArray stringToCJBytesArray(const std::string &str)
{
    CJBytesArray result;
    if (str.empty()) {
        return {0, nullptr};
    }
    result.size = static_cast<int64_t>(str.size());
    result.buf = static_cast<uint8_t *>(malloc(result.size));
    if (result.buf == nullptr) {
        throw std::bad_alloc();
    }
    safe_copy(result.buf, static_cast<uint32_t>(result.size), str.data(), static_cast<uint32_t>(result.size));
    return result;
}

std::string CJBytesArraytoString(const CJBytesArray &bytes)
{
    if (bytes.buf == nullptr || bytes.size <= 0) {
        return "";
    }
    return std::string(reinterpret_cast<const char *>(bytes.buf), bytes.size);
}
} // namespace pag
