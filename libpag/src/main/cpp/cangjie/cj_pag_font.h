/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_PAG_FONT_H
#define LIBPAG4CJ_CJ_PAG_FONT_H

#include <pag/pag.h>
#include <hilog/log.h>
#include "cj_string_util.h"

extern "C" {// cangjie [PAGFont] ffi
long long cj_PAGFont_registerFont(char* fileName, const int32_t ttcIndex, char* fontFamily, char* fontStyle);
long long cj_PAGFont_registerFontBytes(int* data, int size, const int32_t ttcIndex, char* fontFamily, char* fontStyle);
void cj_PAGFont_unregisterFont(const int64_t ptr);
void cj_PAGFont_setFallbackFontPaths(char* fontPaths[], int lenfn, int* ttcIndices, int lenttc);
char* cj_PAGFont_getFontFamily(const int64_t ptr);
char* cj_PAGFont_getFontStyle(const int64_t ptr);
}

namespace pag {
class CJPAGFont {
 public:
        explicit CJPAGFont(pag::PAGFont pagFont) : pagFont(pagFont) {
        }

        ~CJPAGFont() {};
    
        static std::string ClassName() {
            return "CJPAGFont";
        }

        pag::PAGFont get() {
            return pagFont;
        }
    private:
        pag::PAGFont pagFont;
};
}
#endif //LIBPAG4CJ_CJ_PAG_FONT_H
