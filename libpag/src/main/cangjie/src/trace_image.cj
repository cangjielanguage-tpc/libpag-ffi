/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.image.Image as MultiImage
internal import ohos.image.Component as ImageComponent
internal import ohos.image.PixelMap
internal import ohos.image.createImageSource
internal import ohos.image.DecodingOptions
internal import ohos.image.Size
internal import ohos.image.PixelMapFormat
internal import ohos.image.Region
internal import ohos.image.ImageInfo
internal import ohos.image.InitializationOptions
internal import ohos.image.createPixelMap
internal import ohos.hilog.*

public class TraceImage {
    public static func trace(tag: String, byteBuffer: Array<UInt8>, width: Int64, height: Int64): Unit {
        let color: Array<UInt8> = Array<UInt8>(height * width * 4, repeat: 0)
        let opts: InitializationOptions = InitializationOptions(editable: true, pixelFormat: RGBA_8888,
            size: Size(height: Int32(height), width: Int32(width)))
        let pixelMap: PixelMap = createPixelMap(color, opts)
        pixelMap.writeBufferToPixels(byteBuffer)
        // Obtain the width and height of the parsed Pixel_map
        let imageInfo: ImageInfo = pixelMap.getImageInfo()
        let w: Int32 = imageInfo.size.width
        let h: Int32 = imageInfo.size.height
    }
}
