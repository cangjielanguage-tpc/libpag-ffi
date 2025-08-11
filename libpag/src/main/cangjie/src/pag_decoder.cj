/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.image.AlphaType
internal import ohos.image.PixelMapFormat
internal import ohos.image.PixelMap

@FastNative
foreign {
    func cj_PAGDecoder_makeFrom(ptr: Int64, maxFrameRate: Float32, scale: Float32): Int64

    func cj_PAGDecoder_width(ptr: Int64): Int64

    func cj_PAGDecoder_height(ptr: Int64): Int64

    func cj_PAGDecoder_numFrames(ptr: Int64): Int64

    func cj_PAGDecoder_frameRate(ptr: Int64): Float32

    func cj_PAGDecoder_checkFrameChanged(ptr: Int64, index: Int64): Bool

    func cj_PAGDecoder_readFrame(ptr: Int64, index: Int64): CJPixelMap

    func cj_PAGDecoder_nativeRelease(ptr: Int64): Unit

    func cj_PAGDecoder_nativeFinalize(ptr: Int64): Unit
}

/**
 * PAGDecoder provides a utility to read image frames directly from a PAGComposition, and caches the
 * image frames as a sequence file on the disk, which may significantly speed up the reading process
 * depending on the complexity of the PAG files. You can use the PAGDiskCache::SetMaxDiskSize()
 * method to manage the cache limit of the disk usage.
 */
public class PAGDecoder {
    private var nativeContext: Int64 = 0

    private init(nativeContext: Int64) {
        this.nativeContext = nativeContext
    }

    /**
     * Creates a new PAGDecoder with the specified PAGComposition, using the composition's frame
     * rate and size. Please only keep an external reference to the PAGComposition if you need to
     * modify it in the feature. Otherwise, the internal composition will not be released
     * automatically after the associated disk cache is complete, which may cost more memory than
     * necessary. Returns nil if the composition is nil. Note that the returned PAGDecoder may
     * become invalid if the associated PAGComposition is added to a PAGPlayer or another
     * PAGDecoder.
     */
    public static func make(pagComposition: PAGComposition): Option<PAGDecoder> {
        return make(pagComposition, pagComposition.frameRate(), 1.0)
    }

    /**
     * Creates a PAGDecoder with a PAGComposition, a frame rate limit, and a scale factor for the
     * decoded image size. Please only keep an external reference to the PAGComposition if you need
     * to modify it in the feature. Otherwise, the internal composition will not be released
     * automatically after the associated disk cache is complete, which may cost more memory than
     * necessary. Returns nullptr if the composition is nullptr. Note that the returned PAGDecoder
     * may become invalid if the associated PAGComposition is added to a PAGPlayer or another
     * PAGDecoder.
     */
    public static func make(pagComposition: PAGComposition, maxFrameRate: Float32, scale: Float32): Option<PAGDecoder> {
        let nativeContext: Int64 = makeFrom(pagComposition, maxFrameRate, scale)
        if (nativeContext == 0) {
            return None
        }
        return PAGDecoder(nativeContext)
    }

    private static func makeFrom(pagComposition: PAGComposition, maxFrameRate: Float32, scale: Float32): Int64 {
        unsafe {
            let id: Int64 = cj_PAGDecoder_makeFrom(pagComposition.getptr(), maxFrameRate, scale)
            return id
        }
    }

    /**
     * Returns the width of decoded image frames.
     */
    public func width(): Int64 {
        unsafe {
            let num: Int64 = cj_PAGDecoder_width(nativeContext)
            return num
        }
    }

    /**
     * Returns the height of decoded image frames.
     */
    public func height(): Int64 {
        unsafe {
            let num: Int64 = cj_PAGDecoder_height(nativeContext)
            return num
        }
    }

    /**
     * Returns the number of frames in the PAGDecoder. Note that the value may change if the
     * associated PAGComposition was modified.
     */
    public func numFrames(): Int64 {
        unsafe {
            let num: Int64 = cj_PAGDecoder_numFrames(nativeContext)
            return num
        }
    }

    /**
     * Returns the frame rate of decoded image frames. The value may change if the associated
     * PAGComposition was modified.
     */
    public func frameRate(): Float32 {
        unsafe {
            let num: Float32 = cj_PAGDecoder_frameRate(nativeContext)
            return num
        }
    }

    /**
     * Returns true if the frame at the given index has changed since the last copyFrameTo(),
     * readFrameTo(), or frameAtIndex() call. The caller should skip the corresponding call
     * if the frame has not changed.
     */
    public func checkFrameChanged(index: Int64): Bool {
        unsafe {
            let flag: Bool = cj_PAGDecoder_checkFrameChanged(nativeContext, index)
            return flag
        }
    }

    public func readFrame(index: Int64): Option<PixelMap> {
        unsafe {
            let res: CJPixelMap = cj_PAGDecoder_readFrame(nativeContext, index)
            let size: Int64 = res.size
            let buf: CPointer<UInt8> = res.buf
            if (size <= 0 || buf.isNull()) {
                return None
            }
            var alphaType: AlphaType = getAlphaType(res.alphaType)
            var editable: Bool = res.editable
            var pixelFormat: PixelMapFormat = getPixelMapFormat(res.pixelFormat)
            var height: Int32 = res.height
            var width: Int32 = res.width
            let bytes: Array<Byte> = Array<Byte>(size, repeat: 0)
            for (i in 0..size) {
                bytes[i] = buf.read(i)
            }
            free_CPointer_UInt8(buf)
            let opts: InitializationOptions = InitializationOptions(
                alphaType: alphaType,
                editable: editable,
                pixelFormat: pixelFormat,
                size: Size(height: height, width: width)
            )
            let pixelMap: PixelMap = createPixelMap(bytes, opts)
            return pixelMap
        }
    }

    /**
     * Free up resources used by the PAGDecoder instance immediately instead of relying on the
     * garbage collector to do this for you at some point in the future.
     */
    public func release(): Unit {
        nativeRelease()
        nativeContext = 0
    }

    protected func finalize(): Unit {
        nativeFinalize()
    }

    private func nativeRelease(): Unit {
        unsafe {
            cj_PAGDecoder_nativeRelease(nativeContext)
        }
    }

    private func nativeFinalize(): Unit {
        unsafe {
            cj_PAGDecoder_nativeFinalize(nativeContext)
        }
    }
}
