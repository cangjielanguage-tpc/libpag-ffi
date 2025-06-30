/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_helper.h"
#include "cj_pag_layer_handle.h"

namespace pag {
extern "C" {
static std::shared_ptr<PAGTextLayer> getPAGTextLayer(const int64_t ptr) {
    if (ptr == 0) {
        return nullptr;
    }
    CJPAGLayerHandle *instance;
    instance = (CJPAGLayerHandle *)ptr;
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
    CJPAGLayerHandle *player = (CJPAGLayerHandle *)ptr;
    player->reset();
    delete player;
    return;
}

long long cj_PAGTextLayer_make(const int64_t duration, char *text, float fontSize, char *fontFamily, char *fontStyle) {
    std::string textStr = text;
    std::string ff = fontFamily;
    std::string fs = fontStyle;
    std::shared_ptr<PAGTextLayer> layer = PAGTextLayer::Make(duration, textStr, fontSize, ff, fs);
    CJPAGLayerHandle *cjlayer = new CJPAGLayerHandle(layer);
    // Declare and initialize pointers to classes
    return (int64_t)cjlayer;
}

long long cj_PAGTextLayer_fillColor(const int64_t ptr) {
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

void cj_PAGTextLayer_setFillColor(const int64_t ptr, const int64_t color) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setFillColor]-the pointer of PAGTextLayer is null.");
        return;
    }

    Color colors = ToColor(color);
    textLayer->setFillColor(colors);
}

long long cj_PAGTextLayer_font(const int64_t ptr) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[font]-the pointer of PAGTextLayer is null.");
        return 0;
    }
    PAGFont font = textLayer->font();
    PAGFont *ptrPAGFont = &font;
    return (int64_t)ptrPAGFont;
}

void cj_PAGTextLayer_setFont(const int64_t ptr, const int64_t fontptr) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setFont]-the pointer of PAGTextLayer is null.");
        return;
    }

    PAGFont *pagFont;
    pagFont = (PAGFont *)fontptr;
    textLayer->setFont(*pagFont);
}

double cj_PAGTextLayer_fontSize(const int64_t ptr) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[fontSize]-the pointer of PAGTextLayer is null.");
        return 0.0;
    }
    double fontSize = textLayer->fontSize();
    return fontSize;
}

void cj_PAGTextLayer_setFontSize(const int64_t ptr, double fontSize) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setFontSize]-the pointer of PAGTextLayer is null.");
        return;
    }

    textLayer->setFontSize(fontSize);
}

long long cj_PAGTextLayer_strokeColor(const int64_t ptr) {
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

void cj_PAGTextLayer_setStrokeColor(const int64_t ptr, const int64_t color) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setStrokeColor]-the pointer of PAGTextLayer is null.");
        return;
    }

    const Color &colors = ToColor(color);
    textLayer->setStrokeColor(colors);
}

char *cj_PAGTextLayer_text(const int64_t ptr) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[text]-the pointer of PAGTextLayer is null.");
        return nullptr;
    }
    std::string text = textLayer->text();
    char *cstr = new char[text.size() + 1];
    std::strcpy(cstr, text.c_str());
    return cstr;
}

void cj_PAGTextLayer_setText(const int64_t ptr, char *t) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]",
                     "[setText]-the pointer of PAGTextLayer is null.");
        return;
    }
    const std::string &text = t;
    textLayer->setText(text);
}

void cj_PAGTextLayer_reset(const int64_t ptr) {
    std::shared_ptr<PAGTextLayer> textLayer = getPAGTextLayer(ptr);
    if (textLayer == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGTextLayer]", "[reset]-the pointer of PAGTextLayer is null.");
        return;
    }
    textLayer.reset();
}
}
} // namespace pag
