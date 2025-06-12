/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_string_util.h"

namespace pag {

/**
 * There is a known bug in env->NewStringUTF which will lead to crash in some devices.
 * So we use this method instead.
 */
char *cj_string_To_UTF8(const char *input, const char *from_encoding) {
    // If the string is in another encoding (such as ISO-8859-1 or window-1252), it needs to be converted to UTF-8
    // encoding.
    iconv_t cd = iconv_open("UTF-8", from_encoding);
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        return NULL;
    }

    size_t inbytesleft = strlen(input);
    // UTF-8 uses a maximum of 4 bytes to represent a character
    size_t outbytesleft = inbytesleft * 4;
    char *output = (char *)malloc(outbytesleft + 1);
    if (!output) {
        perror("malloc");
        iconv_close(cd);
        return NULL;
    }

    char *inbuf = (char *)input;
    char *outbuf = output;

    if (iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1) {
        perror("iconv");
        free(output);
        iconv_close(cd);
        return NULL;
    }
    // Add string terminator
    *outbuf = '\0';
    iconv_close(cd);
    return output;
}
} // namespace pag
