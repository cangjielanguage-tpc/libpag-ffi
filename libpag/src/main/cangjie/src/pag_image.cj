/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

import ohos.ability.*

@FastNative
foreign {
    func cj_PAGImage_FromPath(path: CString): Int64

    func cj_PAGImage_FromBytes(bytes: CPointer<UInt8>, length: Int64): Int64

    func cj_PAGImage_width(ptrCJPAGImage: Int64): Int64

    func cj_PAGImage_height(ptrCJPAGImage: Int64): Int64

    func cj_PAGImage_matrix(ptrCJPAGImage: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGImage_setMatrix(ptrCJPAGImage: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGImage_scaleMode(ptrCJPAGImage: Int64): Int32

    func cj_PAGImage_setScaleMode(ptrCJPAGImage: Int64, mode: Int32): Unit

    func cj_PAGImage_release(ptrCJPAGImage: Int64): Unit

    func cj_PAGImage_FromPixelMap(pixelMap: CJPixelMap): Int64
}

public class PAGImage {
    var ptrCJPAGImage: Int64 = 0

    private init(ptrCJPAGImage: Int64) {
        if (this.ptrCJPAGImage != 0) {
            unsafe {
                cj_PAGImage_release(ptrCJPAGImage)
            }
        }
        this.ptrCJPAGImage = ptrCJPAGImage
    }

    public prop nativeContext: Int64 {
        get() {
            return this.ptrCJPAGImage
        }
    }

    /**
     * Creates a PAGImage object from a path of a image file, return null if the file does not exist or it's not a valid image file.
     */
    public static func FromPath(path: String): Option<PAGImage> {
        unsafe {
            let p = LibC.mallocCString(path)
            let instanceId = cj_PAGImage_FromPath(p)
            LibC.free(p)
            if (instanceId == 0) {
                return Option<PAGImage>.None;
            }
            return PAGImage(instanceId)
        }
    }

    /**
     * Creates a PAGImage object from the specified byte data, return null if the bytes is empty or it's not a valid image file.
     */
    public static func FromBytes(bytes: Array<UInt8>): Option<PAGImage> {
        unsafe {
            let handle = acquireArrayRawData(bytes)
            let instanceId = cj_PAGImage_FromBytes(handle.pointer, bytes.size)
            releaseArrayRawData(handle)
            if (instanceId == 0) {
                return Option<PAGImage>.None;
            }
            return PAGImage(instanceId)
        }
    }

    /**
     * Creates a PAGImage object from pixelMap, return None if the pixelMap is empty or it's not valid.
     * @param pixelMap - Image pixel class, used for reading or writing image data and obtaining image information.
     * @returns Option<PAGImage> - Successful creation returns PAGImage, failed creation returns None.
     */
    public static func fromPixelMap(pixelMap: PixelMap): Option<PAGImage> {
        unsafe {
            try {
                let nums: Int64 = Int64(pixelMap.getPixelBytesNumber())
                let dst: Array<UInt8> = Array<UInt8>(nums, item: 0)
                pixelMap.readPixelsToBuffer(dst)
                let imageInfo: ImageInfo = pixelMap.getImageInfo()

                let pixelFormat: UInt8 = getPAGColorTypeFromPixelMapFormat(PixelMapFormat.BGRA_8888)

                let handle = acquireArrayRawData(dst)
                let alphaType: UInt8 = 0 // AlphaType.UNKNOWN
                let cjpp: CJPixelMap = CJPixelMap(nums, handle.pointer, alphaType, pixelMap.isEditable, pixelFormat, imageInfo.size.height, imageInfo.size.width)

                let nativeImage = cj_PAGImage_FromPixelMap(cjpp)
                if (nativeImage <= 0) {
                    return Option<PAGImage>.None
                } else {
                    return PAGImage(nativeImage)
                }
            } catch (e: BusinessException) {
                Hilog.error(0, "PAGImage", "FromPixelMap failed, error code: ${e.code}, message: ${e.message}.")
                return Option<PAGImage>.None
            }
        }
    }

    /**
     * Load a pag file from assets, returns null if the file does not exist or the data is not a valid image file.
     */
    public static func LoadFromAssets(manager: ResourceManager, name: String): Option<PAGImage> {
        try {
            let data: Array<UInt8> = manager.getRawFileContent(name)
            let image: Option<PAGImage> = PAGImage.FromBytes(data)
            if (let Some(v) <- image) {
                return image
            } else {
                return Option<PAGImage>.None
            }
        } catch (e: BusinessException) {
            Hilog.error(0, "PAGImage",
                "LoadFromAssets getRawFileContent failed, error code: ${e.code}, message: ${e.message}.")
            return Option<PAGImage>.None
        }
    }

    /**
     * Returns the width in pixels of the image.
     */
    public func width(): Int64 {
        unsafe {
            return cj_PAGImage_width(ptrCJPAGImage)
        }
    }

    /**
     * Returns the height in pixels of the image.
     */
    public func height(): Int64 {
        unsafe {
            return cj_PAGImage_height(ptrCJPAGImage)
        }
    }

    /**
     * Returns the current scale mode.
     */
    public func scaleMode(): Int32 {
        unsafe {
            return cj_PAGImage_scaleMode(ptrCJPAGImage)
        }
    }

    /**
     * Specifies the rule of how to scale the image content to fit the original image size.
     */
    public func setScaleMode(mode: Int32): Unit {
        if (mode != 0 && mode != 1 && mode != 2 && mode != 3) {
            Hilog.error(0, 'PAGImage', "setScaleMode invalid setting");
            return
        }
        unsafe {
            return cj_PAGImage_setScaleMode(ptrCJPAGImage, mode)
        }
    }

    /**
     * Returns a copy of current matrix.
     */
    public func matrix(): Array<Float32> {
        unsafe {
            var values = VArray<Float32, $9>({i => 0.0})
            cj_PAGImage_matrix(ptrCJPAGImage, inout values)
            var data: Array<Float32> = Array<Float32>(6, repeat: 0.0)
            for (i in 0..5) {
                data[i] = values[i]
            }
            return data
        }
    }

    /**
     * Set the transformation which will be applied to the image content.
     */
    public func setMatrix(values: Array<Float32>): Unit {
        if (values.size == 0) {
            Hilog.error(0, 'PAGImage', "setMatrix invalid setting");
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
            cj_PAGImage_setMatrix(ptrCJPAGImage, inout data)
            return
        }
    }

    public func release(): Unit {
        unsafe {
            cj_PAGImage_release(ptrCJPAGImage)
            return
        }
    }
}
