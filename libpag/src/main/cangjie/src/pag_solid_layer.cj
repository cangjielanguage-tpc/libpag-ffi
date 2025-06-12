/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGSolidLayer_make(duration: Int64, width: Int64, height: Int64, solidColor: Color, opacity: UInt8): Int64

    func cj_PAGSolidLayer_solidColor(ptr: Int64): Int64

    func cj_PAGSolidLayer_setSolidColor(ptr: Int64, solidColor: Int64): Unit
}

public class PAGSolidLayer <: PAGLayer {
    public PAGSolidLayer(nativeContext: Int64) {
        super(nativeContext)
    }

    public static func make(duration: Int64, width: Int64, height: Int64, solidColor: Color, opacity!: UInt8 = 255): Option<PAGSolidLayer> {
        unsafe {
            let context: Int64 = cj_PAGSolidLayer_make(duration, width, height, solidColor, opacity)
            if (context <= 0) {
                return None
            }
            return PAGSolidLayer(context)
        }
    }

    /**
     * Return the solid color of the layer
     */
    public func solidColor(): Int64 {
        unsafe {
            return cj_PAGSolidLayer_solidColor(ptr)
        }
    }

    /**
     * Set the solid color of the layer.
     */
    public func setSolidColor(solidColor: Int64): Unit {
        unsafe {
            return cj_PAGSolidLayer_setSolidColor(ptr, solidColor)
        }
    }
}
