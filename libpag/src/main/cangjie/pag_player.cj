/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGPlayer_createPAGPlayer(): Int64

    func cj_PAGPlayer_setComposition(jView: Int64, ptrComposition: Int64): Unit

    func cj_PAGPlayer_setSurface(ptrCJPAGPlayer: Int64, ptrCJPAGSurface: Int64): Unit

    func cj_PAGPlayer_videoEnabled(ptrCJPAGPlayer: Int64): Bool

    func cj_PAGPlayer_setVideoEnabled(ptrCJPAGPlayer: Int64, value: Bool): Unit

    func cj_PAGPlayer_cacheEnabled(ptrCJPAGPlayer: Int64): Bool

    func cj_PAGPlayer_setCacheEnabled(ptrCJPAGPlayer: Int64, value: Bool): Unit

    func cj_PAGPlayer_useDiskCache(ptrCJPAGPlayer: Int64): Bool

    func cj_PAGPlayer_setUseDiskCache(ptrCJPAGPlayer: Int64, value: Bool): Unit

    func cj_PAGPlayer_cacheScale(ptrCJPAGPlayer: Int64): Float32

    func cj_PAGPlayer_setCacheScale(ptrCJPAGPlayer: Int64, value: Float32): Unit

    func cj_PAGPlayer_maxFrameRate(ptrCJPAGPlayer: Int64): Float32

    func cj_PAGPlayer_setMaxFrameRate(ptrCJPAGPlayer: Int64, value: Float32): Unit

    func cj_PAGPlayer_scaleMode(ptrCJPAGPlayer: Int64): Int32

    func cj_PAGPlayer_setScaleMode(ptrCJPAGPlayer: Int64, value: Int32): Unit

    func cj_PAGPlayer_matrix(ptrCJPAGPlayer: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGPlayer_setMatrix(ptrCJPAGPlayer: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGPlayer_duration(ptrCJPAGPlayer: Int64): Float64

    func cj_PAGPlayer_getProgress(ptrCJPAGPlayer: Int64): Float64

    func cj_PAGPlayer_setProgress(ptrCJPAGPlayer: Int64, value: Float64): Unit

    func cj_PAGPlayer_currentFrame(ptrCJPAGPlayer: Int64): Int64

    func cj_PAGPlayer_prepare(ptrCJPAGPlayer: Int64): Unit

    func cj_PAGPlayer_flush(ptrCJPAGPlayer: Int64): Bool

    func cj_PAGPlayer_getBounds(ptrCJPAGPlayer: Int64, ptrCJPAGLayerHandle: Int64, values: VArray<Float32, $4>): Unit

    func cj_PAGPlayer_getLayersUnderPoint(ptrCJPAGPlayer: Int64, surfaceX: Float32, surfaceY: Float32): CJInt64Array

    func cj_PAGPlayer_hitTestPoint(ptrCJPAGPlayer: Int64, ptrCJPAGLayerHandle: Int64, surfaceX: Float32,
        surfaceY: Float32, pixelHitTest: Bool): Bool

    func cj_PAGPlayer_release(ptrCJPAGPlayer: Int64): Unit
}

public class PAGPlayer {
    private var ptrCJPAGPlayer: Int64 = 0
    private var pagSurface: Option<PAGSurface> = Option<PAGSurface>.None
    private var composition: Option<PAGComposition> = None

    public init() {
        unsafe {
            this.ptrCJPAGPlayer = cj_PAGPlayer_createPAGPlayer()
        }
    }

    /**
     * Returns the current PAGComposition for PAGPlayer to render as content.
     */
    public func getComposition(): Option<PAGComposition> {
        return this.composition
    }

    /**
     * Sets a new PAGComposition for PAGPlayer to render as content.
     * Note: If the composition is already added to another PAGPlayer, it will be removed from the
     * previous PAGPlayer.
     */
    public func setComposition(composition: Option<PAGComposition>): Unit {
        unsafe {
            if (let Some(v) <- this.composition) {
                v.nativeRelease()
            }
            this.composition = composition
            if (composition.isNone()) {
                cj_PAGPlayer_setComposition(ptrCJPAGPlayer, 0)
            } else {
                if (let Some(v) <- composition) {
                    let native: Int64 = v.getNativeComposition()
                    cj_PAGPlayer_setComposition(ptrCJPAGPlayer, native)
                }
            }
        }
        return
    }

    /*
     * Returns the PAGSurface object for PAGPlayer to render onto.
     */
    public func getSurface(): Option<PAGSurface> {
        return this.pagSurface
    }

    /*
     * Set the PAGSurface object for PAGPlayer to render onto.
     */
    public func setSurface(surface: Option<PAGSurface>): Unit {
        unsafe {
            if (let Some(v) <- this.pagSurface) {
                v.release()
            }
            this.pagSurface = surface
            if (surface.isNone()) {
                cj_PAGPlayer_setSurface(ptrCJPAGPlayer, 0)
            } else {
                cj_PAGPlayer_setSurface(ptrCJPAGPlayer, surface.getOrThrow().getCID())
            }
        }
    }

    /*
     * If set to false, the player skips rendering for video composition.
     */
    public func videoEnabled(): Bool {
        unsafe {
            return cj_PAGPlayer_videoEnabled(ptrCJPAGPlayer)
        }
    }

    /*
     * Set the value of videoEnabled property.
     */
    public func setVideoEnabled(value: Bool): Unit {
        unsafe {
            cj_PAGPlayer_setVideoEnabled(ptrCJPAGPlayer, value)
        }
    }

    /*
     * If set to true, PAGPlayer caches an internal bitmap representation of the static content for each layer. This
     * caching can increase performance for layers that contain complex vector content. The execution speed can be
     * significantly faster depending on the complexity of the content, but it requires extra graphics memory. The
     * default value is true.
     */
    public func cacheEnabled(): Bool {
        unsafe {
            return cj_PAGPlayer_cacheEnabled(ptrCJPAGPlayer)
        }
    }

    /*
     * Set the value of cacheEnabled property.
     */
    public func setCacheEnabled(value: Bool): Unit {
        unsafe {
            cj_PAGPlayer_setCacheEnabled(ptrCJPAGPlayer, value)
        }
    }

    /*
     * If set to true, PAG will cache the associated rendering data into a disk file, such as the decoded image frames
     * of video compositions.This can help reduce memory usage and improve rendering performance.
     */
    public func useDiskCache(): Bool {
        unsafe {
            return cj_PAGPlayer_useDiskCache(ptrCJPAGPlayer)
        }
    }

    /*
     * Set the value of useDiskCache property.
     */
    public func setUseDiskCache(value: Bool): Unit {
        unsafe {
            cj_PAGPlayer_setUseDiskCache(ptrCJPAGPlayer, value)
        }
    }

    /*
     * This value defines the scale factor for internal graphics caches, ranges from 0.0 to 1.0.The scale factors less
     * than 1.0 may result in blurred output, but it can reduce the usage of graphics memory which leads to better
     * performance. The default value is 1.0.
     */
    public func cacheScale(): Float32 {
        unsafe {
            return cj_PAGPlayer_cacheScale(ptrCJPAGPlayer)
        }
    }

    /*
     * Set the value of cacheScale property.
     */
    public func setCacheScale(value: Float32): Unit {
        unsafe {
            cj_PAGPlayer_setCacheScale(ptrCJPAGPlayer, value)
        }
    }

    /**
     * The maximum frame rate for rendering, ranges from 1 to 60. If set to a value less than the
     * actual frame rate from composition, it drops frames but increases performance. Otherwise, it
     * has no effect. The default value is 60.
     */
    public func maxFrameRate(): Float32 {
        unsafe {
            return cj_PAGPlayer_maxFrameRate(ptrCJPAGPlayer)
        }
    }

    /*
     * Set the maximum frame rate for rendering.
     */
    public func setMaxFrameRate(value: Float32): Unit {
        if (value <= 0.0) {
            Hilog.error(0, 'PAGPlayer', "setMaxFrameRate value range needs to be greater than 0.0");
            return
        }
        unsafe {
            cj_PAGPlayer_setMaxFrameRate(ptrCJPAGPlayer, value)
        }
    }

    /*
     * Returns the current scale mode.
     */
    public func scaleMode(): PAGScaleMode {
        unsafe {
            let mode = cj_PAGPlayer_scaleMode(ptrCJPAGPlayer)
            return PAGScaleMode.int32ToMode(mode)
        }
    }

    /**
     * Specifies the rule of how to scale the pag content to fit the surface size. The matrix
     * changes when this method is called.
     */
    public func setScaleMode(mode: PAGScaleMode): Unit {
        var value = PAGScaleMode.modeToInt32(mode)
        unsafe {
            cj_PAGPlayer_setScaleMode(ptrCJPAGPlayer, value)
        }
    }

    /**
     * Returns a copy of current matrix.
     */
    public func matrix(): Array<Float32> {
        unsafe {
            var values = VArray<Float32, $9>({i => 0.0})
            cj_PAGPlayer_matrix(ptrCJPAGPlayer, inout values)
            var data: Array<Float32> = Array<Float32>(6, repeat: 0.0)
            for (i in 0..6) {
                data[i] = values[i]
            }
            return data
        }
    }

    /**
     * Sets the transformation which will be applied to the composition.The scaleMode property will be set to
     * PAGScaleMode::None when this method is called.
     */
    public func setMatrix(values: Array<Float32>): Unit {
        if (values.size == 0) {
            Hilog.error(0, 'PAGPlayer', "setMatrix invalid setting");
            return
        }
        unsafe {
            var data: VArray<Float32, $9> = VArray<Float32, $9>({i => 0.0})
            for (i in 0..values.size) {
                if (i > 5) {
                    break
                }
                data[i] = values[i]
            }
            cj_PAGPlayer_setMatrix(ptrCJPAGPlayer, inout data)
            return
        }
    }

    /*
     * The duration of current composition in microseconds.
     */
    public func duration(): Float64 {
        unsafe {
            return cj_PAGPlayer_duration(ptrCJPAGPlayer)
        }
    }

    /*
     * Returns the current progress of play position, the value is from 0.0 to 1.0.
     */
    public func getProgress(): Float64 {
        unsafe {
            return cj_PAGPlayer_getProgress(ptrCJPAGPlayer)
        }
    }

    /**
     * Sets the progress of play position, the value ranges from 0.0 to 1.0. It is applied only when
     * the composition is not null.
     */
    public func setProgress(value: Float64): Unit {
        unsafe {
            return cj_PAGPlayer_setProgress(ptrCJPAGPlayer, value)
        }
    }

    /*
     * Returns the current frame.
     */
    public func currentFrame(): Int64 {
        unsafe {
            return cj_PAGPlayer_currentFrame(ptrCJPAGPlayer)
        }
    }

    /**
     * Prepares the player for the next flush() call. It collects all CPU tasks from the current
     * progress of the composition and runs them asynchronously in parallel. It is usually used for
     * speeding up the first frame rendering.
     */
    public func prepare(): Unit {
        unsafe {
            return cj_PAGPlayer_prepare(ptrCJPAGPlayer)
        }
    }

    /*
     * Apply all pending changes to the target surface immediately.Returns true if the content has changed.
     */
    public func flush(): Bool {
        unsafe {
            return cj_PAGPlayer_flush(ptrCJPAGPlayer)
        }
    }

    /**
     * Returns a rectangle in pixels that defines the displaying area of the specified layer, which
     * is in the coordinate of the PAGSurface.
     */
    public func getBounds(layer: PAGLayer): Array<Float32> {
        unsafe {
            var values = VArray<Float32, $4>({i => 0.0})
            cj_PAGPlayer_getBounds(ptrCJPAGPlayer, layer.getptr(), inout values)
            var data: Array<Float32> = Array<Float32>(4, repeat: 0.0)
            for (i in 0..data.size) {
                data[i] = values[i]
            }
            return data
        }
    }

    /**
     * Returns an array of layers that lie under the specified point. The point is in pixels and
     * from the surface's coordinates.
     */
    public func getLayersUnderPoint(surfaceX: Float32, surfaceY: Float32): Array<PAGLayer> {
        unsafe {
            let res: CJInt64Array = cj_PAGPlayer_getLayersUnderPoint(ptrCJPAGPlayer, surfaceX, surfaceY)
            let size: Int64 = res.size
            let buf: CPointer<Int64> = res.buf
            let bytes: Array<Int64> = Array<Int64>(size, repeat: 0)
            for (i in 0..size) {
                if (buf.isNotNull()) {
                    bytes[i] = buf.read(i)
                }
            }
            free_CPointer_Int64(buf)
            return PAGUtils.WarpJPAGLayers(bytes)
        }
    }

    /**
     * Evaluates the PAGLayer to see if it overlaps or intersects with the specified point. The point
     * is in the coordinate space of the PAGSurface, not the PAGComposition that contains the
     * PAGLayer. It always returns false if the PAGLayer or its parent (or parent's parent...) has not
     * been added to this PAGPlayer. The pixelHitTest parameter indicates whether or not to check
     * against the actual pixels of the object (true) or the bounding box (false). Returns true if the
     * PAGLayer overlaps or intersects with the specified point.
     */
    public func hitTestPoint(layer: Option<PAGLayer>, surfaceX: Float32, surfaceY: Float32, pixelHitTest: Bool): Bool {
        unsafe {
            return cj_PAGPlayer_hitTestPoint(ptrCJPAGPlayer, layer.getOrThrow().getptr(), surfaceX, surfaceY,
                pixelHitTest)
        }
    }

    /**
     * Free up resources used by the PAGPlayer instance immediately instead of relying on the
     * garbage collector to do this for you at some point in the future.
     */
    public func release(): Unit {
        unsafe {
            cj_PAGPlayer_release(ptrCJPAGPlayer)
            ptrCJPAGPlayer = 0
        }
    }
}
