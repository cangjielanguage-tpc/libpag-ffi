/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.hilog.*

@FastNative
foreign func cj_pag_sdkVersion(): CJBytesArray

public class PAG {
    /**
     * Get SDK version information.
     */
    public static func sdkVersion(): String {
        unsafe {
            let res: CJBytesArray = cj_pag_sdkVersion()
            let str = BytesArrayToString(res)
            free_CJBytesArray(res)
            return str
        }
    }
}
