/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGTextLayer_make(duration: Int64, text: CString, fontSize: Float32, fontFamily: CString, fontStyle: CString): Int64

    func cj_PAGTextLayer_fillColor(ptr: Int64): Int64

    func cj_PAGTextLayer_setFillColor(ptr: Int64, color: Int64): Unit

    func cj_PAGTextLayer_font(ptr: Int64): Int64

    func cj_PAGTextLayer_setFont(ptr: Int64, fontptr: Int64): Unit

    func cj_PAGTextLayer_fontSize(ptr: Int64): Float64

    func cj_PAGTextLayer_setFontSize(ptr: Int64, fontSize: Float64): Unit

    func cj_PAGTextLayer_strokeColor(ptr: Int64): Int64

    func cj_PAGTextLayer_setStrokeColor(ptr: Int64, color: Int64): Unit

    func cj_PAGTextLayer_text(ptr: Int64): CString

    func cj_PAGTextLayer_setText(ptr: Int64, t: CString): Unit

    func cj_PAGTextLayer_reset(ptr: Int64): Unit

    func cj_PAGTextLayer_release(ptrCJPAGPlayer: Int64): Unit
}

public class PAGTextLayer <: PAGLayer {
    init(nativeLayer: Int64) {
        super(nativeLayer)
    }

    public static func make(duration: Int64, text: String, fontSize: Float32, fontFamily!: String = "",
        fontStyle!: String = ""): Option<PAGTextLayer> {
        unsafe {
            let t = LibC.mallocCString(text)
            let ff = LibC.mallocCString(fontFamily)
            let fs = LibC.mallocCString(fontStyle)
            let context: Int64 = cj_PAGTextLayer_make(duration, t, fontSize, ff, fs)
            LibC.free(t)
            LibC.free(ff)
            LibC.free(fs)
            if (context <= 0) {
                return None
            }
            return PAGTextLayer(context)
        }
    }

    /**
     * Returns the text layer’s fill color.
     */
    public func fillColor(): Int64 {
        unsafe {
            return cj_PAGTextLayer_fillColor(ptr)
        }
    }

    /**
     * Set the text layer’s fill color.
     */
    public func setFillColor(color: Int64): Unit {
        unsafe {
            cj_PAGTextLayer_setFillColor(ptr, color)
        }
    }

    /**
     * Returns the text layer's font.
     */
    public func font(): PAGFont {
        unsafe {
            let context: Int64 = cj_PAGTextLayer_font(ptr)
            if (context <= 0) {
                return PAGFont(context)
            }
            return PAGUtils.ToPAGFont(context)
        }
    }

    /**
     * Set the text layer's font.
     */
    public func setFont(font: PAGFont): Unit {
        unsafe {
            cj_PAGTextLayer_setFont(ptr, font.ptr)
        }
    }

    /**
     * Returns the text layer's font size.
     */
    public func fontSize(): Float64 {
        unsafe {
            return cj_PAGTextLayer_fontSize(ptr)
        }
    }

    /**
     * Set the text layer's font size.
     */
    public func setFontSize(fontSize: Float64): Unit {
        unsafe {
            cj_PAGTextLayer_setFontSize(ptr, fontSize)
        }
    }

    /**
     * Returns the text layer's stroke color.
     */
    public func strokeColor(): Int64 {
        unsafe {
            return cj_PAGTextLayer_strokeColor(ptr)
        }
    }

    /**
     * Set the text layer's stroke color.
     */
    public func setStrokeColor(color: Int64): Unit {
        unsafe {
            cj_PAGTextLayer_setStrokeColor(ptr, color)
        }
    }

    /**
     * Returns the text layer's text.
     */
    public func text(): String {
        unsafe {
            let retC: CString = cj_PAGTextLayer_text(ptr)
            let ret = retC.toString()
            LibC.free(retC)
            return ret
        }
    }

    /**
     * Set the text layer's text.
     */
    public func setText(text: String): Unit {
        unsafe {
            let t = LibC.mallocCString(text)
            cj_PAGTextLayer_setText(ptr, t)
            LibC.free(t)
            return
        }
    }

    /**
     * Reset the text layer to its default text data.
     */
    public func reset(): Unit {
        unsafe {
            cj_PAGTextLayer_reset(ptr)
        }
    }

    /*
     * Free up resources used by the PAGTextLayer instance immediately instead of relying on the garbage collector to do this for you at some point in the future.
     */
    public func release(): Unit {
        if (isRelease) {
            return
        }
        unsafe {
            cj_PAGTextLayer_release(ptr)
            isRelease = true
        }
    }
}
