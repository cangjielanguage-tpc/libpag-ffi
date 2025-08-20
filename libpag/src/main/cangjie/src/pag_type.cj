/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.image.AlphaType

@FastNative
foreign {
    func free_CPointer_CJMarker(ptr: CPointer<CJMarker>): Unit

    func free_CPointer_CJPAGVideoRange(ptr: CPointer<CJPAGVideoRange>): Unit

    func free_CPointer_UInt8(ptr: CPointer<UInt8>): Unit

    func free_CPointer_Int64(ptr: CPointer<Int64>): Unit

    func free_CPointer_Float32(ptr: CPointer<Float32>): Unit
}

@C
struct MarkersPAGLayer {
    var size: Int64
    var markers: CPointer<CJMarker>

    init(size: Int64, markers: CPointer<CJMarker>) {
        this.size = size
        this.markers = markers
    }
}

@C
struct CJPAGVideoRangeArray {
    var size: Int64
    var buf: CPointer<CJPAGVideoRange>

    init(size: Int64, buf: CPointer<CJPAGVideoRange>) {
        this.size = size
        this.buf = buf
    }
}

@C
struct CJBytesArray {
    var size: Int64
    var buf: CPointer<UInt8>

    init(size: Int64, buf: CPointer<UInt8>) {
        this.size = size
        this.buf = buf
    }
}

@C
struct CJInt64Array {
    var size: Int64
    var buf: CPointer<Int64>

    init(size: Int64, buf: CPointer<Int64>) {
        this.size = size
        this.buf = buf
    }
}

@C
struct CJFloat32Array {
    var size: Int64
    var buf: CPointer<Float32>

    init(size: Int64, buf: CPointer<Float32>) {
        this.size = size
        this.buf = buf
    }
}

// in the range [0 - 255]
@C
public struct Color {
    var red: UInt8
    var green: UInt8
    var blue: UInt8

    public init(red: UInt8, green: UInt8, blue: UInt8) {
        this.red = red
        this.green = green
        this.blue = blue
    }
}

/**
 * Describes how to interpret the alpha component of a pixel.
 * Corresponding to Cangjie's AlphaType and C++'s enum class AlphaType.
 */
struct PAGAlphaType {
    /**
     * uninitialized.
     */
    static let Unknown: UInt8 = 0
    /**
     * pixel is opaque.
     */
    static let Opaque: UInt8 = 1
    /**
     * pixel components are premultiplied by alpha.
     */
    static let Premultiplied: UInt8 = 2
    /**
     * pixel components are independent of alpha.
     */
    static let Unpremultiplied: UInt8 = 3
}

/**
 * Describes how pixel bits encode color. These values match up with the enum in Bitmap.Config on
 * Corresponding to PixelMapFormat for Cangjie and enum class ColorType for C++.
 */
struct PAGColorType {
    /**
     * uninitialized.
     */
    static let Unknown: UInt8 = 0
    /**
     * Each pixel is stored as a single translucency (alpha) channel. This is very useful for
     * storing masks efficiently, for instance. No color information is stored. With this
     * configuration, each pixel requires 1 byte of memory.
     */
    static let ALPHA_8: UInt8 = 1
    /**
     * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
     * bits of precision (256 possible values). The channel order is: red, green, blue, alpha.
     */
    static let RGBA_8888: UInt8 = 2
    /**
     * Each pixel is stored on 4 bytes. Each channel (RGB and alpha for translucency) is stored with 8
     * bits of precision (256 possible values). The channel order is: blue, green, red, alpha.
     */
    static let BGRA_8888: UInt8 = 3
    /**
     * Each pixel is stored on 2 bytes, and only the RGB channels are encoded: red is stored with 5
     * bits of precision (32 possible values), green is stored with 6 bits of precision (64 possible
     * values), and blue is stored with 5 bits of precision.
     */
    static let RGB_565: UInt8 = 4
    /**
     * Each pixel is stored as a single grayscale level. No color information is stored. With this
     * configuration, each pixel requires 1 byte of memory.
     */
    static let Gray_8: UInt8 = 5
    /**
     * Each pixel is stored on 8 bytes. Each channel (RGB and alpha for translucency) is stored as a
     * half-precision floating point value. This configuration is particularly suited for wide-gamut
     * and HDR content.
     */
    static let RGBA_F16: UInt8 = 6
    /**
     * Each pixel is stored on 4 bytes. Each RGB channel is stored with 10 bits of precision (1024
     * possible values). There is an additional alpha channel that is stored with 2 bits of precision
     * (4 possible values). This configuration is suited for wide-gamut and HDR content which does not
     * require alpha blending, such that the memory cost is the same as RGBA_8888 while enabling
     * higher color precision.
     */
    static let RGBA_1010102: UInt8 = 7
}

func getAlphaType(alphaType: UInt8): AlphaType {
    match (alphaType) {
        case 0 => AlphaType.UNKNOWN // PAGAlphaType.Unknown 0
        case 1 => AlphaType.OPAQUE // PAGAlphaType.Opaque 1
        case 2 => AlphaType.PREMUL // PAGAlphaType.Premultiplied 2
        case 3 => AlphaType.UNPREMUL // PAGAlphaType.Unpremultiplied 3
        case _ => AlphaType.UNKNOWN
    }
}

func getPixelMapFormat(colorType: UInt8): PixelMapFormat {
    match (colorType) {
        case 0 => PixelMapFormat.UNKNOWN // PAGColorType.Unknown 0
        case 1 => PixelMapFormat.ALPHA_8 // PAGColorType.ALPHA_8 1
        case 2 => PixelMapFormat.RGBA_8888 // PAGColorType.RGBA_8888 2
        case 3 => PixelMapFormat.BGRA_8888 // PAGColorType.BGRA_8888 3
        case 4 => PixelMapFormat.RGB_565 // PAGColorType.RGB_565 4
        case 6 => PixelMapFormat.RGBA_F16 // PAGColorType.RGBA_F16 6
        case 0 => PixelMapFormat.UNKNOWN // PAGColorType.Unknown 0
        case _ => PixelMapFormat.UNKNOWN
    }
}
