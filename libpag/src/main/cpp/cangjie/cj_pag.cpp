/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag.h"

extern "C" {
namespace pag {
char *cj_pag_sdkVersion()
{
    std::string str = pag::PAG::SDKVersion();
    // The string is ISO-8859-1 encoded and needs to be converted to UTF-8 encoding.
    char *sdk = cj_string_To_UTF8((char *)str.c_str(), "ISO-8859-1");
    return sdk;
}
} // namespace pag
}
