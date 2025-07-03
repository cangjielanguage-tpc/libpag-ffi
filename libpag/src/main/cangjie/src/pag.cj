/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.hilog.*

@FastNative
foreign func cj_pag_sdkVersion(): CString

public class PAG {
    /**
     * Get SDK version information.
     */
    public static func sdkVersion(): String {
        unsafe {
            let retC: CString = cj_pag_sdkVersion()
            let ret = retC.toString()
            LibC.free(retC)
            return ret
        }
    }
}
