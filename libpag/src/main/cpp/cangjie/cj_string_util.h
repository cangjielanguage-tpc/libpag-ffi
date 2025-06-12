/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef LIBPAG4CJ_CJ_STRING_UTIL_H
#define LIBPAG4CJ_CJ_STRING_UTIL_H

#include <codecvt>
#include <iconv.h>

extern "C" {
namespace pag {
// If the string is in another encoding (such as ISO-8859-1 or window-1252), it needs to be converted to UTF-8 encoding.
char *cj_string_To_UTF8(const char *input, const char *from_encoding);
} // namespace pag
}
#endif // LIBPAG4CJ_CJ_STRING_UTIL_H
