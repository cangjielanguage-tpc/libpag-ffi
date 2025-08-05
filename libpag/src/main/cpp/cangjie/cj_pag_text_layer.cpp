/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_helper.h"
#include "cj_pag_layer_handle.h"

namespace pag {
extern "C" {
static std::shared_ptr<PAGTextLayer> getPAGTextLayer(const int64_t ptr)
{
    if (ptr == 0) {
        return nullptr;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "getPAGTextLayer", "instance is null");
        return nullptr;
    }
    std::shared_ptr<pag::PAGLayer> layer = instance->get();
    if (layer == nullptr) {
        return nullptr;
    }
    if (layer && layer->layerType() == LayerType::Text) {
        return std::static_pointer_cast<PAGTextLayer>(layer);
    }
    return nullptr;
}

void cj_PAGTextLayer_release(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "cj_PAGTextLayer_release", "ptr is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *player = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    player->reset();
    delete player;
    return;
}

long long cj_PAGTextLayer_make(const int64_t duration, char *text, float fontSize, char *fontFamily, char *fontStyle)
{
    std::string textStr = text;
    std::string ff = fontFamily;
    std::string fs = fontStyle;
    std::shared_ptr<PAGTextLayer> layer = PAGTextLayer::Make(duration, textStr, fontSize, ff, fs);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    // Declare and initialize pointers to classes
    return (int64_t)cjlayer;
}

long long cj_PAGTextLayer_fillColor(const int64_t ptr)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[fillColor]-the pointer of PAGTextLayer is null.");
        return 0;
    }
    Color color = textLayer->fillColor();
    long long res = MakeColorInt(color.red, color.green, color.blue);
    return res;
}

void cj_PAGTextLayer_setFillColor(const int64_t ptr, const int64_t color)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setFillColor]-the pointer of PAGTextLayer is null.");
        return;
    }

    Color colors = ToColor(color);
    textLayer->setFillColor(colors);
}

void cj_PAGTextLayer_setFont(const int64_t ptr, char *fontFamily, char *fontStyle)
{
    if (ptr == 0) {
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[setFont]-the pointer is null.");
        return;
    }
    auto textLayer = std::static_pointer_cast<PAGTextLayer>(instance->get());
    std::string fontFamilyStr = fontFamily;
    std::string fontStyleStr = fontStyle;
    PAGFont pagFont(fontFamilyStr, fontStyleStr);
    textLayer->setFont(pagFont);
}

double cj_PAGTextLayer_fontSize(const int64_t ptr)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[fontSize]-the pointer of PAGTextLayer is null.");
        return 0.0;
    }
    double fontSize = textLayer->fontSize();
    return fontSize;
}

void cj_PAGTextLayer_setFontSize(const int64_t ptr, double fontSize)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setFontSize]-the pointer of PAGTextLayer is null.");
        return;
    }

    textLayer->setFontSize(fontSize);
}

long long cj_PAGTextLayer_strokeColor(const int64_t ptr)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[strokeColor]-the pointer of PAGTextLayer is null.");
        return 0;
    }

    Color color = textLayer->strokeColor();
    long long strokeColor = MakeColorInt(color.red, color.green, color.blue);

    return strokeColor;
}

void cj_PAGTextLayer_setStrokeColor(const int64_t ptr, const int64_t color)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setStrokeColor]-the pointer of PAGTextLayer is null.");
        return;
    }

    const Color &colors = ToColor(color);
    textLayer->setStrokeColor(colors);
}

CJBytesArray cj_PAGTextLayer_text(const int64_t ptr)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[text]-the pointer of PAGTextLayer is null.");
        return {0, nullptr};
    }
    std::string text = textLayer->text();
    CJBytesArray result = stringToCJBytesArray(text);
    return result;
}

void cj_PAGTextLayer_setText(const int64_t ptr, char *t)
{
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setText]-the pointer of PAGTextLayer is null.");
        return;
    }
    const std::string &text = t;
    textLayer->setText(text);
}

void cj_PAGTextLayer_reset(const int64_t ptr)
{
    if (ptr == 0) {
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[reset]-Invalid handler.");
        return;
    }
    auto textLayer = std::static_pointer_cast<PAGTextLayer>(instance->get());
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[reset]-the pointer of PAGTextLayer is null.");
        return;
    }
    textLayer->reset();
}

CJBytesArray cj_PAGTextLayer_getFontFamily(const int64_t ptr)
{
    if (ptr == 0) {
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[getFontFamily]-the pointer is null.");
        return {0, nullptr};
    }
    auto textLayer = std::static_pointer_cast<PAGTextLayer>(instance->get());
    auto font = textLayer->font();
    CJBytesArray result = stringToCJBytesArray(font.fontFamily);
    return result;
}

CJBytesArray cj_PAGTextLayer_getFontStyle(const int64_t ptr)
{
    if (ptr == 0) {
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGLayerHandle *instance = reinterpret_cast<CJPAGLayerHandle *>(ptrInt);
    if (!instance || !instance->get()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[getFontStyle]-the pointer is null.");
        return {0, nullptr};
    }
    auto textLayer = std::static_pointer_cast<PAGTextLayer>(instance->get());
    auto font = textLayer->font();
    CJBytesArray result = stringToCJBytesArray(font.fontStyle);
    return result;
}
}
} // namespace pag
