/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag_font.h"
#include "cj_helper.h"

namespace pag {
extern "C" {
long long cj_PAGFont_registerFont(char *fileName, const int32_t ttcIndex, char *fontFamily, char *fontStyle)
{
    std::string fontPath = fileName;
    std::string fontFamilys = fontFamily;
    std::string fontStyles = fontStyle;
    PAGFont font = PAGFont::RegisterFont(fontPath, ttcIndex, fontFamilys, fontStyles);
    CJPAGFont *cjfont = new CJPAGFont(font);
    return (int64_t)cjfont;
}

long long cj_PAGFont_registerFontBytes(int *data, int size, const int32_t ttcIndex, char *fontFamily, char *fontStyle)
{
    std::string fontFamilys = fontFamily;
    std::string fontStyles = fontStyle;
    PAGFont font = PAGFont::RegisterFont(data, size, ttcIndex, fontFamilys, fontStyles);
    PAGFont *ptr = &font;
    return (int64_t)ptr;
}

void cj_PAGFont_unregisterFont(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[unregisterFont]-the pointer of PAGFont is null.");
        return;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGFont *instance = reinterpret_cast<CJPAGFont *>(ptrInt);
    if (instance == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[unregisterFont]-the pointer of CJPAGFont is null.");
        return;
    }
    PAGFont font = instance->get();
    PAGFont::UnregisterFont(font);
    return;
}

void cj_PAGFont_setFallbackFontPaths(char *fontPaths[], int lenfn, int *ttcIndices, int lenttc)
{
    std::vector<std::string> fallbackList;
    std::vector<int> ttcList;
    int length = std::min(lenfn, lenttc);
    for (int index = 0; index < length; index++) {
        auto fontPath = fontPaths[index];
        auto ttc = ttcIndices[index];
        fallbackList.push_back(fontPath);
        ttcList.push_back(ttc);
    }
    PAGFont::SetFallbackFontPaths(fallbackList, ttcList);
}

CJBytesArray cj_PAGFont_getFontFamily(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[getFontFamily]-the pointer of PAGFont is null.");
        return {0, nullptr};
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGFont *instance = reinterpret_cast<CJPAGFont *>(ptrInt);
    if (instance == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[getFontFamily]-the pointer of CJPAGFont is null.");
        return {0, nullptr};
    }
    PAGFont font = instance->get();
    const std::string fontFamily = font.fontFamily;
    CJBytesArray result = stringToCJBytesArray(fontFamily);
    return result;
}

char *cj_PAGFont_getFontStyle(const int64_t ptr)
{
    if (ptr == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[getFontStyle]-the pointer of PAGFont is null.");
        return nullptr;
    }
    intptr_t ptrInt = static_cast<intptr_t>(ptr);
    CJPAGFont *instance = reinterpret_cast<CJPAGFont *>(ptrInt);
    if (instance == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, "[PAGFont]", "[getFontStyle]-the pointer of CJPAGFont is null.");
        return nullptr;
    }
    PAGFont font = instance->get();
    const std::string fontStyle = font.fontStyle;
    char *cstr = cj_string_To_UTF8((char *)fontStyle.c_str(), "ISO-8859-1");
    return cstr;
}
}
} // namespace pag
