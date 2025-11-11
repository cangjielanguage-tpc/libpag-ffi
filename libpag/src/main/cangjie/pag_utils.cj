/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

protected class PAGUtils {
    protected static func ToTsMatrix(matrix: Array<Float32>): Matrix4 {
        return Matrix4(
            [matrix[0], matrix[1], matrix[2], 0.0, matrix[3], matrix[4], matrix[5], 0.0, matrix[6], matrix[7], matrix[8],
                0.0, 0.0, 0.0, 0.0, 1.0])
    }

    protected static func ToNativeMatrix(matrix4: Matrix4): Array<Float32> {
        let matrix: Array<Float32> = matrix4.props
        return [matrix[0], matrix[1], matrix[2], matrix[4], matrix[5], matrix[6], matrix[8], matrix[9], matrix[10]]
    }

    protected static func ToTsRect(rect: Array<Float32>): Rect {
        return Rect(
            left: rect[0],
            top: rect[1],
            right: rect[2],
            bottom: rect[3]
        )
    }

    protected static func WarpJPAGLayer(nativeLayer: Int64): PAGLayer {
        if (PAGLayer.isPAGFileOfPAGLayer(nativeLayer)) {
            return PAGFile(nativeLayer)
        }
        let layerType: Int8 = PAGLayer.getLayerType(nativeLayer)
        if (layerType == 2) { // PAGLayerType.Solid
            return PAGSolidLayer(nativeLayer)
        } else if (layerType == 3) { // PAGLayerType.Text:
            return PAGTextLayer(nativeLayer)
        } else if (layerType == 4) { // PAGLayerType.Shape:
            return PAGShapeLayer(nativeLayer)
        } else if (layerType == 5) { // PAGLayerType.Image:
            return PAGImageLayer(nativeLayer)
        } else if (layerType == 6) { // PAGLayerType.PreCompose:
            return PAGComposition(nativeLayer)
        }
        return PAGLayer(nativeLayer)
    }

    protected static func WarpJPAGLayers(nativeLayers: Array<Int64>): Array<PAGLayer> {
        let emptyPAGLayer: PAGLayer = PAGLayer.makeEmptyPAGLayer()
        let result: Array<PAGLayer> = Array<PAGLayer>(nativeLayers.size, repeat: emptyPAGLayer)
        for (i in 0..nativeLayers.size) {
            result[i] = PAGUtils.WarpJPAGLayer(nativeLayers[i])
        }
        return result
    }

    protected static func ToPAGFont(font: Int64): PAGFont {
        let fontFamily: String = PAGFont.getFontFamily(font)
        let fontStyle: String = PAGFont.getFontStyle(font)
        return PAGFont(fontFamily, fontStyle, font)
    }
}

public func MakeColorInt(red: UInt8, green: UInt8, blue: UInt8): Int64 {
    let color: Int64 = Int64(UInt32(255 << 24) | (UInt32(red) << 16) | (UInt32(green) << 8) | (UInt32(blue) << 0))
    return color
}

public func ToColor(value: Int64): Color {
    let color: UInt32 = UInt32(value)
    let red: UInt32 = (((color) >> 16) & 0xFF)
    let green: UInt32 = (((color) >> 8) & 0xFF)
    let blue: UInt32 = (((color) >> 0) & 0xFF)
    return Color(UInt8(red), UInt8(green), UInt8(blue))
}

protected func ConvertToPixelMap(res: CJPixelMap): Option<PixelMap> {
    unsafe {
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

@FastNative
foreign func free_CJBytesArray(ptr: CJBytesArray): Unit

func BytesArrayToString(res: CJBytesArray): String {
    unsafe {
        let size: Int64 = res.size
        if (size == 0) {
            return "";
        }
        let buf: CPointer<UInt8> = res.buf
        let bytes: Array<UInt8> = Array<UInt8>(size, repeat: 0)
        for (i in 0..size) {
            if (buf.isNotNull()) {
                bytes[i] = buf.read(i)
            }
        }
        var str = ""
        try{
            str = String.fromUtf8(bytes)
        } catch (e: Exception) {
            return ""
        }
        return str
    }
}
