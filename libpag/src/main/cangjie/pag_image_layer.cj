/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGImageLayer_nativeMake(width: Int64, height: Int64, duration: Int64): Int64

    func cj_PAGImageLayer_contentDuration(ptr: Int64): Int64

    func cj_PAGImageLayer_getVideoRanges(ptr: Int64): CJPAGVideoRangeArray

    func cj_PAGImageLayer_setImage(ptr: Int64, image: Int64): Unit

    func cj_PAGImageLayer_imageBytes(ptr: Int64): CJBytesArray
}

public class PAGImageLayer <: PAGLayer {

    /**
     * Make a PAGImageLayer with with, height and duration(in microseconds).
     */
    public static func make(width: Int64, height: Int64, duration: Int64): Option<PAGImageLayer> {
        unsafe {
            let context: Int64 = cj_PAGImageLayer_nativeMake(width, height, duration)
            if (context <= 0) {
                return None
            }
            return PAGImageLayer(context)
        }
    }

    protected PAGImageLayer(nativeContext: Int64) {
        super(nativeContext)
    }

    /**
     * Returns the content duration in microseconds, which indicates the minimal length required for
     * replacement.
     */
    public func contentDuration(): Int64 {
        unsafe {
            return cj_PAGImageLayer_contentDuration(ptr)
        }
    }

    /**
     * Returns the time ranges of the source video for replacement.
     */
    public func getVideoRanges(): Array<PAGVideoRange> {
        unsafe {
            let res: CJPAGVideoRangeArray = cj_PAGImageLayer_getVideoRanges(ptr)
            let size: Int64 = res.size
            let cjPAGVideoRanges: CPointer<CJPAGVideoRange> = res.buf
            let pagVideoRanges: Array<PAGVideoRange> = Array<PAGVideoRange>(size, repeat: PAGVideoRange())
            for (i in 0..size) {
                let cjvr: CJPAGVideoRange = cjPAGVideoRanges.read(i)
                let pagVideoRange: PAGVideoRange = PAGVideoRange(cjvr.startTime, cjvr.endTime, cjvr.playDuration,
                    cjvr.reversed)
                pagVideoRanges[i] = pagVideoRange
            }
            free_CPointer_CJPAGVideoRange(cjPAGVideoRanges)

            return pagVideoRanges
        }
    }

    /**
     * Replace the original image content with the specified PAGImage object.
     * Passing in null for the image parameter resets the layer to its default image content.
     * The setImage() method only modifies the content of the calling PAGImageLayer.
     *
     * @param image The PAGImage object to replace with.
     */
    public func setImage(image: Option<PAGImage>): Unit {
        if (let Some(v) <- image) {
            setImage(v.nativeContext)
        } else {
            setImage(0)
        }
    }

    private func setImage(image: Int64): Unit {
        unsafe {
            return cj_PAGImageLayer_setImage(ptr, image)
        }
    }

    /**
     * The default image data of this layer, which is webp format.
     */
    public func imageBytes(): Array<UInt8> {
        unsafe {
            let res: CJBytesArray = cj_PAGImageLayer_imageBytes(ptr)
            let size: Int64 = res.size
            let buf: CPointer<UInt8> = res.buf
            let bytes: Array<Byte> = Array<Byte>(size, repeat: 0)
            for (i in 0..size) {
                bytes[i] = buf.read(i)
            }
            free_CPointer_UInt8(buf)

            return bytes
        }
    }
}
