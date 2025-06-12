/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGComposition_Make(width: Int32, height: Int32): Int64

    func cj_PAGComposition_width(ptr: Int64): Int64

    func cj_PAGComposition_height(ptr: Int64): Int64

    func cj_PAGComposition_setContentSize(ptr: Int64, width: Int64, height: Int64): Unit

    func cj_PAGComposition_numChildren(ptr: Int64): Int64

    func cj_PAGComposition_getLayerAt(ptr: Int64, index: Int64): Int64

    func cj_PAGComposition_getLayerIndex(ptr: Int64, nativeLayer: Int64): Int64

    func cj_PAGComposition_setLayerIndex(ptr: Int64, nativeLayer: Int64, index: Int64): Unit

    func cj_PAGComposition_addLayer(ptr: Int64, nativeLayer: Int64): Bool

    func cj_PAGComposition_addLayerAt(ptr: Int64, nativeLayer: Int64, index: Int64): Bool

    func cj_PAGComposition_contains(ptr: Int64, nativeLayer: Int64): Bool

    func cj_PAGComposition_removeLayer(ptr: Int64, nativeLayer: Int64): Int64

    func cj_PAGComposition_removeLayerAt(ptr: Int64, index: Int64): Int64

    func cj_PAGComposition_removeAllLayers(ptr: Int64): Unit

    func cj_PAGComposition_swapLayer(ptr: Int64, pagLayer1: Int64, pagLayer2: Int64): Unit

    func cj_PAGComposition_swapLayerAt(ptr: Int64, index1: Int64, index2: Int64): Unit

    func cj_PAGComposition_audioBytes(ptr: Int64): CJBytesArray

    func cj_PAGComposition_audioStartTime(ptr: Int64): Int64

    func cj_PAGComposition_audioMarkers(ptr: Int64): MarkersPAGLayer

    func cj_PAGComposition_getLayersByName(ptr: Int64, layerName: CString): CJInt64Array

    func cj_PAGComposition_getLayersUnderPoint(ptr: Int64, localX: Float32, localY: Float32): CJInt64Array
}

public open class PAGComposition <: PAGLayer {
    init(nativeLayer: Int64) {
        super(nativeLayer)
    }

    public func getNativeComposition(): Int64 {
        return this.ptr
    }

    /**
     * Create an empty PAGComposition with a specified size.
     */
    public static func make(width: Int32, height: Int32): Option<PAGComposition> {
        unsafe {
            let native: Int64 = cj_PAGComposition_Make(width, height)
            if (native <= 0) {
                return None
            }
            return PAGComposition(native)
        }
    }

    /**
     * Return the width of the composition.
     */
    public func width(): Int64 {
        unsafe {
            return cj_PAGComposition_width(ptr)
        }
    }

    /**
     * Return the height of the composition.
     */
    public func height(): Int64 {
        unsafe {
            return cj_PAGComposition_height(ptr)
        }
    }

    /**
     * Set the size of the composition.
     */
    public func setContentSize(width: Int64, height: Int64): Unit {
        unsafe {
            cj_PAGComposition_setContentSize(ptr, width, height)
        }
    }

    /**
     * Return the values of the sub layers of this combination.
     */
    public func numChildren(): Int64 {
        unsafe {
            return cj_PAGComposition_numChildren(ptr)
        }
    }

    /**
     * Returns the child layer that exists at the specified index.
     * @param index - The index position of the sub layer.
     * @return Type of PAGLayer, Specify the sub layer of the index location.
     */
    public func getLayerAt(index: Int64): Option<PAGLayer> {
        unsafe {
            let native: Int64 = cj_PAGComposition_getLayerAt(ptr, index)
            if (native <= 0) {
                Hilog.error(0, "[PAGComposition]",
                    "[getLayerAt]-The child layer at the specified index position is error.")
                return None
            }
            return PAGUtils.WarpJPAGLayer(native)
        }
    }

    /**
     * Return the index position of the sub layer.
     * @ param layer - The layer instance to be identified.
     * @return Type of Int64, The index position of the sub layer to be identified.
     */
    public func getLayerIndex(layer: PAGLayer): Int64 {
        unsafe {
            return cj_PAGComposition_getLayerIndex(ptr, layer.nativeLayer)
        }
    }

    /**
     * Change the position of existing sub items in the container. This will affect the layering of sub layers.
     * @ param layer - The sub layer where the index needs to be changed.
     * @ param index - The result index of the sub layer.
     */
    public func setLayerIndex(layer: PAGLayer, index: Int64): Unit {
        unsafe {
            cj_PAGComposition_setLayerIndex(ptr, layer.nativeLayer, index)
        }
    }

    /**
     * Add PAGLayer to the current PAGComposition at the top.
     */
    public func addLayer(pagLayer: PAGLayer): Bool {
        unsafe {
            return cj_PAGComposition_addLayer(ptr, pagLayer.nativeLayer)
        }
    }

    /**
     * Add PAGLayer to the current PAGComposition at the specified index.
     */
    public func addLayerAt(pagLayer: PAGLayer, index: Int64): Bool {
        unsafe {
            return cj_PAGComposition_addLayerAt(ptr, pagLayer.nativeLayer, index)
        }
    }

    /**
     * Check if the current PAGComposition contains the specified pagLayer.
     */
    public func contains(pagLayer: PAGLayer): Bool {
        unsafe {
            return cj_PAGComposition_contains(ptr, pagLayer.nativeLayer)
        }
    }

    /**
     * Remove the specified PAGLayer from the current PAGComposition.
     */
    public func removeLayer(pagLayer: PAGLayer): Option<PAGLayer> {
        unsafe {
            let result: Int64 = cj_PAGComposition_removeLayer(ptr, pagLayer.nativeLayer)
            if (result <= 0) {
                return None
            }
            return PAGUtils.WarpJPAGLayer(result)
        }
    }

    /**
     * Remove the PAGLayer at the specified index from the current PAGComposition.
     */
    public func removeLayerAt(index: Int64): Option<PAGLayer> {
        unsafe {
            let result: Int64 = cj_PAGComposition_removeLayerAt(ptr, index)
            if (result <= 0) {
                return None
            }
            return PAGUtils.WarpJPAGLayer(result)
        }
    }

    /**
     * Remove all PAG layers from the current PAGComposition.
     */
    public func removeAllLayers(): Unit {
        unsafe {
            cj_PAGComposition_removeAllLayers(ptr)
        }
    }

    /**
     * Swap layers.
     */
    public func swapLayer(pagLayer1: PAGLayer, pagLayer2: PAGLayer): Unit {
        unsafe {
            cj_PAGComposition_swapLayer(ptr, pagLayer1.nativeLayer, pagLayer2.nativeLayer)
        }
    }

    /**
     * Swap layers at the specified index.
     */
    public func swapLayerAt(index1: Int64, index2: Int64): Unit {
        unsafe {
            cj_PAGComposition_swapLayerAt(ptr, index1, index2)
        }
    }

    /**
     * The audio data of this work is AAC audio in an MPEG-4 container.
     */
    public func audioBytes(): Array<UInt8> {
        unsafe {
            let res: CJBytesArray = cj_PAGComposition_audioBytes(ptr)
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

    /**
     * Indicate when the first frame of the audio is played in the timeline of the music piece.
     */
    public func audioStartTime(): Int64 {
        unsafe {
            return cj_PAGComposition_audioStartTime(ptr)
        }
    }

    /**
     * Return the audio label of this song.
     */
    public func audioMarkers(): Array<PAGMarker> {
        unsafe {
            let res: MarkersPAGLayer = cj_PAGComposition_audioMarkers(ptr)
            let size: Int64 = res.size
            let markers: CPointer<CJMarker> = res.markers
            let pagMarkers: Array<PAGMarker> = Array<PAGMarker>(size, repeat: PAGMarker(0, 0, ""))
            for (i in 0..size) {
                let marker: CJMarker = markers.read(i)
                let mComment: CString = marker.mComment
                let pagMarker: PAGMarker = PAGMarker(marker.mStartTime, marker.mDuration, mComment.toString())
                LibC.free(mComment)
                pagMarkers[i] = pagMarker
            }
            free_CPointer_CJMarker(markers)
            return pagMarkers
        }
    }

    /**
     * Returns an array of layers that match the specified layer name.
     */
    public func getLayersByName(layerName: String): Array<PAGLayer> {
        unsafe {
            let ln = LibC.mallocCString(layerName)
            let res: CJInt64Array = cj_PAGComposition_getLayersByName(ptr, ln)
            let size: Int64 = res.size
            let buf: CPointer<Int64> = res.buf
            let bytes: Array<Int64> = Array<Int64>(size, repeat: 0)
            for (i in 0..size) {
                if (buf.isNotNull()) {
                    bytes[i] = buf.read(i)
                }
            }
            LibC.free(ln)
            free_CPointer_Int64(buf)

            return PAGUtils.WarpJPAGLayers(bytes)
        }
    }

    /**
     * Return the layer array located below the specified point. This point is measured in pixels and comes from the local coordinates of the PAG combination.
     */
    public func getLayersUnderPoint(localX: Float32, localY: Float32): Array<PAGLayer> {
        unsafe {
            let res: CJInt64Array = cj_PAGComposition_getLayersUnderPoint(ptr, localX, localY)
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
}
