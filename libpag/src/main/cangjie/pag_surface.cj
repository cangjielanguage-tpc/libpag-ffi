/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGSurface_setupOffscreen(width: Int32, height: Int32): Int64

    func cj_PAGSurface_fromSurfaceID(surfaceId: Int64): Int64

    func cj_PAGSurface_width(ptrCJPAGSurface: Int64): Int64

    func cj_PAGSurface_height(ptrCJPAGSurface: Int64): Int64

    func cj_PAGSurface_clearAll(ptrCJPAGSurface: Int64): Bool

    func cj_PAGSurface_freeCache(ptrCJPAGSurface: Int64): Unit

    func cj_PAGSurface_updateSize(ptrCJPAGSurface: Int64): Unit

    func cj_PAGSurface_makeSnapshot(ptrCJPAGSurface: Int64): CJPixelMap

    func cj_PAGSurface_release(ptrCJPAGSurface: Int64): Unit
}

public class PAGSurface {

    // Binding with C code, the CJPAGSurface object pointer returned by C code.
    var ptrCJPAGSurface: Int64 = 0

    private init(ptrCJPAGSurface: Int64) {
        if (this.ptrCJPAGSurface != 0) {
            unsafe {
                cj_PAGSurface_release(this.ptrCJPAGSurface)
            }
        }
        this.ptrCJPAGSurface = ptrCJPAGSurface
    }

    /**
     * The width of surface in pixels.
     */
    protected func getCID(): Int64 {
        unsafe {
            return ptrCJPAGSurface
        }
    }
    /**
     * Create a new PAGSurface for off screen rendering. Allocate memory for pixels based on width and height, which
     * can be accessed through readPixels(). If the specified size is invalid, return null.
     */
    public static func makeOffscreen(width: Int32, height: Int32): Option<PAGSurface> {
        unsafe {
            let ptrCJPAGSurface: Int64 = cj_PAGSurface_setupOffscreen(width, height)
            if (ptrCJPAGSurface <= 0) {
                return None
            }
            return PAGSurface(ptrCJPAGSurface)
        }
    }

    public static func fromSurfaceID(surfaceId: Int64): Option<PAGSurface> {
        unsafe {
            let nativeSurface: Int64 = cj_PAGSurface_fromSurfaceID(surfaceId)
            if (nativeSurface <= 0) {
                return None
            } else {
                return PAGSurface(nativeSurface)
            }
        }
    }

    /**
     * The width of surface in pixels.
     */
    public func width(): Int64 {
        unsafe {
            return cj_PAGSurface_width(ptrCJPAGSurface)
        }
    }

    /**
     * The height of surface in pixels.
     */
    public func height(): Int64 {
        unsafe {
            return cj_PAGSurface_height(ptrCJPAGSurface)
        }
    }

    /**
     * Erases all pixels of this surface with transparent color. Returns true if the content has changed.
     */
    public func clearAll(): Bool {
        unsafe {
            return cj_PAGSurface_clearAll(ptrCJPAGSurface)
        }
    }

    /**
     * Free the cache created by the surface immediately. Call this method can reduce memory pressure.
     */
    public func freeCache(): Unit {
        unsafe {
            cj_PAGSurface_freeCache(ptrCJPAGSurface)
        }
    }

    /**
     * Update the size of the surface. This method should be called when the size of the surface is changed.
     */
    public func updateSize(): Unit {
        unsafe {
            cj_PAGSurface_updateSize(ptrCJPAGSurface)
        }
    }

    /**
     * Returns a bitmap capturing the contents of the PAGSurface. Subsequent rendering of the PAGSurface will not be captured.
     */
    public func makeSnapshot(): Option<PixelMap> {
        unsafe {
            let res: CJPixelMap = cj_PAGSurface_makeSnapshot(ptrCJPAGSurface)
            return ConvertToPixelMap(res)
        }
    }

    public func release(): Unit {
        unsafe {
            cj_PAGSurface_release(ptrCJPAGSurface)
            ptrCJPAGSurface = 0
        }
    }
}
