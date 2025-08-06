/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_file.h"

namespace pag {
extern "C" {
uint32_t cj_PAGFile_MaxSupportedTagLevel() { return pag::PAGFile::MaxSupportedTagLevel(); }

int64_t cj_PAGFile_LoadFromPath(const char *path)
{
    if (path == nullptr || path[0] == '\0') {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromPath", "Path is null or empty.");
        return 0;
    }
    std::shared_ptr<PAGFile> surface = PAGFile::Load(path);
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromPath", "Failed to load PAGFile.");
        return 0;
    }
    try {
        CJPAGLayerHandle *handler = new CJPAGLayerHandle(surface);
        return (int64_t)handler;
    } catch (const std::bad_alloc &) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromPath", "Memory allocation failed.");
        return 0;
    }
}

int64_t cj_PAGFile_LoadFromBytes(uint8_t *bytes, size_t length, const char *path)
{
    if (bytes == NULL || length == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromBytes",
                     "Input bytes is NULL or length is zero.");
        return 0;
    }
    std::shared_ptr<PAGFile> surface = PAGFile::Load(bytes, length, path);
    if (!surface) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromBytes", "Failed to load PAGFile from bytes.");
        return 0;
    }
    try {
        CJPAGLayerHandle *handler = new CJPAGLayerHandle(surface);
        return (int64_t)handler;
    } catch (const std::bad_alloc &) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_LoadFromBytes", "Memory allocation failed.");
        return 0;
    }
}

int64_t cj_PAGFile_tagLevel(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_tagLevel", "Input pointer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (layer == NULL) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_tagLevel", "Layer is null.");
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> pagLayer = layer->get();
    if (!pagLayer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_tagLevel", "PAGLayer is null.");
        return -1;
    }
    std::shared_ptr<pag::File> file = pagLayer->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_tagLevel", "getFile() returned null.");
        return -1;
    }
    return file->tagLevel();
}

int64_t cj_PAGFile_numTexts(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numTexts", "Input pointer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (layer == NULL) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numTexts", "Layer is null.");
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> pagLayer = layer->get();
    if (!pagLayer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numTexts", "PAGLayer is null.");
        return -1;
    }
    std::shared_ptr<pag::File> file = pagLayer->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numTexts", "getFile() returned null.");
        return -1;
    }
    return file->numTexts();
}

int64_t cj_PAGFile_numImages(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numImages", "Pointer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numImages", "Layer is null.");
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> pagLayer = layer->get();
    if (!pagLayer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numImages", "PAGLayer is null.");
        return -1;
    }
    std::shared_ptr<pag::File> file = pagLayer->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numImages", "getFile() returned null.");
        return -1;
    }
    return file->numImages();
}

int64_t cj_PAGFile_numVideos(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numVideos", "Pointer is null.");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numVideos", "Layer is null.");
        return -1;
    }
    std::shared_ptr<pag::PAGLayer> pagLayer = layer->get();
    if (!pagLayer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numVideos", "PAGLayer is null.");
        return -1;
    }
    std::shared_ptr<pag::File> file = pagLayer->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_numVideos", "getFile() returned null.");
        return -1;
    }
    return file->numVideos();
}

CJBytesArray cj_PAGFile_path(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_path", "Pointer is null.");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (layer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_path", "Layer is null.");
        return {0, nullptr};
    }
    std::shared_ptr<pag::PAGLayer> pagLayer = layer->get();
    if (!pagLayer) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_path", "PAGLayer is null.");
        return {0, nullptr};
    }
    std::shared_ptr<pag::File> file = pagLayer->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_path", "getFile() returned null.");
        return {0, nullptr};
    }
    const std::string &str = file->path;
    CJBytesArray result = stringToCJBytesArray(str);
    return result;
}

PAGTextData cj_PAGFile_getTextData(const int64_t ptr, int32_t index)
{
    PAGTextData data;
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getTextData", "ptr is null");
        return data;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getTextData", "layer or layer->get() is null");
        return data;
    }
    std::shared_ptr<pag::File> file = layer->get()->getFile();
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getTextData", "file is null");
        return data;
    }
    std::shared_ptr<TextDocument> textDocument = file->getTextData(index);
    if (!textDocument) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getTextData", "textDocument is null");
        return data;
    }
    data.applyFill = textDocument->applyFill;
    data.applyStroke = textDocument->applyStroke;
    data.boxText = textDocument->boxText;
    data.fauxBold = textDocument->fauxBold;
    data.strokeOverFill = textDocument->strokeOverFill;
    data.fauxItalic = textDocument->fauxItalic;
    data.baselineShift = textDocument->baselineShift;
    data.firstBaseLine = textDocument->firstBaseLine;
    data.fontSize = textDocument->fontSize;
    data.strokeWidth = textDocument->strokeWidth;
    data.leading = textDocument->leading;
    data.tracking = textDocument->tracking;
    data.backgroundAlpha = textDocument->backgroundAlpha;
    data.fillColor =
        MakeColorInt(textDocument->fillColor.red, textDocument->fillColor.green, textDocument->fillColor.blue);
    data.strokeColor =
        MakeColorInt(textDocument->strokeColor.red, textDocument->strokeColor.green, textDocument->strokeColor.blue);
    data.backgroundColor = MakeColorInt(textDocument->backgroundColor.red, textDocument->backgroundColor.green,
                                        textDocument->backgroundColor.blue);
    data.justification = textDocument->justification;
    constexpr int BOX_TEXT_LEFT = 0;
    constexpr int BOX_TEXT_TOP = 1;
    constexpr int BOX_TEXT_WIDTH = 2;
    constexpr int BOX_TEXT_HEIGHT = 3;
    data.boxTextRect[BOX_TEXT_LEFT] = textDocument->boxTextPos.x;
    data.boxTextRect[BOX_TEXT_TOP] = textDocument->boxTextPos.y;
    data.boxTextRect[BOX_TEXT_WIDTH] = textDocument->boxTextSize.x;
    data.boxTextRect[BOX_TEXT_HEIGHT] = textDocument->boxTextSize.y;
    const std::string strFontFamily = textDocument->fontFamily;
    data.fontFamily = stringToCJBytesArray(strFontFamily);
    const std::string strFontStyle = textDocument->fontStyle;
    data.fontStyle = stringToCJBytesArray(strFontStyle);
    const std::string strText = textDocument->text;
    data.text = stringToCJBytesArray(strText);
    return data;
}

void cj_PAGFile_replaceText(const int64_t ptr, int32_t index, PAGTextData data)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceText", "ptr is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceText", "layer or layer->get() is null");
        return;
    }
    std::shared_ptr<PAGFile> file = std::static_pointer_cast<PAGFile>(layer->get());
    if (!file) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceText", "file is null");
        return;
    }
    auto text = std::make_shared<TextDocument>();
    text->applyFill = data.applyFill;
    text->applyStroke = data.applyStroke;
    text->baselineShift = data.baselineShift;
    text->boxText = data.boxText;
    constexpr int BOX_TEXT_LEFT = 0;
    constexpr int BOX_TEXT_TOP = 1;
    constexpr int BOX_TEXT_WIDTH = 2;
    constexpr int BOX_TEXT_HEIGHT = 3;
    Rect rect = Rect::MakeXYWH(data.boxTextRect[BOX_TEXT_LEFT], data.boxTextRect[BOX_TEXT_TOP],
                               data.boxTextRect[BOX_TEXT_WIDTH], data.boxTextRect[BOX_TEXT_HEIGHT]);
    text->boxTextPos = {rect.x(), rect.y()};
    text->boxTextSize = {rect.width(), rect.height()};
    text->firstBaseLine = data.firstBaseLine;
    text->fauxBold = data.fauxBold;
    text->fauxItalic = data.fauxItalic;
    text->fillColor = ToColor(data.fillColor);
    text->fontSize = data.fontSize;
    text->strokeColor = ToColor(data.strokeColor);
    text->strokeOverFill = data.strokeOverFill;
    text->strokeWidth = data.strokeWidth;
    text->justification = data.justification;
    text->leading = data.leading;
    text->tracking = data.tracking;
    text->backgroundColor = ToColor(data.backgroundColor);
    text->backgroundAlpha = data.backgroundAlpha;
    text->fontFamily = CJBytesArraytoString(data.fontFamily);
    text->fontStyle = CJBytesArraytoString(data.fontStyle);
    text->text = CJBytesArraytoString(data.text);
    file->replaceText(index, text);
    return;
}

void cj_PAGFile_replaceImage(const int64_t ptrPAGFile, int32_t index, const int64_t ptrPAGImage)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImage", "ptrPAGFile is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImage", "layer or layer->get() is null");
        return;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImage", "file is null");
        return;
    }
    auto image = reinterpret_cast<CJPAGImage *>(ptrPAGImage);
    auto pagImage = (image != nullptr) ? image->get() : nullptr;
    pagFile->replaceImage(index, pagImage);
}

void cj_PAGFile_replaceImageByName(const int64_t ptrPAGFile, const char *layerName, const int64_t ptrPAGImage)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImageByName", "ptrPAGFile is null");
        return;
    }
    if (!layerName || layerName[0] == '\0') {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImageByName", "layerName is null or empty");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImageByName", "layer or layer->get() is null");
        return;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_replaceImageByName", "pagFile is null");
        return;
    }
    auto *image = reinterpret_cast<CJPAGImage *>(ptrPAGImage);
    auto pagImage = image ? image->get() : nullptr;
    pagFile->replaceImageByName(layerName, pagImage);
}

CJInt64Array cj_PAGFile_getLayersByEditableIndex(const int64_t ptrPAGFile, const int32_t index,
                                                 const int8_t layerType)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getLayersByEditableIndex", "ptrPAGFile is null");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getLayersByEditableIndex",
                     "layer or layer->get() is null");
        return {0, nullptr};
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getLayersByEditableIndex", "pagFile is null");
        return {0, nullptr};
    }
    std::vector<std::shared_ptr<PAGLayer>> pagLayers =
        pagFile->getLayersByEditableIndex(index, static_cast<pag::LayerType>(layerType));
    if (pagLayers.empty()) {
        return {0, nullptr};
    }
    const size_t size = pagLayers.size();
    auto *arr = new int64_t[size];
    for (size_t i = 0; i < size; ++i) {
        std::shared_ptr<PAGLayer> pagLayer = pagLayers[i];
        if (!pagLayer) {
            delete[] arr;
            return {0, nullptr};
        }
        CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(pagLayer);
        arr[i] = (int64_t)cjlayer;
    }
    return CJInt64Array{static_cast<int64_t>(size), arr};
}

CJInt64Array cj_PAGFile_getEditableIndices(const int64_t ptrPAGFile, const int8_t layerType)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getEditableIndices", "ptrPAGFile is null");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getEditableIndices", "layer or layer->get() is null");
        return {0, nullptr};
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_getEditableIndices", "pagFile is null");
        return {0, nullptr};
    }
    std::vector<int> data = pagFile->getEditableIndices(static_cast<pag::LayerType>(layerType));
    long long size = data.size();
    int64_t *arr = new int64_t[size];
    for (size_t i = 0; i < data.size(); i++) {
        arr[i] = data[i];
    }
    return CJInt64Array{size, arr};
}

int32_t cj_PAGFile_timeStretchMode(const int64_t ptrPAGFile)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_timeStretchMode", "ptrPAGFile is null");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_timeStretchMode", "layer or layer->get() is null");
        return -1;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_timeStretchMode", "pagFile is null");
        return -1;
    }
    return pagFile->timeStretchMode();
}

void cj_PAGFile_setTimeStretchMode(const int64_t ptrPAGFile, int32_t mode)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setTimeStretchMode", "ptrPAGFile is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setTimeStretchMode", "layer or layer->get() is null");
        return;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setTimeStretchMode", "pagFile is null");
        return;
    }
    pagFile->setTimeStretchMode(static_cast<Enum>(mode));
    return;
}

void cj_PAGFile_setDuration(const int64_t ptrPAGFile, int64_t duration)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setDuration", "ptrPAGFile is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setDuration", "layer or layer->get() is null");
        return;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_setDuration", "pagFile is null");
        return;
    }
    pagFile->setDuration(duration);
}

int64_t cj_PAGFile_duration(const int64_t ptrPAGFile)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_duration", "ptrPAGFile is null");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_duration", "layer or layer->get() is null");
        return -1;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_duration", "pagFile is null");
        return -1;
    }
    return pagFile->duration();
}

int64_t cj_PAGFile_copyOriginal(const int64_t ptrPAGFile)
{
    if (ptrPAGFile == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_copyOriginal", "ptrPAGFile is null");
        return -1;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptrPAGFile);
    CJPAGLayerHandle *layer = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!layer || !layer->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_copyOriginal", "layer or layer->get() is null");
        return -1;
    }
    std::shared_ptr<PAGFile> pagFile = std::static_pointer_cast<PAGFile>(layer->get());
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_copyOriginal", "pagFile is null");
        return -1;
    }
    std::shared_ptr<PAGFile> newFile = pagFile->copyOriginal();
    if (!newFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_copyOriginal", "copyOriginal returned null");
        return -1;
    }
    CJPAGLayerHandle *handler = new CJPAGLayerHandle(newFile);
    if (!handler) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_copyOriginal", "newHandle allocation failed");
        return -1;
    }
    return (int64_t)handler;
}

void cj_PAGFile_release(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_release", "Pointer is null");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *pagFile = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!pagFile) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGFile_release", "Invalid instance");
        return;
    }
    delete pagFile;
}
}
} // namespace pag