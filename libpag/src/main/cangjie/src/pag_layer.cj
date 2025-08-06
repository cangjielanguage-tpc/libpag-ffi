/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGLayer_make(bytes: CPointer<UInt8>, length: Int64, filePath: CString, password: CString): Int64

    func cj_PAGLayer_makeByURL(filePath: CString, password: CString): Int64

    func cj_PAGLayer_layerType(ptr: Int64): Int8

    func cj_PAGLayer_layerName(ptr: Int64): CJBytesArray

    func cj_PAGLayer_matrix(ptr: Int64, buf: VArray<Float32, $9>): Unit

    func cj_PAGLayer_setMatrix(ptr: Int64, buf: CPointer<Float32>): Unit

    func cj_PAGLayer_resetMatrix(ptr: Int64): Unit

    func cj_PAGLayer_getTotalMatrix(ptr: Int64, buf: VArray<Float32, $9>): Unit

    func cj_PAGLayer_visible(ptr: Int64): Bool

    func cj_PAGLayer_setVisible(ptr: Int64, value: Bool): Unit

    func cj_PAGLayer_editableIndex(ptr: Int64): Int32

    func cj_PAGLayer_parent(ptr: Int64): Int64

    func cj_PAGLayer_markers(ptr: Int64): MarkersPAGLayer

    func cj_PAGLayer_localTimeToGlobal(ptr: Int64, localTime: Int64): Int64

    func cj_PAGLayer_globalToLocalTime(ptr: Int64, globalTime: Int64): Int64

    func cj_PAGLayer_duration(ptr: Int64): Int64

    func cj_PAGLayer_frameRate(ptr: Int64): Float32

    func cj_PAGLayer_startTime(ptr: Int64): Int64

    func cj_PAGLayer_setStartTime(ptr: Int64, time: Int64): Unit

    func cj_PAGLayer_currentTime(ptr: Int64): Int64

    func cj_PAGLayer_setCurrentTime(ptr: Int64, time: Int64): Unit

    func cj_PAGLayer_getProgress(ptr: Int64): Float64

    func cj_PAGLayer_setProgress(ptr: Int64, value: Float64): Unit

    func cj_PAGLayer_isPAGFile(ptr: Int64): Bool

    func cj_PAGLayer_trackMatteLayer(ptr: Int64): Int64

    func cj_PAGLayer_getBounds(ptr: Int64): CPointer<Float32>

    func cj_PAGLayer_excludedFromTimeline(ptr: Int64): Bool

    func cj_PAGLayer_setExcludedFromTimeline(ptr: Int64, value: Bool): Unit

    func cj_PAGLayer_nativeEquals(ptr: Int64, otherptr: Int64): Bool

    func cj_PAGLayer_nativeRelease(ptr: Int64): Unit

    func cj_PAGLayer_isNullptr(ptr: Int64): Bool
}

public open class PAGLayer {
    // Binding with C code, the object pointer returned by C code.
    protected var ptr: Int64

    protected var isRelease: Bool = false

    init(ptr: Int64) {
        this.ptr = ptr
    }

    public prop nativeLayer: Int64 {
        get() {
            return this.ptr
        }
    }

    protected func getptr(): Int64 {
        return this.ptr
    }

    protected static func makeEmptyPAGLayer(): PAGLayer {
        return PAGLayer(0)
    }

    /**
     *  Load the PAG file from byte data, and return null if the byte is empty or not a valid PAG file.
     */
    protected static func makePAGLayer(bytes: Array<UInt8>, length: Int64, filePath!: String = "", password!: String = ""): Option<PAGLayer> {
        unsafe {
            let handle = acquireArrayRawData(bytes)
            let fp = LibC.mallocCString(filePath)
            let pw = LibC.mallocCString(password)
            let native: Int64 = cj_PAGLayer_make(handle.pointer, length, fp, pw)
            LibC.free(fp)
            LibC.free(pw)
            releaseArrayRawData(handle)
            if (native <= 0) {
                return None
            }
            return PAGLayer(native)
        }
    }

    /**
     *  Load the PAG file from the path, and return null if the file does not exist or the data is not a PAG file.
     */
    protected static func makePAGLayer(filePath: String, password!: String = ""): Option<PAGLayer> {
        unsafe {
            let fp = LibC.mallocCString(filePath)
            let pw = LibC.mallocCString(password)
            let native: Int64 = cj_PAGLayer_makeByURL(fp, pw)
            LibC.free(fp)
            LibC.free(pw)
            if (native <= 0) {
                return None
            }
            return PAGLayer(native)
        }
    }

    /**
     * Return the type of layer.
     */
    public func layerType(): PAGLayerType {
        unsafe {
            let value = cj_PAGLayer_layerType(ptr)
            return PAGLayerType.int8ToType(value)
        }
    }

    protected static func getLayerType(nativeLayer: Int64): Int8 {
        unsafe {
            return cj_PAGLayer_layerType(nativeLayer)
        }
    }

    /**
     * Return the name of the layer.
     */
    public func layerName(): String {
        unsafe {
            let res: CJBytesArray = cj_PAGLayer_layerName(ptr)
            let str = BytesArrayToString(res)
            free_CJBytesArray(res)
            return str
        }
    }

    /**
     * A matrix object containing values that alter the scaling, rotation, and translation of the layer.
     * Altering it does not change the animation matrix, and it will be concatenated to current animation matrix for
     * displaying.
     */
    public func matrix(): Matrix4 {
        unsafe {
            var res: VArray<Float32, $9> = VArray<Float32, $9>({i => 0.0})
            cj_PAGLayer_matrix(ptr, inout res)
            let buf: Array<Float32> = [res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7], res[8]]
            return PAGUtils.ToTsMatrix(buf)
        }
    }

    /**
     * A matrix object containing values that alter the scaling, rotation, and translation of the layer.
     * Altering it does not change the animation matrix, and it will be concatenated to current animation matrix for
     * displaying.
     */
    public func setMatrix(matrix: Matrix4): Unit {
        unsafe {
            let buf: Array<Float32> = PAGUtils.ToNativeMatrix(matrix)
            let handle = acquireArrayRawData(buf)
            cj_PAGLayer_setMatrix(ptr, handle.pointer)
            releaseArrayRawData(handle)
        }
    }

    /**
     * Resets the matrix to its default value.
     */
    public func resetMatrix(): Unit {
        unsafe {
            cj_PAGLayer_resetMatrix(ptr)
        }
    }

    /**
     * The final matrix for displaying, it is the combination of the matrix property and current matrix from animation.
     */
    public func getTotalMatrix(): Matrix4 {
        unsafe {
            var res: VArray<Float32, $9> = VArray<Float32, $9>({i => 0.0})
            cj_PAGLayer_getTotalMatrix(ptr, inout res)
            let buf: Array<Float32> = [res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7], res[8]]
            return PAGUtils.ToTsMatrix(buf)
        }
    }

    /**
     * Whether or not the layer is visible.
     */
    public func visible(): Bool {
        unsafe {
            return cj_PAGLayer_visible(ptr)
        }
    }

    public func setVisible(value: Bool): Unit {
        unsafe {
            cj_PAGLayer_setVisible(ptr, value)
        }
    }

    /**
     * Ranges from 0 to PAGFile.numTexts - 1 if the layer type is text, or from 0 to PAGFile.numImages -1 if the
     * layer type is image, otherwise returns -1.
     */
    public func editableIndex(): Int32 {
        unsafe {
            return cj_PAGLayer_editableIndex(ptr)
        }
    }

    /**
     * Indicates the Container instance that contains this Node instance.
     */
    public func parent(): Option<PAGComposition> {
        unsafe {
            let native: Int64 = cj_PAGLayer_parent(ptr)
            if (native > 0) {
                return PAGComposition(native)
            } else {
                return None
            }
        }
    }

    /**
     * Returns the markers of this layer.
     */
    public func markers(): Array<PAGMarker> {
        unsafe {
            let res: MarkersPAGLayer = cj_PAGLayer_markers(ptr)
            let size: Int64 = res.size
            let markers: CPointer<CJMarker> = res.markers
            let pagMarkers: Array<PAGMarker> = Array<PAGMarker>(size, repeat: PAGMarker(0, 0, ""))
            for (i in 0..size) {
                let marker: CJMarker = markers.read(i)
                let mComment: String = BytesArrayToString(marker.mComment)
                free_CJBytesArray(marker.mComment)
                let pagMarker: PAGMarker = PAGMarker(marker.mStartTime, marker.mDuration, mComment)
                pagMarkers[i] = pagMarker
            }
            free_CPointer_CJMarker(markers)
            return pagMarkers
        }
    }

    /**
     * Converts the time from the PAGLayer's (local) timeline to the PAGSurface (global) timeline. The time is in
     * microseconds.
     */
    public func localTimeToGlobal(localTime: Int64): Int64 {
        unsafe {
            return cj_PAGLayer_localTimeToGlobal(ptr, localTime)
        }
    }

    /**
     * Converts the time from the PAGSurface (global) to the PAGLayer's (local) timeline timeline. The time is in
     * microseconds.
     */
    public func globalToLocalTime(globalTime: Int64): Int64 {
        unsafe {
            return cj_PAGLayer_globalToLocalTime(ptr, globalTime)
        }
    }

    /**
     * The duration of the layer in microseconds, indicates the length of the visible range.
     */
    public func duration(): Int64 {
        unsafe {
            return cj_PAGLayer_duration(ptr)
        }
    }

    /**
     * Returns the frame rate of this layer.
     */
    public func frameRate(): Float32 {
        unsafe {
            return cj_PAGLayer_frameRate(ptr)
        }
    }

    /**
     * The start time of the layer in microseconds, indicates the start position of the visible range. It could be a negative value.
     */
    public func startTime(): Int64 {
        unsafe {
            return cj_PAGLayer_startTime(ptr)
        }
    }

    /**
     * Set the start time of the layer, in microseconds.
     */
    public func setStartTime(time: Int64): Unit {
        unsafe {
            cj_PAGLayer_setStartTime(ptr, time)
        }
    }

    /**
     * The current time of the layer in microseconds, the layer is invisible if currentTime is not in the visible range
     * {@code (startTime <= currentTime < startTime + duration)}.
     */
    public func currentTime(): Int64 {
        unsafe {
            return cj_PAGLayer_currentTime(ptr)
        }
    }

    /**
     * Set the current time of the layer in microseconds.
     */
    public func setCurrentTime(time: Int64): Unit {
        unsafe {
            cj_PAGLayer_setCurrentTime(ptr, time)
        }
    }

    /**
     * Returns the current progress of play position, the value is from 0.0 to 1.0.
     */
    public func getProgress(): Float64 {
        unsafe {
            return cj_PAGLayer_getProgress(ptr)
        }
    }

    /**
     * Set the progress of play position, the value ranges from 0.0 to 1.0. A value of 0.0 represents the
     * frame at startTime. A value of 1.0 represents the frame at the end of duration.
     */
    public func setProgress(value: Float64): Unit {
        unsafe {
            cj_PAGLayer_setProgress(ptr, value)
        }
    }

    protected func isPAGFile(): Bool {
        unsafe {
            return cj_PAGLayer_isPAGFile(ptr)
        }
    }

    // The incoming pointer is from the C side
    protected static func isPAGFileOfPAGLayer(nativeLayer: Int64): Bool {
        unsafe {
            return cj_PAGLayer_isPAGFile(nativeLayer)
        }
    }

    /**
     * Returns trackMatte layer of this layer.
     */
    public func trackMatteLayer(): Option<PAGLayer> {
        unsafe {
            let native: Int64 = cj_PAGLayer_trackMatteLayer(ptr)
            if (native > 0) {
                return PAGUtils.WarpJPAGLayer(native)
            } else {
                return None
            }
        }
    }

    /**
     * Returns a rectangle in pixels that defines the original area of the layer, which is not
     * transformed by the matrix.
     */
    public func getBounds(): Rect {
        unsafe {
            let res: CPointer<Float32> = cj_PAGLayer_getBounds(ptr)
            let bounds: Array<Float32> = Array<Float32>(4, repeat: 0.0)
            if (res.isNotNull()) {
                for (i in 0..4) {
                    bounds[i] = res.read(i)
                }
            }
            free_CPointer_Float32(res)

            return PAGUtils.ToTsRect(bounds)
        }
    }

    /**
     * Indicate whether this layer is excluded from parent's timeline. If set to true, this layer's current time
     * will not change when parent's current time changes.
     */
    public func excludedFromTimeline(): Bool {
        unsafe {
            return cj_PAGLayer_excludedFromTimeline(ptr)
        }
    }

    /**
     * Set the excludedFromTimeline flag of this layer.
     */
    public func setExcludedFromTimeline(value: Bool): Unit {
        unsafe {
            cj_PAGLayer_setExcludedFromTimeline(ptr, value)
        }
    }

    protected func nativeRelease(): Unit {
        unsafe {
            cj_PAGLayer_nativeRelease(ptr)
        }
    }

    protected func finalize(): Unit {
        nativeRelease()
    }

    private func nativeEquals(other: PAGLayer): Bool {
        unsafe {
            return cj_PAGLayer_nativeEquals(ptr, other.getptr())
        }
    }

    public func equals(obj: PAGLayer): Bool {
        if (refEq(this, obj)) {
            return true
        }
        return nativeEquals(obj)
    }

    protected func hashCode(): Int64 {
        return 31 * 17 + (ptr ^ (ptr >> 32))
    }

    public func isNullptr(): Bool {
        unsafe {
            return cj_PAGLayer_isNullptr(ptr)
        }
    }
}
