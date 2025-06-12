/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGShapeLayer_make(bytes: CPointer<UInt8>, length: Int64, filePath: CString, password: CString): Int64

    func cj_PAGShapeLayer_makeByURL(filePath: CString, password: CString): Int64
}

public class PAGShapeLayer <: PAGLayer {
    public PAGShapeLayer(nativeContext: Int64) {
        super(nativeContext)
    }

    /**
     *  Load the PAG file from byte data, and return null if the byte is empty or not a valid PAG file.
     */
    public static func make(bytes: Array<UInt8>, length: Int64, filePath!: String = "", password!: String = ""): Option<PAGShapeLayer> {
        unsafe {
            let handle = acquireArrayRawData(bytes)
            let fp = LibC.mallocCString(filePath)
            let pw = LibC.mallocCString(password)
            let native: Int64 = cj_PAGShapeLayer_make(handle.pointer, length, fp, pw)
            LibC.free(fp)
            LibC.free(pw)
            releaseArrayRawData(handle)
            if (native <= 0) {
                return None
            }
            return PAGShapeLayer(native)
        }
    }

    /**
     *  Load the PAG file from the path, and return null if the file does not exist or the data is not a PAG file.
     */
    public static func make(filePath: String, password!: String = ""): Option<PAGShapeLayer> {
        unsafe {
            let fp = LibC.mallocCString(filePath)
            let pw = LibC.mallocCString(password)
            let native: Int64 = cj_PAGShapeLayer_makeByURL(fp, pw)
            LibC.free(fp)
            LibC.free(pw)
            if (native <= 0) {
                return None
            }
            return PAGShapeLayer(native)
        }
    }
}
