/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "cj_pag.h"

extern "C" {
namespace pag {
CJBytesArray cj_pag_sdkVersion()
{
    std::string str = pag::PAG::SDKVersion();
    CJBytesArray sdk = stringToCJBytesArray(str);
    return sdk;
}
} // namespace pag
}
